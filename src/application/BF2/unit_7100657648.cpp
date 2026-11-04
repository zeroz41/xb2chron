// Registers every script VM plugin and script class, in the original's order.
#include "plugin/PluginRegist.h"

void pluginRegist() {
    ocBuiltinRegist();
    ocThreadRegist();
    ocBdatRegist();
    ocMenuRegist();
    ocAiDataRegist();
    pluginWaitRegist();
    pluginDebRegist();
    pluginSysRegist();
    pluginFldRegist();
    pluginPartyRegist();
    pluginUiRegist();
    pluginEvtRegist();
    pluginEvtObjRegist();
    pluginEvtSetupRegist();
    pluginEvtCharaRegist();
    pluginEvtCamRegist();
    pluginEvtEffRegist();
    pluginEvtLgtRegist();
    pluginEvtPostRegist();
    pluginEvtTextRegist();
    pluginEvtSelRegist();
    pluginEvtStatusRegist();
    pluginEvtBgmRegist();
    pluginEvtSeRegist();
    pluginEvtVolRegist();
    pluginEvtRandRegist();
    pluginEvtPayRegist();
    pluginEvtExRegist();
    pluginEvtEnvRegist();
    pluginEvtMovRegist();
    pluginEvtMapRegist();
    pluginEvtUiRegist();
    pluginEvtVoiceRegist();
    pluginBtlAiRegist();
    pluginGmkRegist();
}
