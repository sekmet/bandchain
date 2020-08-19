// module Styles = {
//   open Css;

//   let vFlex = style([display(`flex), flexDirection(`row), alignItems(`center)]);
//   let hFlex = style([display(`flex), flexDirection(`column), alignItems(`flexStart)]);

//   let logo = style([width(`px(50)), marginRight(`px(10))]);
//   let logoSmall = style([width(`px(20))]);

//   let oracleStatusLogo = style([width(`px(12))]);

//   let oracleBadge = active =>
//     style([
//       display(`flex),
//       flexDirection(`row),
//       backgroundColor(active ? Colors.green4 : `hex("E74A4B")),
//       borderRadius(`px(12)),
//       padding2(~v=`px(5), ~h=`px(7)),
//     ]);

//   let fillLeft = style([marginLeft(`auto)]);

//   let header =
//     style([display(`flex), flexDirection(`row), alignItems(`center), height(`px(50))]);

//   let fullWidth = dir => style([width(`percent(100.0)), display(`flex), flexDirection(dir)]);

//   let seperatedLine =
//     style([
//       width(`px(13)),
//       height(`px(1)),
//       marginLeft(`px(10)),
//       marginRight(`px(10)),
//       backgroundColor(Colors.blueGray2),
//     ]);

//   let longLine = style([width(`px(1)), height(`px(68)), backgroundColor(Colors.blueGray2)]);

//   let topPartWrapper =
//     style([
//       width(`percent(100.0)),
//       display(`flex),
//       flexDirection(`column),
//       backgroundColor(Colors.white),
//       borderRadius(`px(4)),
//       padding2(~v=`px(35), ~h=`px(30)),
//       boxShadow(Shadow.box(~x=`zero, ~y=`px(2), ~blur=`px(8), Css.rgba(0, 0, 0, 0.08))),
//     ]);

//   let validatorWebsiteLink = style([color(Colors.bandBlue)]);

//   // Mobile

//   let validatorBoxMobile =
//     style([
//       width(`percent(100.)),
//       borderRadius(`px(4)),
//       backgroundColor(Colors.white),
//       boxShadow(
//         Shadow.box(~x=`zero, ~y=`px(2), ~blur=`px(4), ~spread=`zero, rgba(0, 0, 0, 0.08)),
//       ),
//       padding2(~v=`px(15), ~h=`px(10)),
//     ]);

//   let monikerContainer =
//     style([display(`flex), flexDirection(`row), alignItems(`center), minHeight(`px(60))]);
//   let addressMobileContainer = style([width(`percent(100.))]);
//   let votingPowerMobile = style([display(`flex), flexDirection(`column), paddingTop(`px(3))]);
//   let headerMobile = style([paddingTop(`px(10))]);

//   let validatorDetailsTopPart =
//     style([
//       selector(
//         "> div + div",
//         [borderLeft(`px(1), `solid, Colors.gray5), paddingLeft(`px(12))],
//       ),
//       selector("> div", [padding2(~h=`px(3), ~v=`px(3))]),
//     ]);
//   let validatorDetailsBox = style([marginBottom(`px(5))]);
// };

// type value_row_t =
//   | VAddress(Address.t)
//   | ValidatorAddress(Address.t)
//   | VText(string)
//   | VDetail(string)
//   | VExtLink(string)
//   | VCode(string)
//   | VReactElement(React.element)
//   | Loading(int, int);

// let kvRowMobile = (k, v: value_row_t) => {
//   <div>
//     <div className=Styles.validatorDetailsBox>
//       <Text value=k size=Text.Xs color=Colors.gray5 />
//     </div>
//     <div className={Styles.fullWidth(`row)}>
//       {switch (v) {
//        | VAddress(address) =>
//          <div className=Styles.addressMobileContainer>
//            <AddressRender address wordBreak=true />
//          </div>
//        | ValidatorAddress(address) =>
//          <div className=Styles.addressMobileContainer>
//            <AddressRender address accountType=`validator wordBreak=true />
//          </div>
//        | VText(value) => <Text value nowrap=true />
//        | VDetail(value) => <Text value />
//        | VExtLink(value) =>
//          <a href=value target="_blank" rel="noopener">
//            <div className=Styles.validatorWebsiteLink> <Text value nowrap=true /> </div>
//          </a>
//        | VCode(value) => <Text value code=true nowrap=true />
//        | VReactElement(element) => element
//        | Loading(width, height) => <LoadingCensorBar width height />
//        }}
//     </div>
//   </div>;
// };

// let kvRow = (k, description, v: value_row_t) => {
//   <Row alignItems=`flexStart wrap=true>
//     <Col size=1.>
//       <div className={Styles.fullWidth(`row)}>
//         <Text value=k weight=Text.Thin tooltipItem=description tooltipPlacement=Text.AlignRight />
//       </div>
//     </Col>
//     <Col size=1. justifyContent=Col.Center alignItems=Col.End>
//       <div className={Styles.fullWidth(`row)}>
//         <div className=Styles.fillLeft />
//         {switch (v) {
//          | VAddress(address) => <AddressRender address />
//          | ValidatorAddress(address) =>
//            <AddressRender address accountType=`validator clickable=false />
//          | VText(value) => <Text value nowrap=true />
//          | VDetail(value) => <Text value align=Text.Right />
//          | VExtLink(value) =>
//            <a href=value target="_blank" rel="noopener">
//              <div className=Styles.validatorWebsiteLink> <Text value nowrap=true /> </div>
//            </a>
//          | VCode(value) => <Text value code=true nowrap=true />
//          | VReactElement(element) => element
//          | Loading(width, height) => <LoadingCensorBar width height />
//          }}
//       </div>
//     </Col>
//   </Row>;
// };

