#ifndef PLUGIN_PLUGINREGIST_H
#define PLUGIN_PLUGINREGIST_H

// The script VM's plugins and script classes: each Regist function registers one (vmPluginRegist / vmOCRegist),
// pluginRegist all of them. Each is defined in its plugin's own file. (The header's name is not the original's.)
void ocBuiltinRegist();
void ocThreadRegist();
void ocBdatRegist();
void ocMenuRegist();
void ocAiDataRegist();
void pluginWaitRegist();
void pluginDebRegist();
void pluginSysRegist();
void pluginFldRegist();
void pluginPartyRegist();
void pluginUiRegist();
void pluginEvtRegist();
void pluginEvtObjRegist();
void pluginEvtSetupRegist();
void pluginEvtCharaRegist();
void pluginEvtCamRegist();
void pluginEvtEffRegist();
void pluginEvtLgtRegist();
void pluginEvtPostRegist();
void pluginEvtTextRegist();
void pluginEvtSelRegist();
void pluginEvtStatusRegist();
void pluginEvtBgmRegist();
void pluginEvtSeRegist();
void pluginEvtVolRegist();
void pluginEvtRandRegist();
void pluginEvtPayRegist();
// 2.0.0's symbols name it. pluginRegist calls it between pluginEvtPayRegist and pluginEvtEnvRegist; it registers the
// evt_ex plugin (ScriptCamMotion.cpp).
void pluginEvtExRegist();
void pluginEvtEnvRegist();
void pluginEvtMovRegist();
void pluginEvtMapRegist();
void pluginEvtUiRegist();
void pluginEvtVoiceRegist();
void pluginBtlAiRegist();
void pluginGmkRegist();
void pluginRegist();

#endif
