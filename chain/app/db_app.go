package app

import (
	"io"

	bam "github.com/cosmos/cosmos-sdk/baseapp"
	abci "github.com/tendermint/tendermint/abci/types"
	"github.com/tendermint/tendermint/libs/log"
	dbm "github.com/tendermint/tm-db"

	"github.com/bandprotocol/d3n/chain/db"
)

type dbBandApp struct {
	*bandApp
	dbBand *db.BandDB
}

func NewDBBandApp(
	logger log.Logger, db dbm.DB, traceStore io.Writer, loadLatest bool,
	invCheckPeriod uint, dbBand *db.BandDB, baseAppOptions ...func(*bam.BaseApp),
) *dbBandApp {
	app := NewBandApp(logger, db, traceStore, loadLatest, invCheckPeriod, baseAppOptions...)

	return &dbBandApp{bandApp: app, dbBand: dbBand}
}

func (app *dbBandApp) InitChain(req abci.RequestInitChain) abci.ResponseInitChain {
	app.dbBand.BeginTransaction()

	app.dbBand.SaveChainID(req.GetChainId())
	app.dbBand.SetBlockHeight(0)

	app.dbBand.Commit()

	return app.bandApp.InitChain(req)
}

func (app *dbBandApp) DeliverTx(req abci.RequestDeliverTx) (res abci.ResponseDeliverTx) {
	res = app.bandApp.DeliverTx(req)
	if res.IsOK() && app.dbBand.GetBlockHeight()+1 == app.DeliverContext.BlockHeight() {
		for _, event := range res.Events {
			kvMap := make(map[string]string)
			for _, kv := range event.Attributes {
				kvMap[string(kv.GetKey())] = string(kv.GetValue())
			}
			app.dbBand.HandleEvent(event.Type, kvMap)
		}
	}
	return res
}

func (app *dbBandApp) BeginBlock(req abci.RequestBeginBlock) (res abci.ResponseBeginBlock) {
	res = app.bandApp.BeginBlock(req)
	// Open transaction
	app.dbBand.BeginTransaction()
	if err := app.dbBand.ValidateChainID(app.DeliverContext.ChainID()); err != nil {
		panic(err)
	}

	return res
}

func (app *dbBandApp) EndBlock(req abci.RequestEndBlock) (res abci.ResponseEndBlock) {
	res = app.bandApp.EndBlock(req)
	app.dbBand.SetBlockHeight(req.GetHeight())
	// Do other logic
	return res
}

func (app *dbBandApp) Commit() (res abci.ResponseCommit) {
	res = app.bandApp.Commit()
	app.dbBand.Commit()
	return res
}