// module Uptime = {
//   [@react.component]
//   let make = (~consensusAddress) => {
//     let uptimeHeader = "UPTIME (LAST 250 BLOCKS)";
//     let uptimeDescription = "Percentage of the blocks that the validator is active for out of the last 250";

//     let uptimeSub = ValidatorSub.getUptime(consensusAddress);
//     switch (uptimeSub) {
//     | Data(uptimeOpt) =>
//       switch (uptimeOpt) {
//       | Some(uptime) =>
//         kvRow(
//           uptimeHeader,
//           {
//             uptimeDescription |> React.string;
//           },
//           VCode(uptime |> Format.fPercent(~digits=2)),
//         )
//       | None =>
//         kvRow(
//           uptimeHeader,
//           {
//             uptimeDescription |> React.string;
//           },
//           VText("N/A"),
//         )
//       }
//     | _ =>
//       kvRow(
//         uptimeHeader,
//         {
//           uptimeDescription |> React.string;
//         },
//         Loading(100, 16),
//       )
//     };
//   };
// };

// module UptimeMobile = {
//   [@react.component]
//   let make = (~consensusAddress) => {
//     let uptimeSub = ValidatorSub.getUptime(consensusAddress);
//     switch (uptimeSub) {
//     | Data(uptimeOpt) =>
//       switch (uptimeOpt) {
//       | Some(uptime) =>
//         kvRowMobile(
//           "UPTIME",
//           VReactElement(
//             <div className=Styles.headerMobile>
//               <Text value={uptime |> Format.fPercent(~digits=2)} weight=Text.Bold code=true />
//             </div>,
//           ),
//         )
//       | None => kvRowMobile("UPTIME", VText("N/A"))
//       }
//     | _ =>
//       kvRowMobile(
//         "UPTIME",
//         VReactElement(
//           <div className=Styles.headerMobile> <LoadingCensorBar width=70 height=16 /> </div>,
//         ),
//       )
//     };
//   };
// };

// module ValidatorDetails = {
//   [@react.component]
//   let make =
//       (~allSub: ApolloHooks.Subscription.variant((BandScan.ValidatorSub.t, BandScan.Coin.t))) => {
//     <Row justify=Row.Between>
//       <Col>
//         <div className={Css.merge([Styles.vFlex, Styles.header])}>
//           <img src=Images.validatorLogo className=Styles.logo />
//           <Text
//             value="VALIDATOR DETAILS"
//             weight=Text.Medium
//             size=Text.Md
//             spacing={Text.Em(0.06)}
//             height={Text.Px(15)}
//             nowrap=true
//             color=Colors.gray7
//             block=true
//           />
//           <div className=Styles.seperatedLine />
//           {switch (allSub) {
//            | Data((validator, _)) =>
//              <>
//                <Text
//                  value={validator.isActive ? "ACTIVE" : "INACTIVE"}
//                  size=Text.Md
//                  weight=Text.Thin
//                  spacing={Text.Em(0.06)}
//                  color=Colors.gray7
//                  nowrap=true
//                />
//                <HSpacing size=Spacing.md />
//                <img
//                  src={
//                    validator.isActive ? Images.activeValidatorLogo : Images.inactiveValidatorLogo
//                  }
//                  className=Styles.logoSmall
//                />
//              </>
//            | _ => <LoadingCensorBar width=80 height=24 />
//            }}
//           <HSpacing size=Spacing.md />
//         </div>
//       </Col>
//     </Row>;
//   };
// };

// module RenderDesktop = {
//   [@react.component]
//   let make = (~address, ~hashtag: Route.validator_tab_t) => {
//     let validatorSub = ValidatorSub.get(address);
//     let bondedTokenCountSub = ValidatorSub.getTotalBondedAmount();
//     let allSub = Sub.all2(validatorSub, bondedTokenCountSub);

//     <Section>
//       <div className=CssHelper.container>
//         <ValidatorDetails allSub />
//         <VSpacing size=Spacing.xl />
//         <div className=Styles.vFlex>
//           {switch (allSub) {
//            | Data(({moniker, identity, oracleStatus}, _)) =>
//              <>
//                <Avatar moniker identity width=40 />
//                <HSpacing size=Spacing.md />
//                <div className=Styles.hFlex>
//                  <Text value=moniker size=Text.Xxl weight=Text.Bold nowrap=true />
//                  <VSpacing size=Spacing.sm />
//                  <div className={Styles.oracleBadge(oracleStatus)}>
//                    <Text
//                      value="ORACLE"
//                      color=Colors.white
//                      weight=Text.Medium
//                      height={Text.Px(11)}
//                    />
//                    <HSpacing size=Spacing.sm />
//                    <img
//                      src={oracleStatus ? Images.whiteCheck : Images.whiteClose}
//                      className=Styles.oracleStatusLogo
//                    />
//                  </div>
//                </div>
//              </>
//            | _ => <LoadingCensorBar width=150 height=30 />
//            }}
//         </div>
//         <VSpacing size=Spacing.xl />
//         <ValidatorStakingInfo validatorAddress=address />
//         <VSpacing size=Spacing.md />
//         <div className=Styles.topPartWrapper>
//           <Text value="INFORMATION" size=Text.Lg weight=Text.Semibold />
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "OPERATOR ADDRESS",
//              {
//                "The address used to show the entity's validator status" |> React.string;
//              },
//              {
//                switch (allSub) {
//                | Data(_) => ValidatorAddress(address)
//                | _ => Loading(360, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "ADDRESS",
//              {
//                "The entity's unique address" |> React.string;
//              },
//              {
//                switch (allSub) {
//                | Data(_) => VAddress(address)
//                | _ => Loading(310, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "VOTING POWER",
//              {
//                "Sum of self-bonded and delegated tokens" |> React.string;
//              },
//  {
//    switch (allSub) {
//    | Data((validator, bondedTokenCount)) =>
//      VCode(
//        (
//          bondedTokenCount.amount > 0.
//            ? validator.votingPower *. 100. /. bondedTokenCount.amount : 0.
//        )
//        ->Format.fPretty
//        ++ "% ("
//        ++ (validator.votingPower /. 1e6 |> Format.fPretty)
//        ++ " BAND)",
//      )
//    | _ => Loading(100, 16)
//    };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "COMMISSION",
//              {
//                "Validator service fees charged to delegators" |> React.string;
//              },
//              {
//                switch (allSub) {
//                | Data((validator, _)) =>
//                  VCode(validator.commission |> Format.fPercent(~digits=2))
//                | _ => Loading(50, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "COMMISSION MAX CHANGE",
//              {
//                "Maximum increment in which the validator can change their commission rate at a time"
//                |> React.string;
//              },
//              {
//                switch (allSub) {
//                | Data((validator, _)) =>
//                  VCode(validator.commissionMaxChange |> Format.fPercent(~digits=2))
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "COMMISSION MAX RATE",
//              {
//                "The highest possible commission rate the validator can set" |> React.string;
//              },
//              {
//                switch (allSub) {
//                | Data((validator, _)) =>
//                  VCode(validator.commissionMaxRate |> Format.fPercent(~digits=2))
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {switch (allSub) {
//            | Data((validator, _)) => <Uptime consensusAddress={validator.consensusAddress} />

//            | _ =>
//              kvRow(
//                "UPTIME",
//                {
//                  "Percentage of the blocks that the validator is active for out of the last 250"
//                  |> React.string;
//                },
//                Loading(100, 16),
//              )
//            }}
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "WEBSITE",
//              {
//                "The validator's website" |> React.string;
//              },
//              {
//                switch (allSub) {
//                | Data((validator, _)) => VExtLink(validator.website)
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRow(
//              "DETAILS",
//              {
//                "Extra self-added detail about the validator" |> React.string;
//              },
//              {
//                switch (allSub) {
//                | Data((validator, _)) => VDetail(validator.details)
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//         </div>
//         // <div className=Styles.longLine />
//         // <div className={Styles.fullWidth(`row)}>
//         //   <Col size=1.>
//         //     <Text value="NODE STATUS" size=Text.Lg weight=Text.Semibold />
//         //     <VSpacing size=Spacing.lg />
//         //     {kvRow("UPTIME", VCode(validator.nodeStatus.uptime->Format.fPretty ++ "%"))}
//         //     <VSpacing size=Spacing.lg />
//         //     {kvRow(
//         //        "AVG. RESPONSE TIME",
//         //        VCode(
//         //          validator.avgResponseTime->Format.iPretty
//         //          ++ (validator.avgResponseTime <= 1 ? " block" : " blocks"),
//         //        ),
//         //      )}
//         //   </Col>
//         //   <HSpacing size=Spacing.lg />
//         //   <Col size=1.>
//         //     <Text value="REQUEST RESPONSE" size=Text.Lg weight=Text.Semibold />
//         //     <VSpacing size=Spacing.lg />
//         //     {kvRow("COMPLETED REQUESTS", VCode(validator.completedRequestCount->Format.iPretty))}
//         //     <VSpacing size=Spacing.lg />
//         //     {kvRow("MISSED REQUESTS", VCode(validator.missedRequestCount->Format.iPretty))}
//         //   </Col>
//         // </div>
//         <VSpacing size=Spacing.md />
//         <Tab
//           tabs=[|
//             {
//               name: "PROPOSED BLOCKS",
//               route: Route.ValidatorIndexPage(address, Route.ProposedBlocks),
//             },
//             {name: "DELEGATORS", route: Route.ValidatorIndexPage(address, Route.Delegators)},
//             {name: "REPORTS", route: Route.ValidatorIndexPage(address, Route.Reports)},
//           |]
//           currentRoute={Route.ValidatorIndexPage(address, hashtag)}>
//           {switch (hashtag) {
//            | ProposedBlocks =>
//              switch (validatorSub) {
//              | Data(validator) =>
//                <ProposedBlocksTable consensusAddress={validator.consensusAddress} />
//              | _ => <ProposedBlocksTable.LoadingWithHeader />
//              }
//            | Delegators => <DelegatorsTable address isMobile=false />
//            | Reports => <ReportsTable address />
//            }}
//         </Tab>
//       </div>
//     </Section>;
//   };
// };

// module RenderMobile = {
//   [@react.component]
//   let make = (~address, ~hashtag: Route.validator_tab_t) => {
//     let validatorSub = ValidatorSub.get(address);
//     let bondedTokenCountSub = ValidatorSub.getTotalBondedAmount();
//     let allSub = Sub.all2(validatorSub, bondedTokenCountSub);

//     <Section>
//       <div className=CssHelper.container>
//         <VSpacing size=Spacing.md />
//         <ValidatorDetails allSub />
//         <VSpacing size=Spacing.md />
//         <VSpacing size=Spacing.sm />
//         <div className=Styles.validatorBoxMobile>
//           <div className=Styles.monikerContainer>
//             {switch (allSub) {
//              | Data(({moniker, identity, _}, _)) =>
//                <>
//                  <Avatar moniker identity width=40 />
//                  <HSpacing size=Spacing.md />
//                  <div className=Styles.hFlex>
//                    <Text value=moniker size=Text.Xxl weight=Text.Bold nowrap=true />
//                  </div>
//                </>
//              | _ => <LoadingCensorBar width=150 height=30 />
//              }}
//           </div>
//           <VSpacing size=Spacing.md />
//           <VSpacing size=Spacing.sm />
//           <Row alignItems=Css.stretch style=Styles.validatorDetailsTopPart>
//             <Col size=1.>
//               {kvRowMobile(
//                  "VOTING POWER",
//                  {
//                    switch (allSub) {
//                    | Data((validator, bondedTokenCount)) =>
//                      VReactElement(
//                        <div className=Styles.votingPowerMobile>
//                          <Text
//                            value={validator.votingPower /. 1e6 |> Format.fPretty}
//                            size=Text.Md
//                            weight=Text.Bold
//                            code=true
//                          />
//                          <VSpacing size=Spacing.xs />
//                          <Text
//                            value={
//                              "("
//                              ++ (
//                                   bondedTokenCount.amount > 0.
//                                     ? validator.votingPower *. 100. /. bondedTokenCount.amount : 0.
//                                 )
//                                 ->Format.fPretty(_, ~digits=2)
//                              ++ "%)"
//                            }
//                            size=Text.Md
//                            weight=Text.Thin
//                            color=Colors.gray6
//                            code=true
//                          />
//                        </div>,
//                      )
//                    | _ =>
//                      VReactElement(
//                        <div className=Styles.votingPowerMobile>
//                          <LoadingCensorBar width=70 height=16 />
//                          <VSpacing size=Spacing.xs />
//                          <LoadingCensorBar width=60 height=16 />
//                        </div>,
//                      )
//                    };
//                  },
//                )}
//             </Col>
//             <Col size=1.>
//               {kvRowMobile(
//                  "COMMISSION",
//                  {
//                    switch (allSub) {
//                    | Data((validator, _)) =>
//                      VReactElement(
//                        <div className=Styles.headerMobile>
//  <Text
//    value={validator.commission |> Format.fPretty(~digits=2)}
//    weight=Text.Bold
//    code=true
//  />
//                        </div>,
//                      )
//                    | _ =>
//                      VReactElement(
//                        <div className=Styles.headerMobile>
//                          <LoadingCensorBar width=60 height=16 />
//                        </div>,
//                      )
//                    };
//                  },
//                )}
//             </Col>
//             <Col size=1.>
//               {switch (allSub) {
//                | Data((validator, _)) =>
//                  <UptimeMobile consensusAddress={validator.consensusAddress} />
//                | _ =>
//                  kvRowMobile(
//                    "UPTIME",
//                    VReactElement(
//                      <div className=Styles.headerMobile>
//                        <LoadingCensorBar width=70 height=16 />
//                      </div>,
//                    ),
//                  )
//                }}
//             </Col>
//           </Row>
//           <VSpacing size=Spacing.lg />
//           <VSpacing size=Spacing.sm />
//           {kvRowMobile(
//              "OPERATOR ADDRESS",
//              {
//                switch (allSub) {
//                | Data(_) => ValidatorAddress(address)
//                | _ => Loading(360, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRowMobile(
//              "ADDRESS",
//              {
//                switch (allSub) {
//                | Data(_) => VAddress(address)
//                | _ => Loading(360, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRowMobile(
//              "COMMISSION MAX CHANGE",
//              {
//                switch (allSub) {
//                | Data((validator, _)) =>
//                  VCode(validator.commissionMaxChange |> Format.fPercent(~digits=2))
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRowMobile(
//              "COMMISSION MAX RATE",
//              {
//                switch (allSub) {
//                | Data((validator, _)) =>
//                  VCode(validator.commissionMaxRate |> Format.fPercent(~digits=2))
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRowMobile(
//              "WEBSITE",
//              {
//                switch (allSub) {
//                | Data((validator, _)) => VExtLink(validator.website)
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//           {kvRowMobile(
//              "DETAILS",
//              {
//                switch (allSub) {
//                | Data((validator, _)) => VDetail(validator.details)
//                | _ => Loading(100, 16)
//                };
//              },
//            )}
//           <VSpacing size=Spacing.lg />
//         </div>
//         <VSpacing size=Spacing.md />
//         <Tab
//           tabs=[|
//             {
//               name: "PROPOSED BLOCKS",
//               route: Route.ValidatorIndexPage(address, Route.ProposedBlocks),
//             },
//             {name: "DELEGATORS", route: Route.ValidatorIndexPage(address, Route.Delegators)},
//             {name: "REPORTS", route: Route.ValidatorIndexPage(address, Route.Reports)},
//           |]
//           currentRoute={Route.ValidatorIndexPage(address, hashtag)}>
//           {switch (hashtag) {
//            | ProposedBlocks =>
//              switch (validatorSub) {
//              | Data(validator) =>
//                <ProposedBlocksTableMobile consensusAddress={validator.consensusAddress} />
//              | _ => <ProposedBlocksTableMobile.Loading />
//              }
//            | Delegators => <DelegatorsTable address isMobile=true />
//            | Reports => <ReportsTable address />
//            }}
//         </Tab>
//       </div>
//     </Section>;
//   };
// };

module Styles = {
  open Css;
  let link = style([color(Colors.bandBlue), textDecoration(`none)]);
  let infoContainer =
    style([
      backgroundColor(Colors.white),
      boxShadow(Shadow.box(~x=`zero, ~y=`px(2), ~blur=`px(4), Css.rgba(0, 0, 0, 0.08))),
      padding(`px(24)),
      Media.mobile([padding(`px(16))]),
    ]);
  let infoHeader =
    style([borderBottom(`px(1), `solid, Colors.gray9), paddingBottom(`px(16))]);
  let loadingBox = style([width(`percent(100.))]);
  let idContainer = style([marginBottom(`px(16)), Media.mobile([marginBottom(`px(8))])]);
  let containerSpacingSm = style([Media.mobile([marginTop(`px(16))])]);

  // Avatar Box

  let avatarContainer =
    style([
      position(`relative),
      marginRight(`px(40)),
      Media.mobile([marginRight(`zero), marginBottom(`px(16))]),
    ]);
  let rankContainer =
    style([
      backgroundColor(Colors.bandBlue),
      borderRadius(`percent(50.)),
      position(`absolute),
      right(`zero),
      bottom(`zero),
      width(`px(26)),
      height(`px(26)),
    ]);

  // Active Status
  let statusBox = isActive_ => {
    style([
      backgroundColor(isActive_ ? Colors.green4 : Colors.gray7),
      position(`relative),
      width(`px(20)),
      height(`px(20)),
      borderRadius(`percent(50.)),
    ]);
  };

  // Oracle Status
  let oracleStatusBox = isActive_ => {
    style([
      backgroundColor(isActive_ ? Colors.green4 : Colors.red4),
      borderRadius(`px(50)),
      padding2(~v=`px(2), ~h=`px(10)),
    ]);
  };

  //Mockup
  let mockup = {
    style([minHeight(`px(300))]);
  };
};

module UptimePercentage = {
  [@react.component]
  let make = (~consensusAddress) => {
    let uptimeSub = ValidatorSub.getUptime(consensusAddress);
    <>
      {switch (uptimeSub) {
       | Data(uptime) =>
         switch (uptime) {
         | Some(uptime) =>
           <Text
             value={uptime |> Format.fPercent(~digits=2)}
             size=Text.Xxxl
             align=Text.Center
             block=true
           />
         | None => <Text value="N/A" size=Text.Xxxl align=Text.Center block=true />
         }
       | _ => <LoadingCensorBar width=100 height=24 />
       }}
    </>;
  };
};

module UptimeBlock = {
  module InnerStyles = {
    open Css;
    let blockContainer =
      style([
        flexGrow(0.),
        flexShrink(0.),
        flexBasis(`calc((`sub, `percent(5.), `px(2)))),
        margin(`px(1)),
        height(`px(16)),
        display(`block),
        Media.smallMobile([height(`px(10))]),
      ]);
    let blockBase = style([width(`percent(100.)), height(`percent(100.))]);
    let status = (~status, ()) => {
      switch (status) {
      | ValidatorSub.Missed => style([backgroundColor(Colors.blue10)])
      | Proposed => style([backgroundColor(Colors.blue9)])
      | Signed => style([backgroundColor(Colors.bandBlue)])
      };
    };
  };
  [@react.component]
  let make = (~status, ~height: ID.Block.t) => {
    let blockRoute = height |> ID.Block.getRoute;
    <CTooltip
      width=90
      tooltipPlacement=CTooltip.Top
      tooltipPlacementSm=CTooltip.BottomLeft
      mobile=false
      align=`center
      pd=10
      tooltipText={height |> ID.Block.toString}
      styles=InnerStyles.blockContainer>
      <Link route=blockRoute className=InnerStyles.blockContainer>
        <div className={Css.merge([InnerStyles.blockBase, InnerStyles.status(~status, ())])} />
      </Link>
    </CTooltip>;
  };
};

module BlockUptimeChart = {
  module InnerStyles = {
    open Css;
    let chartContainer =
      style([
        width(`percent(100.)),
        maxWidth(`px(400)),
        margin2(~v=`zero, ~h=`auto),
        Media.smallMobile([maxWidth(`px(260))]),
      ]);
    let statusLabel = style([height(`px(8)), width(`px(8))]);
  };
  [@react.component]
  let make = (~consensusAddress) => {
    let getUptimeSub = ValidatorSub.getBlockUptimeByValidator(consensusAddress);
    <>
      <Row.Grid marginBottom=24>
        <Col.Grid>
          <div className={Css.merge([CssHelper.flexBox(), InnerStyles.chartContainer])}>
            {switch (getUptimeSub) {
             | Data({validatorVotes}) =>
               validatorVotes
               ->Belt.Array.map(({blockHeight, status}) =>
                   <UptimeBlock key={blockHeight |> ID.Block.toString} status height=blockHeight />
                 )
               ->React.array
             | _ => <LoadingCensorBar width=400 height=90 style=Styles.loadingBox />
             }}
          </div>
        </Col.Grid>
      </Row.Grid>
      <Row.Grid>
        <Col.Grid col=Col.Four colSm=Col.Four>
          <div className={CssHelper.flexBox(~justify=`spaceBetween, ())}>
            <div className={CssHelper.flexBox()}>
              <div
                className={Css.merge([
                  UptimeBlock.InnerStyles.status(~status=ValidatorSub.Proposed, ()),
                  InnerStyles.statusLabel,
                ])}
              />
              <HSpacing size=Spacing.sm />
              <Text block=true value="Proposed" weight=Text.Semibold />
            </div>
            {switch (getUptimeSub) {
             | Data({proposedCount}) => <Text block=true value={proposedCount |> string_of_int} />
             | _ => <LoadingCensorBar width=20 height=14 />
             }}
          </div>
        </Col.Grid>
        <Col.Grid col=Col.Four colSm=Col.Four>
          <div className={CssHelper.flexBox(~justify=`spaceBetween, ())}>
            <div className={CssHelper.flexBox()}>
              <div
                className={Css.merge([
                  UptimeBlock.InnerStyles.status(~status=ValidatorSub.Signed, ()),
                  InnerStyles.statusLabel,
                ])}
              />
              <HSpacing size=Spacing.sm />
              <Text block=true value="Signed" weight=Text.Semibold />
            </div>
            {switch (getUptimeSub) {
             | Data({signedCount}) => <Text block=true value={signedCount |> string_of_int} />
             | _ => <LoadingCensorBar width=20 height=14 />
             }}
          </div>
        </Col.Grid>
        <Col.Grid col=Col.Four colSm=Col.Four>
          <div className={CssHelper.flexBox(~justify=`spaceBetween, ())}>
            <div className={CssHelper.flexBox()}>
              <div
                className={Css.merge([
                  UptimeBlock.InnerStyles.status(~status=ValidatorSub.Missed, ()),
                  InnerStyles.statusLabel,
                ])}
              />
              <HSpacing size=Spacing.sm />
              <Text block=true value="Missed" weight=Text.Semibold />
            </div>
            {switch (getUptimeSub) {
             | Data({missedCount}) => <Text block=true value={missedCount |> string_of_int} />
             | _ => <LoadingCensorBar width=20 height=14 />
             }}
          </div>
        </Col.Grid>
      </Row.Grid>
    </>;
  };
};

[@react.component]
let make = (~address, ~hashtag: Route.validator_tab_t) => {
  // Media.isMobile() ? <RenderMobile address hashtag /> : <RenderDesktop address hashtag />;
  let validatorSub = ValidatorSub.get(address);
  let bondedTokenCountSub = ValidatorSub.getTotalBondedAmount();
  let allSub = Sub.all2(validatorSub, bondedTokenCountSub);

  <Section pbSm=0>
    <div className=CssHelper.container>
      <Heading value="Validator Details" size=Heading.H4 marginBottom=40 marginBottomSm=24 />
      <Row.Grid marginBottom=40 marginBottomSm=16 alignItems=Row.Center>
        <Col.Grid col=Col.Nine>
          <div
            className={Css.merge([
              CssHelper.flexBox(),
              CssHelper.flexBoxSm(~direction=`column, ()),
              Styles.idContainer,
            ])}>
            <div className=Styles.avatarContainer>
              {switch (allSub) {
               | Data(({identity, rank, moniker}, _)) =>
                 <>
                   <Avatar moniker identity width=100 widthSm=80 />
                   <div
                     className={Css.merge([
                       Styles.rankContainer,
                       CssHelper.flexBox(~justify=`center, ()),
                     ])}>
                     //TODO: Will get rank later
                      <Text value={rank |> string_of_int} color=Colors.white /> </div>
                 </>
               | _ => <LoadingCensorBar width=100 height=100 radius=100 />
               }}
            </div>
            {switch (allSub) {
             | Data(({moniker}, _)) => <Heading size=Heading.H3 value=moniker />
             | _ => <LoadingCensorBar width=270 height=20 />
             }}
          </div>
        </Col.Grid>
        <Col.Grid col=Col.Three>
          <div
            className={Css.merge([
              CssHelper.flexBox(~justify=`flexEnd, ()),
              CssHelper.flexBoxSm(~justify=`center, ()),
            ])}>
            {switch (allSub) {
             | Data(({isActive}, _)) =>
               <div className={CssHelper.flexBox()}>
                 <div
                   className={Css.merge([
                     CssHelper.flexBox(~justify=`center, ()),
                     Styles.statusBox(isActive),
                   ])}>
                   <Icon name={isActive ? "fas fa-bolt" : "fas fa-moon"} color=Colors.white />
                 </div>
                 <HSpacing size=Spacing.sm />
                 <Text value={isActive ? "Active" : "Inactive"} />
               </div>
             | _ => <LoadingCensorBar width=60 height=14 />
             }}
            <HSpacing size=Spacing.md />
            {switch (allSub) {
             | Data(({oracleStatus}, _)) =>
               <div
                 className={Css.merge([
                   CssHelper.flexBox(~justify=`center, ()),
                   Styles.oracleStatusBox(oracleStatus),
                 ])}>
                 <Text value="Oracle" color=Colors.white />
                 <HSpacing size=Spacing.sm />
                 <Icon
                   name={oracleStatus ? "fas fa-check" : "fal fa-times"}
                   color=Colors.white
                   size=10
                 />
               </div>
             | _ => <LoadingCensorBar width=75 height=14 />
             }}
          </div>
        </Col.Grid>
      </Row.Grid>
      <Row.Grid marginBottom=24 marginBottomSm=16>
        <Col.Grid>
          <div className=Styles.infoContainer>
            <Row.Grid>
              <Col.Grid col=Col.Three colSm=Col.Six mbSm=48>
                <div className={CssHelper.flexBox(~direction=`column, ())}>
                  <Heading
                    value="Voting power"
                    size=Heading.H4
                    marginBottom=16
                    align=Heading.Center
                  />
                  {switch (allSub) {
                   | Data(({votingPower}, {amount})) =>
                     <>
                       <Text
                         value={votingPower *. 100. /. amount |> Format.fPercent(~digits=2)}
                         size=Text.Xxxl
                         align=Text.Center
                         block=true
                       />
                     </>
                   | _ => <LoadingCensorBar width=100 height=24 />
                   }}
                  <VSpacing size=Spacing.xs />
                  {switch (allSub) {
                   | Data(({votingPower}, _)) =>
                     <>
                       <Text
                         value={(votingPower /. 1e6 |> Format.fPretty(~digits=0)) ++ " Band"}
                         size=Text.Lg
                         color=Colors.gray6
                         align=Text.Center
                         block=true
                       />
                     </>
                   | _ => <LoadingCensorBar width=80 height=14 />
                   }}
                </div>
              </Col.Grid>
              <Col.Grid col=Col.Three colSm=Col.Six mbSm=48>
                <div className={CssHelper.flexBox(~direction=`column, ())}>
                  <Heading
                    value="Commission"
                    size=Heading.H4
                    marginBottom=27
                    align=Heading.Center
                  />
                  {switch (allSub) {
                   | Data(({commission}, _)) =>
                     <>
                       <Text
                         value={commission |> Format.fPercent(~digits=2)}
                         size=Text.Xxxl
                         align=Text.Center
                         block=true
                       />
                     </>
                   | _ => <LoadingCensorBar width=100 height=24 />
                   }}
                </div>
              </Col.Grid>
              <Col.Grid col=Col.Three colSm=Col.Six>
                <div className={CssHelper.flexBox(~direction=`column, ())}>
                  <Heading value="Uptime" size=Heading.H4 marginBottom=27 align=Heading.Center />
                  {switch (allSub) {
                   | Data(({consensusAddress}, _)) => <UptimePercentage consensusAddress />
                   | _ => <LoadingCensorBar width=100 height=24 />
                   }}
                </div>
              </Col.Grid>
              <Col.Grid col=Col.Three colSm=Col.Six>
                <div className={CssHelper.flexBox(~direction=`column, ())}>
                  <div className={Css.merge([CssHelper.flexBox(), CssHelper.mb(~size=27, ())])}>
                    <Heading value="Oracle Reports" size=Heading.H4 align=Heading.Center />
                    <HSpacing size=Spacing.xs />
                    //TODO: remove mock message later
                    <CTooltip
                      tooltipPlacementSm=CTooltip.BottomRight
                      tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                      <Icon name="fal fa-info-circle" size=12 />
                    </CTooltip>
                  </div>
                  {switch (allSub) {
                   | Data(({oracleReports}, _)) =>
                     <Text
                       value={oracleReports |> Format.iPretty}
                       size=Text.Xxxl
                       color=Colors.gray7
                       align=Text.Center
                       block=true
                     />
                   | _ => <LoadingCensorBar width=100 height=24 />
                   }}
                </div>
              </Col.Grid>
            </Row.Grid>
          </div>
        </Col.Grid>
      </Row.Grid>
      <Row.Grid marginBottom=24>
        <Col.Grid>
          <div className=Styles.infoContainer>
            <Heading value="Information" size=Heading.H4 style=Styles.infoHeader marginBottom=24 />
            <Row.Grid marginBottom=24>
              <Col.Grid col=Col.Six mbSm=24>
                <div className={CssHelper.flexBox()}>
                  <Heading value="Operator Address" size=Heading.H5 />
                  <HSpacing size=Spacing.xs />
                  //TODO: remove mock message later
                  <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                    <Icon name="fal fa-info-circle" size=10 />
                  </CTooltip>
                </div>
                <VSpacing size=Spacing.sm />
                {switch (allSub) {
                 | Data(({operatorAddress}, _)) =>
                   <AddressRender
                     address=operatorAddress
                     position=AddressRender.Subtitle
                     accountType=`validator
                   />
                 | _ => <LoadingCensorBar width=284 height=15 />
                 }}
              </Col.Grid>
              <Col.Grid col=Col.Six>
                <div className={CssHelper.flexBox()}>
                  <Heading value="Address" size=Heading.H5 />
                  <HSpacing size=Spacing.xs />
                  //TODO: remove mock message later
                  <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                    <Icon name="fal fa-info-circle" size=10 />
                  </CTooltip>
                </div>
                <VSpacing size=Spacing.sm />
                {switch (allSub) {
                 | Data(({operatorAddress}, _)) =>
                   <AddressRender address=operatorAddress position=AddressRender.Subtitle />
                 | _ => <LoadingCensorBar width=284 height=15 />
                 }}
              </Col.Grid>
            </Row.Grid>
            <Row.Grid marginBottom=24>
              <Col.Grid col=Col.Six mbSm=24>
                <div className={CssHelper.flexBox()}>
                  <Heading value="Commission Max Change" size=Heading.H5 />
                  <HSpacing size=Spacing.xs />
                  //TODO: remove mock message later
                  <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                    <Icon name="fal fa-info-circle" size=10 />
                  </CTooltip>
                </div>
                <VSpacing size=Spacing.sm />
                {switch (allSub) {
                 | Data(({commissionMaxChange}, _)) =>
                   <Text
                     value={commissionMaxChange |> Format.fPercent(~digits=2)}
                     size=Text.Lg
                     block=true
                   />
                 | _ => <LoadingCensorBar width=284 height=15 />
                 }}
              </Col.Grid>
              <Col.Grid col=Col.Six>
                <div className={CssHelper.flexBox()}>
                  <Heading value="Commission Max Rate" size=Heading.H5 />
                  <HSpacing size=Spacing.xs />
                  //TODO: remove mock message later
                  <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                    <Icon name="fal fa-info-circle" size=10 />
                  </CTooltip>
                </div>
                <VSpacing size=Spacing.sm />
                {switch (allSub) {
                 | Data(({commissionMaxRate}, _)) =>
                   <Text
                     value={commissionMaxRate |> Format.fPercent(~digits=2)}
                     size=Text.Lg
                     block=true
                   />
                 | _ => <LoadingCensorBar width=284 height=15 />
                 }}
              </Col.Grid>
            </Row.Grid>
            <Row.Grid marginBottom=24>
              <Col.Grid>
                <Heading value="Website" size=Heading.H5 marginBottom=16 />
                {switch (allSub) {
                 | Data(({website}, _)) =>
                   <a href=website target="_blank" className=Styles.link>
                     <Text value=website size=Text.Lg color=Colors.bandBlue block=true />
                   </a>
                 | _ => <LoadingCensorBar width=284 height=15 />
                 }}
              </Col.Grid>
            </Row.Grid>
            <Row.Grid marginBottom=24>
              <Col.Grid>
                <Heading value="Description" size=Heading.H5 marginBottom=16 />
                {switch (allSub) {
                 | Data(({details}, _)) =>
                   <p> <Text value=details size=Text.Lg color=Colors.gray7 block=true /> </p>
                 | _ => <LoadingCensorBar width=284 height=15 />
                 }}
              </Col.Grid>
            </Row.Grid>
          </div>
        </Col.Grid>
      </Row.Grid>
      <Row.Grid marginBottom=24>
        <Col.Grid col=Col.Four mbSm=24>
          <div className={Css.merge([Styles.mockup, Styles.infoContainer])}>
            <div className={Css.merge([CssHelper.flexBox(), Styles.infoHeader])}>
              <Heading value="Bonded Token" size=Heading.H5 />
              <HSpacing size=Spacing.xs />
              //TODO: remove mock message later
              <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                <Icon name="fal fa-info-circle" size=10 />
              </CTooltip>
            </div>
          </div>
        </Col.Grid>
        <Col.Grid col=Col.Eight>
          <div className={Css.merge([Styles.mockup, Styles.infoContainer])}>
            <div className={Css.merge([CssHelper.flexBox(), Styles.infoHeader])}>
              <Heading value="Your Delegation Info" size=Heading.H5 />
              <HSpacing size=Spacing.xs />
              //TODO: remove mock message later
              <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                <Icon name="fal fa-info-circle" size=10 />
              </CTooltip>
            </div>
          </div>
        </Col.Grid>
      </Row.Grid>
      <Row.Grid marginBottom=24>
        <Col.Grid col=Col.Six mbSm=24>
          <div className=Styles.infoContainer>
            <div
              className={Css.merge([
                CssHelper.flexBox(),
                CssHelper.mb(~size=24, ()),
                Styles.infoHeader,
              ])}>
              <Heading value="Block Uptime" size=Heading.H5 />
              <HSpacing size=Spacing.xs />
              //TODO: remove mock message later
              <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                <Icon name="fal fa-info-circle" size=10 />
              </CTooltip>
            </div>
            {switch (allSub) {
             | Data(({consensusAddress}, _)) => <BlockUptimeChart consensusAddress />
             | _ => <LoadingCensorBar width=400 height=90 style=Styles.loadingBox />
             }}
          </div>
        </Col.Grid>
        <Col.Grid col=Col.Six>
          <div className={Css.merge([Styles.mockup, Styles.infoContainer])}>
            <div className={Css.merge([CssHelper.flexBox(), Styles.infoHeader])}>
              <Heading value="Oracle Data Report" size=Heading.H5 />
              <HSpacing size=Spacing.xs />
              //TODO: remove mock message later
              <CTooltip tooltipText="Lorem ipsum, or lipsum as it is sometimes known.">
                <Icon name="fal fa-info-circle" size=10 />
              </CTooltip>
            </div>
          </div>
        </Col.Grid>
      </Row.Grid>
    </div>
  </Section>;
};
