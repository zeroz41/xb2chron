#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatRsc.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the resource tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked up once
// (init) and a row's value read through it (get)
namespace _gfbrs {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberRscEnDebugName;
static unsigned char* s_memberRscEnTypeFamily;
static unsigned char* s_memberRscEnTypeGenus;
static unsigned char* s_memberRscEnActType;
static unsigned char* s_memberRscEnFlyHeight;
static unsigned char* s_memberRscEnFldMoveType;
static unsigned char* s_memberRscEnMaterial;
static unsigned char* s_memberRscEnProxyID;
static unsigned char* s_memberRscEnEnRadius;
static unsigned char* s_memberRscEnEnRadius2;
static unsigned char* s_memberRscEnChestHeight;
static unsigned char* s_memberRscEnChestHeight2;
static unsigned char* s_memberRscEnBallRadius;
static unsigned char* s_memberRscEnBallHeight;
static unsigned char* s_memberRscEnCharColli;
static unsigned char* s_memberRscEnoffsetID;
static unsigned char* s_memberRscEnEyeRot;
static unsigned char* s_memberRscEnSearchBaseBone;
static unsigned char* s_memberRscEnCenterBone;
static unsigned char* s_memberRscEnCamBone;
static unsigned char* s_memberRscEnFrontAngle;
static unsigned char* s_memberRscEnTurnAngleSmall;
static unsigned char* s_memberRscEnTurnAngleBig;
static unsigned char* s_memberRscEnUnduration;
static unsigned char* s_memberRscEnModel;
static unsigned char* s_memberRscEnChrFile;
static unsigned char* s_memberRscEnMotion;
static unsigned char* s_memberRscEnRefMotion;
static unsigned char* s_memberRscEnEffectPack;
static unsigned char* s_memberRscEnLoopEffect;
static unsigned char* s_memberRscEnSePack;
static unsigned char* s_memberRscEnVoice;
static unsigned char* s_memberRscEnVoiceEx;
static unsigned char* s_memberRscEnClipEvent;
static unsigned char* s_memberRscEnComp_Eff;
static unsigned char* s_memberRscEnComp_Se;
static unsigned char* s_memberRscEnComp_Vo;
static unsigned char* s_memberRscEnFlagNoEcSkipFlag;
static unsigned char* s_memberRscEnFlagNoEcSkip;
static unsigned char* s_memberRscEnFlagMapFlag;
static unsigned char* s_memberRscEnFlagMap;
static unsigned char* s_memberRscEnFlagEvtFlag;
static unsigned char* s_memberRscEnFlagEvt;
static unsigned char* s_memberRscEnFlagNoWinVoFlag;
static unsigned char* s_memberRscEnFlagNoWinVo;
static unsigned char* s_memberRscEnFlagBaitFlag;
static unsigned char* s_memberRscEnFlagBait;
static unsigned char* s_memberRscEnFlagUseSearchBoneFlag;
static unsigned char* s_memberRscEnFlagUseSearchBone;
static unsigned char* s_memberRscEnFlagNoVanishFlag;
static unsigned char* s_memberRscEnFlagNoVanish;
static unsigned char* s_memberRscEnFlagNoCameraFlag;
static unsigned char* s_memberRscEnFlagNoCamera;
static unsigned char* s_memberRscEnFlagWeaponDrawDispFlag;
static unsigned char* s_memberRscEnFlagWeaponDrawDisp;
static unsigned char* s_memberRscEnFlagJoinAllFlag;
static unsigned char* s_memberRscEnFlagJoinAll;
static unsigned char* s_memberRscEnFlagDeathMotionFlag;
static unsigned char* s_memberRscEnFlagDeathMotion;
static unsigned char* s_memberRscEnWeaponNum1;
static unsigned char* s_memberRscEnWeaponNum2;
static unsigned char* s_memberRscEnWeaponNum3;
static unsigned char* s_memberRscEnWeaponNum4;
static unsigned char* s_memberRscEnWeaponNum5;
static unsigned char* s_memberRscEnMemorySlot;
static unsigned char* s_memberRscEnRace;
static unsigned char* s_memberRscEnDrType;
static unsigned char* s_memberRscEnGoldDivideRev;
static unsigned char* s_memberRscEnFootStep;
static unsigned char* s_memberRscEnFootStepEffect;
static unsigned char* s_memberRscEnRotateX;
static unsigned char* s_memberRscEnRotateY;
static unsigned char* s_memberRscEnRotateZ;
static unsigned char* s_memberRscEnRotateDeg;
static unsigned char* s_memberRscEnRotEffScale;
static unsigned char* s_memberRscEnExtraParts1;
static unsigned char* s_memberRscEnExtraParts2;
static unsigned char* s_memberRscEnExtraParts3;
static unsigned char* s_memberRscEnExtraParts4;
static unsigned char* s_memberRscEnExtraParts5;
static unsigned char* s_memberRscEnExtraParts6;
static unsigned char* s_memberRscEnDeadSeNum;
static unsigned char* s_memberRscEnRotateBone;
static unsigned char* s_memberRscEnGenusNAME;
static unsigned char* s_memberRscEnGenusCAPTION;
static unsigned char* s_memberRscEnGenusFlaggimmicktypeFlag;
static unsigned char* s_memberRscEnGenusFlaggimmicktype;
static unsigned char* s_memberRscEnUndFlagUndXFlag;
static unsigned char* s_memberRscEnUndFlagUndX;
static unsigned char* s_memberRscEnUndFlagUndZFlag;
static unsigned char* s_memberRscEnUndFlagUndZ;
static unsigned char* s_memberRscEnUndUndMinX;
static unsigned char* s_memberRscEnUndUndMaxX;
static unsigned char* s_memberRscEnUndUndMinZ;
static unsigned char* s_memberRscEnUndUndMaxZ;
static unsigned char* s_memberRscEnUndUndDeg;
static unsigned char* s_memberRscNpcListModel;
static unsigned char* s_memberRscNpcListMotion;
static unsigned char* s_memberRscNpcListAddMotion;
static unsigned char* s_memberRscNpcListEvtRetarget;
static unsigned char* s_memberRscNpcListComp_Eff;
static unsigned char* s_memberRscNpcListCollisionId;
static unsigned char* s_memberRscNpcListSE;
static unsigned char* s_memberRscNpcListSeEnv;
static unsigned char* s_memberRscNpcListRace;
static unsigned char* s_memberRscNpcListFootStep;
static unsigned char* s_memberRscNpcListFootStepEffect;
static unsigned char* s_memberRscNpcListRoots;
static unsigned char* s_memberRscNpcListGender;
static unsigned char* s_memberRscNpcListName;
static unsigned char* s_memberRscNpcListOffsetID;
static unsigned char* s_memberRscNpcListEyeRot;
static unsigned char* s_memberRscNpcListExtraParts1;
static unsigned char* s_memberRscNpcListExtraParts2;
static unsigned char* s_memberRscNpcListExtraParts3;
static unsigned char* s_memberRscNpcListExtraParts4;
static unsigned char* s_memberRscNpcListExtraParts5;
static unsigned char* s_memberRscNpcListExtraParts6;
static unsigned char* s_memberRscNpcListScale;
static unsigned char* s_memberRscNpcListEventAsset;
static unsigned char* s_memberRscNpcListJob;
static unsigned char* s_memberRscNpcListHitonowaFlag;
static unsigned char* s_memberRscNpcListNpcMeetFlag;
static unsigned char* s_memberRscNpcListMSGID;
static unsigned char* s_memberRscNpcListCondition1;
static unsigned char* s_memberRscNpcListMSGID2;
static unsigned char* s_memberRscNpcListCondition2;
static unsigned char* s_memberRscNpcListMSGID3;
static unsigned char* s_memberRscNpcListresult;
static unsigned char* s_memberRscMobListModel;
static unsigned char* s_memberRscMobListMotion;
static unsigned char* s_memberRscMobListAddMotion;
static unsigned char* s_memberRscMobListComp_Eff;
static unsigned char* s_memberRscMobListCollisionId;
static unsigned char* s_memberRscMobListSE;
static unsigned char* s_memberRscMobListSeEnv;
static unsigned char* s_memberRscMobListRace;
static unsigned char* s_memberRscMobListFootStep;
static unsigned char* s_memberRscMobListFootStepEffect;
static unsigned char* s_memberRscMobListOffsetID;
static unsigned char* s_memberRscMobListExtraParts1;
static unsigned char* s_memberRscMobListExtraParts2;
static unsigned char* s_memberRscMobListExtraParts3;
static unsigned char* s_memberRscMobListExtraParts4;
static unsigned char* s_memberRscMobListExtraParts5;
static unsigned char* s_memberRscMobListExtraParts6;
static unsigned char* s_memberRSC_MapObjListModel;
static unsigned char* s_memberRSC_MapObjListMotion;
static unsigned char* s_memberRSC_MapObjListComp_Eff;
static unsigned char* s_memberRSC_MapObjListSE;
static unsigned char* s_memberRSC_MapObjListSeEnv;
static unsigned char* s_memberRSC_MapObjListflagBigObjFlag;
static unsigned char* s_memberRSC_MapObjListflagBigObj;
static unsigned char* s_memberRSC_MapObjListExtraParts1;
static unsigned char* s_memberRSC_TboxListModel;
static unsigned char* s_memberRSC_TboxListMotion;
static unsigned char* s_memberRSC_PcWpnModel;
static unsigned char* s_memberRSC_PcWpnMotion;
static unsigned char* s_memberRSC_PcWpnMenuImageID;
static unsigned char* s_memberRSC_PcWpnMountWpn01rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn01rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn02rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn02rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn03rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn03rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn03lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn03lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn04rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn04rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn05rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn05rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn05lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn05lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn06rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn06rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn07rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn07rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn07lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn07lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn08rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn08rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn09rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn09rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn09lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn09lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn10rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn10rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn10lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn10lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn11rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn11rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn12rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn12rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn12lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn12lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn13rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn13rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn14rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn14rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn15rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn15rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn16rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn16rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn16lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn16lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn17rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn17rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn18rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn18rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn19rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn19rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn20rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn20rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn20lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn20lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn21rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn21rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn22rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn22rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn22lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn22lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn23rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn23rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn23lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn23lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn24rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn24rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn24lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn24lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn25rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn25rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn25lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn25lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn26rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn26rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn26lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn26lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn28rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn28rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn28lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn28lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn29rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn29rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn29lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn29lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn30rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn30rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn30lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn30lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn31rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn31rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn31lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn31lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn32rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn32rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn32lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn32lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn33rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn33rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn33lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn33lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn34rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn34rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn34lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn34lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn35rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn35rOut;
static unsigned char* s_memberRSC_PcWpnMountWpn35lIn;
static unsigned char* s_memberRSC_PcWpnMountWpn35lOut;
static unsigned char* s_memberRSC_PcWpnMountWpn36rIn;
static unsigned char* s_memberRSC_PcWpnMountWpn36rOut;
static unsigned char* s_memberRscEnWpnModel;
static unsigned char* s_memberRscEnWpnScale;
static unsigned char* s_memberRscEnWpnMotion;
static unsigned char* s_memberRscEnWpnMtpInChara;
static unsigned char* s_memberRscEnWpnMtpInWpn;
static unsigned char* s_memberRscEnWpnMtpOutChara;
static unsigned char* s_memberRscEnWpnMtpOutWpn;
static unsigned char* s_memberRscNpcWpnModel;
static unsigned char* s_memberRscNpcWpnMotion;
static unsigned char* s_memberDriverParamExtMountNpc;
static unsigned char* s_memberDriverParamExtMountBone;
static unsigned char* s_memberDriverParamExtMountCond;
static unsigned char* s_memberVoiceTableDriver1;
static unsigned char* s_memberVoiceTableDriver2;
static unsigned char* s_memberVoiceTableDriver3;
static unsigned char* s_memberVoiceTableDriver4;
static unsigned char* s_memberVoiceTableDriver5;
static unsigned char* s_memberVoiceTableDriver6;
static unsigned char* s_memberVoiceTableIra1;
static unsigned char* s_memberVoiceTableIra2;
static unsigned char* s_memberVoiceTableIra3;
static unsigned char* s_memberVoiceTableIra4;
static unsigned char* s_memberVoiceTableIra5;
static unsigned char* s_memberVoiceTableIra6;
static unsigned char* s_memberVoiceTableIra7;
static unsigned char* s_memberVoiceTableIra8;
static unsigned char* s_memberVoiceTableIra9;
static unsigned char* s_memberVoiceTableBladeBlade1;
static unsigned char* s_memberVoiceTableBladeBlade2;
static unsigned char* s_memberVoiceTableBladeBlade3;
static unsigned char* s_memberVoiceTableBladeBlade4;
static unsigned char* s_memberVoiceTableBladeBlade5;
static unsigned char* s_memberVoiceTableBladeBlade6;
static unsigned char* s_memberVoiceTableBladeBlade7;
static unsigned char* s_memberVoiceTableBladeBlade8;
static unsigned char* s_memberVoiceTableBladeBlade9;
static unsigned char* s_memberVoiceTableBladeBlade10;
static unsigned char* s_memberVoiceTableBladeBlade11;
static unsigned char* s_memberVoiceTableRareRareBlade1;
static unsigned char* s_memberVoiceTableRareRareBlade2;
static unsigned char* s_memberVoiceTableRareRareBlade3;
static unsigned char* s_memberVoiceTableRareRareBlade4;
static unsigned char* s_memberVoiceTableRareRareBlade5;
static unsigned char* s_memberVoiceTableRareRareBlade6;
static unsigned char* s_memberVoiceTableRareRareBlade7;
static unsigned char* s_memberVoiceTableRareRareBlade8;
static unsigned char* s_memberVoiceTableRareRareBlade9;
static unsigned char* s_memberVoiceTableRareRareBlade10;
static unsigned char* s_memberVoiceTableRareRareBlade11;
static unsigned char* s_memberVoiceTableRareRareBlade12;
static unsigned char* s_memberVoiceTableRareRareBlade13;
static unsigned char* s_memberVoiceTableRareRareBlade14;
static unsigned char* s_memberVoiceTableRareRareBlade15;
static unsigned char* s_memberVoiceTableRareRareBlade16;
static unsigned char* s_memberVoiceTableRareRareBlade17;
static unsigned char* s_memberVoiceTableRareRareBlade18;
static unsigned char* s_memberVoiceTableRareRareBlade19;
static unsigned char* s_memberVoiceTableRareRareBlade20;
static unsigned char* s_memberVoiceTableRareRareBlade21;
static unsigned char* s_memberVoiceTableRareRareBlade22;
static unsigned char* s_memberVoiceTableRareRareBlade23;
static unsigned char* s_memberVoiceTableRareRareBlade24;
static unsigned char* s_memberVoiceTableRareRareBlade25;
static unsigned char* s_memberVoiceTableRareRareBlade26;
static unsigned char* s_memberVoiceTableRareRareBlade27;
static unsigned char* s_memberVoiceTableRareRareBlade28;
static unsigned char* s_memberVoiceTableRareRareBlade29;
static unsigned char* s_memberVoiceTableRareRareBlade30;
static unsigned char* s_memberVoiceTableRareRareBlade31;
static unsigned char* s_memberVoiceTableRareRareBlade32;
static unsigned char* s_memberVoiceTableRareRareBlade33;
static unsigned char* s_memberVoiceTableRareRareBlade34;
static unsigned char* s_memberVoiceTableRareRareBlade35;
static unsigned char* s_memberVoiceTableRareRareBlade36;
static unsigned char* s_memberVoiceTableRareRareBlade37;
static unsigned char* s_memberVoiceTableRareRareBlade38;
static unsigned char* s_memberVoiceTableRareRareBlade39;
static unsigned char* s_memberVoiceTableRareRareBlade40;
static unsigned char* s_memberVoiceTableRareRareBlade41;
static unsigned char* s_memberVoiceTableRareRareBlade42;
static unsigned char* s_memberVoiceTableRareRareBlade43;
static unsigned char* s_memberVoiceTableRareRareBlade44;
static unsigned char* s_memberVoiceTableCommonCommonBlade1;
static unsigned char* s_memberVoiceTableCommonCommonBlade2;
static unsigned char* s_memberVoiceTableCommonCommonBlade3;
static unsigned char* s_memberVoiceTableCommonCommonBlade4;
static unsigned char* s_memberVoiceTableCommonCommonBlade5;
static unsigned char* s_memberVoiceTableCommonCommonBlade6;
static unsigned char* s_memberVoiceTableCommonCommonBlade7;
static unsigned char* s_memberVoiceTableCommonCommonBlade8;
static unsigned char* s_memberVoiceTableCommonCommonBlade9;
static unsigned char* s_memberVoiceTableCommonCommonBlade10;
static unsigned char* s_memberVoiceTableCommonCommonBlade11;
static unsigned char* s_memberVoiceTableCommonCommonBlade12;
static unsigned char* s_memberVoiceTableCommonCommonBlade13;
static unsigned char* s_memberVoiceTableCommonCommonBlade14;
static unsigned char* s_memberVoiceTableCommonCommonBlade15;
static unsigned char* s_memberVoiceTableCommonCommonBlade16;
static unsigned char* s_memberVoiceTableCommonCommonBlade17;
static unsigned char* s_memberVoiceTableCommonCommonBlade18;
static unsigned char* s_memberVoiceTableCommonCommonBlade19;
static unsigned char* s_memberVoiceTableCommonCommonBlade20;
static unsigned char* s_memberVoiceTableCommonCommonBlade21;
static unsigned char* s_memberVoiceTableCommonCommonBlade22;
static unsigned char* s_memberVoiceTableCommonCommonBlade23;
static unsigned char* s_memberVoiceTableCommonCommonBlade24;
static unsigned char* s_memberVoiceTableCommonCommonBlade25;
static unsigned char* s_memberVoiceTableCommonCommonBlade26;
static unsigned char* s_memberVoiceTableCommonCommonBlade27;
static unsigned char* s_memberVoiceTableCommonCommonBlade28;
static unsigned char* s_memberVoiceTableCommonCommonBlade29;
static unsigned char* s_memberVoiceTableCommonCommonBlade30;
static unsigned char* s_memberVoiceTableCommonCommonBlade31;
static unsigned char* s_memberVoiceTableCommonCommonBlade32;
static unsigned char* s_memberFLD_actorSELOD;
static unsigned char* s_memberFLD_actorSEse_type;
static unsigned char* s_memberFLD_actorSEseName;
static unsigned char* s_memberFLD_actorSEmax_volume_Dist;
static unsigned char* s_memberFLD_actorSEmin_volume_Dist;
static unsigned char* s_memberFLD_actorSEvolumeMAX;
static unsigned char* s_memberFLD_actorSEvolumeMIN;
static unsigned char* s_memberFLD_actorSEoffsetX;
static unsigned char* s_memberFLD_actorSEoffsetY;
static unsigned char* s_memberFLD_actorSEoffsetZ;
static unsigned char* s_memberNoRetargetAnoRetarget;
static unsigned char* s_memberNoRetargetBnoRetarget;

// 3.0.1's column: 1.0.0 has no RscEnDebugName accessors (the name is not the original's)
void initRscEnDebugName(const CBdatWrapper& bdat) {
    s_memberRscEnDebugName = bdat.getMember("DebugName");
}

void initRscEnTypeFamily(const CBdatWrapper& bdat) {
    s_memberRscEnTypeFamily = bdat.getMember("TypeFamily");
}

unsigned int getRscEnTypeFamily(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnTypeFamily != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnTypeFamily, id, 1);
    }
    return 0;
}

void initRscEnTypeGenus(const CBdatWrapper& bdat) {
    s_memberRscEnTypeGenus = bdat.getMember("TypeGenus");
}

unsigned int getRscEnTypeGenus(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnTypeGenus != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnTypeGenus, id, 1);
    }
    return 0;
}

void initRscEnActType(const CBdatWrapper& bdat) {
    s_memberRscEnActType = bdat.getMember("ActType");
}

unsigned int getRscEnActType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnActType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnActType, id, 1);
    }
    return 0;
}

void initRscEnFlyHeight(const CBdatWrapper& bdat) {
    s_memberRscEnFlyHeight = bdat.getMember("FlyHeight");
}

int getRscEnFlyHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFlyHeight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (short)bdat.getValCheck(s_memberRscEnFlyHeight, id, 5);
    }
    return 0;
}

void initRscEnFldMoveType(const CBdatWrapper& bdat) {
    s_memberRscEnFldMoveType = bdat.getMember("FldMoveType");
}

unsigned int getRscEnFldMoveType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFldMoveType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnFldMoveType, id, 1);
    }
    return 0;
}

void initRscEnMaterial(const CBdatWrapper& bdat) {
    s_memberRscEnMaterial = bdat.getMember("Material");
}

unsigned int getRscEnMaterial(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnMaterial != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnMaterial, id, 1);
    }
    return 0;
}

void initRscEnProxyID(const CBdatWrapper& bdat) {
    s_memberRscEnProxyID = bdat.getMember("ProxyID");
}

void initRscEnEnRadius(const CBdatWrapper& bdat) {
    s_memberRscEnEnRadius = bdat.getMember("EnRadius");
}

unsigned int getRscEnEnRadius(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnEnRadius != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnEnRadius, id, 1);
    }
    return 0;
}

void initRscEnEnRadius2(const CBdatWrapper& bdat) {
    s_memberRscEnEnRadius2 = bdat.getMember("EnRadius2");
}

unsigned int getRscEnEnRadius2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnEnRadius2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnEnRadius2, id, 1);
    }
    return 0;
}

void initRscEnChestHeight(const CBdatWrapper& bdat) {
    s_memberRscEnChestHeight = bdat.getMember("ChestHeight");
}

unsigned int getRscEnChestHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnChestHeight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnChestHeight, id, 2);
    }
    return 0;
}

void initRscEnChestHeight2(const CBdatWrapper& bdat) {
    s_memberRscEnChestHeight2 = bdat.getMember("ChestHeight2");
}

unsigned int getRscEnChestHeight2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnChestHeight2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnChestHeight2, id, 2);
    }
    return 0;
}

void initRscEnBallRadius(const CBdatWrapper& bdat) {
    s_memberRscEnBallRadius = bdat.getMember("BallRadius");
}

float getRscEnBallRadius(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnBallRadius != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberRscEnBallRadius, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initRscEnBallHeight(const CBdatWrapper& bdat) {
    s_memberRscEnBallHeight = bdat.getMember("BallHeight");
}

float getRscEnBallHeight(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnBallHeight != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberRscEnBallHeight, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initRscEnCharColli(const CBdatWrapper& bdat) {
    s_memberRscEnCharColli = bdat.getMember("CharColli");
}

float getRscEnCharColli(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnCharColli != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberRscEnCharColli, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initRscEnoffsetID(const CBdatWrapper& bdat) {
    s_memberRscEnoffsetID = bdat.getMember("offsetID");
}

unsigned int getRscEnoffsetID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnoffsetID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnoffsetID, id, 2);
    }
    return 0;
}

void initRscEnEyeRot(const CBdatWrapper& bdat) {
    s_memberRscEnEyeRot = bdat.getMember("EyeRot");
}

unsigned int getRscEnEyeRot(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnEyeRot != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnEyeRot, id, 1);
    }
    return 0;
}

void initRscEnSearchBaseBone(const CBdatWrapper& bdat) {
    s_memberRscEnSearchBaseBone = bdat.getMember("SearchBaseBone");
}

const char* getRscEnSearchBaseBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnSearchBaseBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnSearchBaseBone, id, 7);
    }
    return nullptr;
}

void initRscEnCenterBone(const CBdatWrapper& bdat) {
    s_memberRscEnCenterBone = bdat.getMember("CenterBone");
}

const char* getRscEnCenterBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnCenterBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnCenterBone, id, 7);
    }
    return nullptr;
}

void initRscEnCamBone(const CBdatWrapper& bdat) {
    s_memberRscEnCamBone = bdat.getMember("CamBone");
}

const char* getRscEnCamBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnCamBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnCamBone, id, 7);
    }
    return nullptr;
}

void initRscEnFrontAngle(const CBdatWrapper& bdat) {
    s_memberRscEnFrontAngle = bdat.getMember("FrontAngle");
}

unsigned int getRscEnFrontAngle(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFrontAngle != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnFrontAngle, id, 1);
    }
    return 0;
}

void initRscEnTurnAngleSmall(const CBdatWrapper& bdat) {
    s_memberRscEnTurnAngleSmall = bdat.getMember("TurnAngleSmall");
}

void initRscEnTurnAngleBig(const CBdatWrapper& bdat) {
    s_memberRscEnTurnAngleBig = bdat.getMember("TurnAngleBig");
}

void initRscEnUnduration(const CBdatWrapper& bdat) {
    s_memberRscEnUnduration = bdat.getMember("Unduration");
}

void initRscEnModel(const CBdatWrapper& bdat) {
    s_memberRscEnModel = bdat.getMember("Model");
}

const char* getRscEnModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnModel, id, 7);
    }
    return nullptr;
}

void initRscEnChrFile(const CBdatWrapper& bdat) {
    s_memberRscEnChrFile = bdat.getMember("ChrFile");
}

void initRscEnMotion(const CBdatWrapper& bdat) {
    s_memberRscEnMotion = bdat.getMember("Motion");
}

const char* getRscEnMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnMotion, id, 7);
    }
    return nullptr;
}

void initRscEnRefMotion(const CBdatWrapper& bdat) {
    s_memberRscEnRefMotion = bdat.getMember("RefMotion");
}

const char* getRscEnRefMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRefMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnRefMotion, id, 7);
    }
    return nullptr;
}

void initRscEnEffectPack(const CBdatWrapper& bdat) {
    s_memberRscEnEffectPack = bdat.getMember("EffectPack");
}

const char* getRscEnEffectPack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnEffectPack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnEffectPack, id, 7);
    }
    return nullptr;
}

void initRscEnLoopEffect(const CBdatWrapper& bdat) {
    s_memberRscEnLoopEffect = bdat.getMember("LoopEffect");
}

const char* getRscEnLoopEffect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnLoopEffect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnLoopEffect, id, 7);
    }
    return nullptr;
}

void initRscEnSePack(const CBdatWrapper& bdat) {
    s_memberRscEnSePack = bdat.getMember("SePack");
}

const char* getRscEnSePack(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnSePack != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnSePack, id, 7);
    }
    return nullptr;
}

void initRscEnVoice(const CBdatWrapper& bdat) {
    s_memberRscEnVoice = bdat.getMember("Voice");
}

const char* getRscEnVoice(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnVoice != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnVoice, id, 7);
    }
    return nullptr;
}

void initRscEnVoiceEx(const CBdatWrapper& bdat) {
    s_memberRscEnVoiceEx = bdat.getMember("VoiceEx");
}

unsigned int getRscEnVoiceEx(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnVoiceEx != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnVoiceEx, id, 1);
    }
    return 0;
}

void initRscEnClipEvent(const CBdatWrapper& bdat) {
    s_memberRscEnClipEvent = bdat.getMember("ClipEvent");
}

void initRscEnComp_Eff(const CBdatWrapper& bdat) {
    s_memberRscEnComp_Eff = bdat.getMember("Comp_Eff");
}

const char* getRscEnComp_Eff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnComp_Eff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnComp_Eff, id, 7);
    }
    return nullptr;
}

void initRscEnComp_Se(const CBdatWrapper& bdat) {
    s_memberRscEnComp_Se = bdat.getMember("Comp_Se");
}

void initRscEnComp_Vo(const CBdatWrapper& bdat) {
    s_memberRscEnComp_Vo = bdat.getMember("Comp_Vo");
}

void initRscEnFlagNoEcSkip(const CBdatWrapper& bdat) {
    s_memberRscEnFlagNoEcSkipFlag = bdat.getMember("Flag");
    s_memberRscEnFlagNoEcSkip = bdat.getMember("NoEcSkip");
}

void initRscEnFlagMap(const CBdatWrapper& bdat) {
    s_memberRscEnFlagMapFlag = bdat.getMember("Flag");
    s_memberRscEnFlagMap = bdat.getMember("Map");
}

void initRscEnFlagEvt(const CBdatWrapper& bdat) {
    s_memberRscEnFlagEvtFlag = bdat.getMember("Flag");
    s_memberRscEnFlagEvt = bdat.getMember("Evt");
}

void initRscEnFlagNoWinVo(const CBdatWrapper& bdat) {
    s_memberRscEnFlagNoWinVoFlag = bdat.getMember("Flag");
    s_memberRscEnFlagNoWinVo = bdat.getMember("NoWinVo");
}

void initRscEnFlagBait(const CBdatWrapper& bdat) {
    s_memberRscEnFlagBaitFlag = bdat.getMember("Flag");
    s_memberRscEnFlagBait = bdat.getMember("Bait");
}

// (the name is not the original's: 3.0.1's column, read only inline)
bool getRscEnFlagBait(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFlagBaitFlag != nullptr && s_memberRscEnFlagBait != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberRscEnFlagBaitFlag, id, s_memberRscEnFlagBait) != 0;
    }
    return false;
}

void initRscEnFlagUseSearchBone(const CBdatWrapper& bdat) {
    s_memberRscEnFlagUseSearchBoneFlag = bdat.getMember("Flag");
    s_memberRscEnFlagUseSearchBone = bdat.getMember("UseSearchBone");
}

void initRscEnFlagNoVanish(const CBdatWrapper& bdat) {
    s_memberRscEnFlagNoVanishFlag = bdat.getMember("Flag");
    s_memberRscEnFlagNoVanish = bdat.getMember("NoVanish");
}

// (the name is not the original's: 3.0.1's column, read only inline)
bool getRscEnFlagNoVanish(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFlagNoVanishFlag != nullptr && s_memberRscEnFlagNoVanish != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberRscEnFlagNoVanishFlag, id, s_memberRscEnFlagNoVanish) != 0;
    }
    return false;
}

void initRscEnFlagNoCamera(const CBdatWrapper& bdat) {
    s_memberRscEnFlagNoCameraFlag = bdat.getMember("Flag");
    s_memberRscEnFlagNoCamera = bdat.getMember("NoCamera");
}

// (the name is not the original's: 3.0.1's column, read only inline)
bool getRscEnFlagNoCamera(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFlagNoCameraFlag != nullptr && s_memberRscEnFlagNoCamera != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberRscEnFlagNoCameraFlag, id, s_memberRscEnFlagNoCamera) != 0;
    }
    return false;
}

void initRscEnFlagWeaponDrawDisp(const CBdatWrapper& bdat) {
    s_memberRscEnFlagWeaponDrawDispFlag = bdat.getMember("Flag");
    s_memberRscEnFlagWeaponDrawDisp = bdat.getMember("WeaponDrawDisp");
}

// (the name is not the original's: 3.0.1's column, read only inline)
bool getRscEnFlagWeaponDrawDisp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFlagWeaponDrawDispFlag != nullptr && s_memberRscEnFlagWeaponDrawDisp != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberRscEnFlagWeaponDrawDispFlag, id, s_memberRscEnFlagWeaponDrawDisp) != 0;
    }
    return false;
}

void initRscEnFlagJoinAll(const CBdatWrapper& bdat) {
    s_memberRscEnFlagJoinAllFlag = bdat.getMember("Flag");
    s_memberRscEnFlagJoinAll = bdat.getMember("JoinAll");
}

// (the name is not the original's: 3.0.1's column, read only inline)
bool getRscEnFlagJoinAll(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFlagJoinAllFlag != nullptr && s_memberRscEnFlagJoinAll != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberRscEnFlagJoinAllFlag, id, s_memberRscEnFlagJoinAll) != 0;
    }
    return false;
}

void initRscEnFlagDeathMotion(const CBdatWrapper& bdat) {
    s_memberRscEnFlagDeathMotionFlag = bdat.getMember("Flag");
    s_memberRscEnFlagDeathMotion = bdat.getMember("DeathMotion");
}

// (the name is not the original's: 3.0.1's column, read only inline)
bool getRscEnFlagDeathMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFlagDeathMotionFlag != nullptr && s_memberRscEnFlagDeathMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberRscEnFlagDeathMotionFlag, id, s_memberRscEnFlagDeathMotion) != 0;
    }
    return false;
}

void initRscEnWeaponNum1(const CBdatWrapper& bdat) {
    s_memberRscEnWeaponNum1 = bdat.getMember("WeaponNum1");
}

unsigned int getRscEnWeaponNum1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWeaponNum1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnWeaponNum1, id, 2);
    }
    return 0;
}

void initRscEnWeaponNum2(const CBdatWrapper& bdat) {
    s_memberRscEnWeaponNum2 = bdat.getMember("WeaponNum2");
}

unsigned int getRscEnWeaponNum2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWeaponNum2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnWeaponNum2, id, 2);
    }
    return 0;
}

void initRscEnWeaponNum3(const CBdatWrapper& bdat) {
    s_memberRscEnWeaponNum3 = bdat.getMember("WeaponNum3");
}

unsigned int getRscEnWeaponNum3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWeaponNum3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnWeaponNum3, id, 2);
    }
    return 0;
}

void initRscEnWeaponNum4(const CBdatWrapper& bdat) {
    s_memberRscEnWeaponNum4 = bdat.getMember("WeaponNum4");
}

unsigned int getRscEnWeaponNum4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWeaponNum4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnWeaponNum4, id, 2);
    }
    return 0;
}

void initRscEnWeaponNum5(const CBdatWrapper& bdat) {
    s_memberRscEnWeaponNum5 = bdat.getMember("WeaponNum5");
}

unsigned int getRscEnWeaponNum5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWeaponNum5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnWeaponNum5, id, 2);
    }
    return 0;
}

void initRscEnMemorySlot(const CBdatWrapper& bdat) {
    s_memberRscEnMemorySlot = bdat.getMember("MemorySlot");
}

unsigned int getRscEnMemorySlot(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnMemorySlot != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnMemorySlot, id, 1);
    }
    return 0;
}

void initRscEnRace(const CBdatWrapper& bdat) {
    s_memberRscEnRace = bdat.getMember("Race");
}

unsigned int getRscEnRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnRace, id, 1);
    }
    return 0;
}

void initRscEnDrType(const CBdatWrapper& bdat) {
    s_memberRscEnDrType = bdat.getMember("DrType");
}

unsigned int getRscEnDrType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnDrType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnDrType, id, 1);
    }
    return 0;
}

void initRscEnGoldDivideRev(const CBdatWrapper& bdat) {
    s_memberRscEnGoldDivideRev = bdat.getMember("GoldDivideRev");
}

int getRscEnGoldDivideRev(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnGoldDivideRev != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberRscEnGoldDivideRev, id, 4);
    }
    return 0;
}

void initRscEnFootStep(const CBdatWrapper& bdat) {
    s_memberRscEnFootStep = bdat.getMember("FootStep");
}

unsigned int getRscEnFootStep(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFootStep != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnFootStep, id, 1);
    }
    return 0;
}

void initRscEnFootStepEffect(const CBdatWrapper& bdat) {
    s_memberRscEnFootStepEffect = bdat.getMember("FootStepEffect");
}

unsigned int getRscEnFootStepEffect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnFootStepEffect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnFootStepEffect, id, 1);
    }
    return 0;
}

void initRscEnRotateX(const CBdatWrapper& bdat) {
    s_memberRscEnRotateX = bdat.getMember("RotateX");
}

int getRscEnRotateX(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRotateX != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberRscEnRotateX, id, 4);
    }
    return 0;
}

void initRscEnRotateY(const CBdatWrapper& bdat) {
    s_memberRscEnRotateY = bdat.getMember("RotateY");
}

int getRscEnRotateY(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRotateY != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberRscEnRotateY, id, 4);
    }
    return 0;
}

void initRscEnRotateZ(const CBdatWrapper& bdat) {
    s_memberRscEnRotateZ = bdat.getMember("RotateZ");
}

int getRscEnRotateZ(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRotateZ != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberRscEnRotateZ, id, 4);
    }
    return 0;
}

void initRscEnRotateDeg(const CBdatWrapper& bdat) {
    s_memberRscEnRotateDeg = bdat.getMember("RotateDeg");
}

int getRscEnRotateDeg(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRotateDeg != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (signed char)bdat.getValCheck(s_memberRscEnRotateDeg, id, 4);
    }
    return 0;
}

void initRscEnRotEffScale(const CBdatWrapper& bdat) {
    s_memberRscEnRotEffScale = bdat.getMember("RotEffScale");
}

unsigned int getRscEnRotEffScale(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRotEffScale != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnRotEffScale, id, 2);
    }
    return 0;
}

void initRscEnExtraParts1(const CBdatWrapper& bdat) {
    s_memberRscEnExtraParts1 = bdat.getMember("ExtraParts1");
}

unsigned int getRscEnExtraParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnExtraParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnExtraParts1, id, 1);
    }
    return 0;
}

void initRscEnExtraParts2(const CBdatWrapper& bdat) {
    s_memberRscEnExtraParts2 = bdat.getMember("ExtraParts2");
}

unsigned int getRscEnExtraParts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnExtraParts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnExtraParts2, id, 1);
    }
    return 0;
}

void initRscEnExtraParts3(const CBdatWrapper& bdat) {
    s_memberRscEnExtraParts3 = bdat.getMember("ExtraParts3");
}

unsigned int getRscEnExtraParts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnExtraParts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnExtraParts3, id, 1);
    }
    return 0;
}

void initRscEnExtraParts4(const CBdatWrapper& bdat) {
    s_memberRscEnExtraParts4 = bdat.getMember("ExtraParts4");
}

unsigned int getRscEnExtraParts4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnExtraParts4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnExtraParts4, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscEnExtraParts5 accessors (the name is not the original's)
void initRscEnExtraParts5(const CBdatWrapper& bdat) {
    s_memberRscEnExtraParts5 = bdat.getMember("ExtraParts5");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RscEn getters holds it.
// What it does: reads the ExtraParts5 column (unsigned int) of a row, as the init function above found it.
unsigned int fn_710020D650(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnExtraParts5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnExtraParts5, id, 1);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscEnExtraParts6 accessors (the name is not the original's)
void initRscEnExtraParts6(const CBdatWrapper& bdat) {
    s_memberRscEnExtraParts6 = bdat.getMember("ExtraParts6");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RscEn getters holds it.
// What it does: reads the ExtraParts6 column (unsigned int) of a row, as the init function above found it.
unsigned int fn_710020D6D8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnExtraParts6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnExtraParts6, id, 1);
    }
    return 0;
}

void initRscEnDeadSeNum(const CBdatWrapper& bdat) {
    s_memberRscEnDeadSeNum = bdat.getMember("DeadSeNum");
}

unsigned int getRscEnDeadSeNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnDeadSeNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnDeadSeNum, id, 1);
    }
    return 0;
}

void initRscEnRotateBone(const CBdatWrapper& bdat) {
    s_memberRscEnRotateBone = bdat.getMember("RotateBone");
}

const char* getRscEnRotateBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnRotateBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnRotateBone, id, 7);
    }
    return nullptr;
}

void initRscEnGenusNAME(const CBdatWrapper& bdat) {
    s_memberRscEnGenusNAME = bdat.getMember("NAME");
}

unsigned int getRscEnGenusNAME(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnGenusNAME != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscEnGenusNAME, id, 1);
    }
    return 0;
}

void initRscEnGenusCAPTION(const CBdatWrapper& bdat) {
    s_memberRscEnGenusCAPTION = bdat.getMember("CAPTION");
}

void initRscEnGenusFlaggimmicktype(const CBdatWrapper& bdat) {
    s_memberRscEnGenusFlaggimmicktypeFlag = bdat.getMember("Flag");
    s_memberRscEnGenusFlaggimmicktype = bdat.getMember("gimmicktype");
}

// (the name is not the original's: 3.0.1's column, read only inline)
bool getRscEnGenusFlaggimmicktype(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnGenusFlaggimmicktypeFlag != nullptr && s_memberRscEnGenusFlaggimmicktype != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberRscEnGenusFlaggimmicktypeFlag, id, s_memberRscEnGenusFlaggimmicktype) != 0;
    }
    return false;
}

void initRscEnUndFlagUndX(const CBdatWrapper& bdat) {
    s_memberRscEnUndFlagUndXFlag = bdat.getMember("Flag");
    s_memberRscEnUndFlagUndX = bdat.getMember("UndX");
}

void initRscEnUndFlagUndZ(const CBdatWrapper& bdat) {
    s_memberRscEnUndFlagUndZFlag = bdat.getMember("Flag");
    s_memberRscEnUndFlagUndZ = bdat.getMember("UndZ");
}

void initRscEnUndUndMinX(const CBdatWrapper& bdat) {
    s_memberRscEnUndUndMinX = bdat.getMember("UndMinX");
}

void initRscEnUndUndMaxX(const CBdatWrapper& bdat) {
    s_memberRscEnUndUndMaxX = bdat.getMember("UndMaxX");
}

void initRscEnUndUndMinZ(const CBdatWrapper& bdat) {
    s_memberRscEnUndUndMinZ = bdat.getMember("UndMinZ");
}

void initRscEnUndUndMaxZ(const CBdatWrapper& bdat) {
    s_memberRscEnUndUndMaxZ = bdat.getMember("UndMaxZ");
}

void initRscEnUndUndDeg(const CBdatWrapper& bdat) {
    s_memberRscEnUndUndDeg = bdat.getMember("UndDeg");
}

void initRscNpcListModel(const CBdatWrapper& bdat) {
    s_memberRscNpcListModel = bdat.getMember("Model");
}

const char* getRscNpcListModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscNpcListModel, id, 7);
    }
    return nullptr;
}

void initRscNpcListMotion(const CBdatWrapper& bdat) {
    s_memberRscNpcListMotion = bdat.getMember("Motion");
}

const char* getRscNpcListMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscNpcListMotion, id, 7);
    }
    return nullptr;
}

void initRscNpcListAddMotion(const CBdatWrapper& bdat) {
    s_memberRscNpcListAddMotion = bdat.getMember("AddMotion");
}

const char* getRscNpcListAddMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListAddMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscNpcListAddMotion, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RscNpcListEvtRetarget accessors (the name is not the original's)
void initRscNpcListEvtRetarget(const CBdatWrapper& bdat) {
    s_memberRscNpcListEvtRetarget = bdat.getMember("EvtRetarget");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListEvtRetarget(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListEvtRetarget != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListEvtRetarget, id, 1);
    }
    return 0;
}

void initRscNpcListComp_Eff(const CBdatWrapper& bdat) {
    s_memberRscNpcListComp_Eff = bdat.getMember("Comp_Eff");
}

const char* getRscNpcListComp_Eff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListComp_Eff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscNpcListComp_Eff, id, 7);
    }
    return nullptr;
}

void initRscNpcListCollisionId(const CBdatWrapper& bdat) {
    s_memberRscNpcListCollisionId = bdat.getMember("CollisionId");
}

unsigned int getRscNpcListCollisionId(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListCollisionId != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListCollisionId, id, 2);
    }
    return 0;
}

void initRscNpcListSE(const CBdatWrapper& bdat) {
    s_memberRscNpcListSE = bdat.getMember("SE");
}

void initRscNpcListSeEnv(const CBdatWrapper& bdat) {
    s_memberRscNpcListSeEnv = bdat.getMember("SeEnv");
}

void initRscNpcListRace(const CBdatWrapper& bdat) {
    s_memberRscNpcListRace = bdat.getMember("Race");
}

unsigned int getRscNpcListRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListRace, id, 1);
    }
    return 0;
}

void initRscNpcListFootStep(const CBdatWrapper& bdat) {
    s_memberRscNpcListFootStep = bdat.getMember("FootStep");
}

unsigned int getRscNpcListFootStep(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListFootStep != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListFootStep, id, 2);
    }
    return 0;
}

void initRscNpcListFootStepEffect(const CBdatWrapper& bdat) {
    s_memberRscNpcListFootStepEffect = bdat.getMember("FootStepEffect");
}

unsigned int getRscNpcListFootStepEffect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListFootStepEffect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListFootStepEffect, id, 1);
    }
    return 0;
}

void initRscNpcListRoots(const CBdatWrapper& bdat) {
    s_memberRscNpcListRoots = bdat.getMember("Roots");
}

unsigned int getRscNpcListRoots(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListRoots != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListRoots, id, 1);
    }
    return 0;
}

void initRscNpcListGender(const CBdatWrapper& bdat) {
    s_memberRscNpcListGender = bdat.getMember("Gender");
}

unsigned int getRscNpcListGender(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListGender != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListGender, id, 1);
    }
    return 0;
}

void initRscNpcListName(const CBdatWrapper& bdat) {
    s_memberRscNpcListName = bdat.getMember("Name");
}

unsigned int getRscNpcListName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListName, id, 2);
    }
    return 0;
}

void initRscNpcListOffsetID(const CBdatWrapper& bdat) {
    s_memberRscNpcListOffsetID = bdat.getMember("OffsetID");
}

unsigned int getRscNpcListOffsetID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListOffsetID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListOffsetID, id, 2);
    }
    return 0;
}

void initRscNpcListEyeRot(const CBdatWrapper& bdat) {
    s_memberRscNpcListEyeRot = bdat.getMember("EyeRot");
}

unsigned int getRscNpcListEyeRot(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListEyeRot != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListEyeRot, id, 1);
    }
    return 0;
}

void initRscNpcListExtraParts1(const CBdatWrapper& bdat) {
    s_memberRscNpcListExtraParts1 = bdat.getMember("ExtraParts1");
}

unsigned int getRscNpcListExtraParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListExtraParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListExtraParts1, id, 1);
    }
    return 0;
}

void initRscNpcListExtraParts2(const CBdatWrapper& bdat) {
    s_memberRscNpcListExtraParts2 = bdat.getMember("ExtraParts2");
}

unsigned int getRscNpcListExtraParts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListExtraParts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListExtraParts2, id, 1);
    }
    return 0;
}

void initRscNpcListExtraParts3(const CBdatWrapper& bdat) {
    s_memberRscNpcListExtraParts3 = bdat.getMember("ExtraParts3");
}

unsigned int getRscNpcListExtraParts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListExtraParts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListExtraParts3, id, 1);
    }
    return 0;
}

void initRscNpcListExtraParts4(const CBdatWrapper& bdat) {
    s_memberRscNpcListExtraParts4 = bdat.getMember("ExtraParts4");
}

unsigned int getRscNpcListExtraParts4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListExtraParts4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListExtraParts4, id, 1);
    }
    return 0;
}

void initRscNpcListExtraParts5(const CBdatWrapper& bdat) {
    s_memberRscNpcListExtraParts5 = bdat.getMember("ExtraParts5");
}

unsigned int getRscNpcListExtraParts5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListExtraParts5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListExtraParts5, id, 1);
    }
    return 0;
}

void initRscNpcListExtraParts6(const CBdatWrapper& bdat) {
    s_memberRscNpcListExtraParts6 = bdat.getMember("ExtraParts6");
}

unsigned int getRscNpcListExtraParts6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListExtraParts6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscNpcListExtraParts6, id, 1);
    }
    return 0;
}

void initRscNpcListScale(const CBdatWrapper& bdat) {
    s_memberRscNpcListScale = bdat.getMember("Scale");
}

unsigned int getRscNpcListScale(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListScale != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListScale, id, 2);
    }
    return 0;
}

void initRscNpcListEventAsset(const CBdatWrapper& bdat) {
    s_memberRscNpcListEventAsset = bdat.getMember("EventAsset");
}

// 3.0.1's column: 1.0.0 has no RscNpcListJob accessors (the name is not the original's)
void initRscNpcListJob(const CBdatWrapper& bdat) {
    s_memberRscNpcListJob = bdat.getMember("Job");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListJob(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListJob != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListJob, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListHitonowaFlag accessors (the name is not the original's)
void initRscNpcListHitonowaFlag(const CBdatWrapper& bdat) {
    s_memberRscNpcListHitonowaFlag = bdat.getMember("HitonowaFlag");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListHitonowaFlag(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListHitonowaFlag != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListHitonowaFlag, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListNpcMeetFlag accessors (the name is not the original's)
void initRscNpcListNpcMeetFlag(const CBdatWrapper& bdat) {
    s_memberRscNpcListNpcMeetFlag = bdat.getMember("NpcMeetFlag");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListNpcMeetFlag(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListNpcMeetFlag != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListNpcMeetFlag, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListMSGID accessors (the name is not the original's)
void initRscNpcListMSGID(const CBdatWrapper& bdat) {
    s_memberRscNpcListMSGID = bdat.getMember("MSGID");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListMSGID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListMSGID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListMSGID, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListCondition1 accessors (the name is not the original's)
void initRscNpcListCondition1(const CBdatWrapper& bdat) {
    s_memberRscNpcListCondition1 = bdat.getMember("Condition1");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListCondition1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListCondition1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListCondition1, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListMSGID2 accessors (the name is not the original's)
void initRscNpcListMSGID2(const CBdatWrapper& bdat) {
    s_memberRscNpcListMSGID2 = bdat.getMember("MSGID2");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListMSGID2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListMSGID2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListMSGID2, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListCondition2 accessors (the name is not the original's)
void initRscNpcListCondition2(const CBdatWrapper& bdat) {
    s_memberRscNpcListCondition2 = bdat.getMember("Condition2");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListCondition2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListCondition2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListCondition2, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListMSGID3 accessors (the name is not the original's)
void initRscNpcListMSGID3(const CBdatWrapper& bdat) {
    s_memberRscNpcListMSGID3 = bdat.getMember("MSGID3");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListMSGID3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListMSGID3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListMSGID3, id, 2);
    }
    return 0;
}

// 3.0.1's column: 1.0.0 has no RscNpcListresult accessors (the name is not the original's)
void initRscNpcListresult(const CBdatWrapper& bdat) {
    s_memberRscNpcListresult = bdat.getMember("result");
}

// (the name is not the original's: 3.0.1's column, read only inline)
unsigned int getRscNpcListresult(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcListresult != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscNpcListresult, id, 2);
    }
    return 0;
}

void initRscMobListModel(const CBdatWrapper& bdat) {
    s_memberRscMobListModel = bdat.getMember("Model");
}

const char* getRscMobListModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscMobListModel, id, 7);
    }
    return nullptr;
}

void initRscMobListMotion(const CBdatWrapper& bdat) {
    s_memberRscMobListMotion = bdat.getMember("Motion");
}

const char* getRscMobListMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscMobListMotion, id, 7);
    }
    return nullptr;
}

void initRscMobListAddMotion(const CBdatWrapper& bdat) {
    s_memberRscMobListAddMotion = bdat.getMember("AddMotion");
}

const char* getRscMobListAddMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListAddMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscMobListAddMotion, id, 7);
    }
    return nullptr;
}

void initRscMobListComp_Eff(const CBdatWrapper& bdat) {
    s_memberRscMobListComp_Eff = bdat.getMember("Comp_Eff");
}

const char* getRscMobListComp_Eff(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListComp_Eff != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscMobListComp_Eff, id, 7);
    }
    return nullptr;
}

void initRscMobListCollisionId(const CBdatWrapper& bdat) {
    s_memberRscMobListCollisionId = bdat.getMember("CollisionId");
}

void initRscMobListSE(const CBdatWrapper& bdat) {
    s_memberRscMobListSE = bdat.getMember("SE");
}

void initRscMobListSeEnv(const CBdatWrapper& bdat) {
    s_memberRscMobListSeEnv = bdat.getMember("SeEnv");
}

void initRscMobListRace(const CBdatWrapper& bdat) {
    s_memberRscMobListRace = bdat.getMember("Race");
}

unsigned int getRscMobListRace(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListRace != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListRace, id, 1);
    }
    return 0;
}

void initRscMobListFootStep(const CBdatWrapper& bdat) {
    s_memberRscMobListFootStep = bdat.getMember("FootStep");
}

unsigned int getRscMobListFootStep(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListFootStep != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscMobListFootStep, id, 2);
    }
    return 0;
}

void initRscMobListFootStepEffect(const CBdatWrapper& bdat) {
    s_memberRscMobListFootStepEffect = bdat.getMember("FootStepEffect");
}

unsigned int getRscMobListFootStepEffect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListFootStepEffect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListFootStepEffect, id, 1);
    }
    return 0;
}

void initRscMobListOffsetID(const CBdatWrapper& bdat) {
    s_memberRscMobListOffsetID = bdat.getMember("OffsetID");
}

unsigned int getRscMobListOffsetID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListOffsetID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscMobListOffsetID, id, 2);
    }
    return 0;
}

void initRscMobListExtraParts1(const CBdatWrapper& bdat) {
    s_memberRscMobListExtraParts1 = bdat.getMember("ExtraParts1");
}

unsigned int getRscMobListExtraParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListExtraParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListExtraParts1, id, 1);
    }
    return 0;
}

void initRscMobListExtraParts2(const CBdatWrapper& bdat) {
    s_memberRscMobListExtraParts2 = bdat.getMember("ExtraParts2");
}

unsigned int getRscMobListExtraParts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListExtraParts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListExtraParts2, id, 1);
    }
    return 0;
}

void initRscMobListExtraParts3(const CBdatWrapper& bdat) {
    s_memberRscMobListExtraParts3 = bdat.getMember("ExtraParts3");
}

unsigned int getRscMobListExtraParts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListExtraParts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListExtraParts3, id, 1);
    }
    return 0;
}

void initRscMobListExtraParts4(const CBdatWrapper& bdat) {
    s_memberRscMobListExtraParts4 = bdat.getMember("ExtraParts4");
}

unsigned int getRscMobListExtraParts4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListExtraParts4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListExtraParts4, id, 1);
    }
    return 0;
}

void initRscMobListExtraParts5(const CBdatWrapper& bdat) {
    s_memberRscMobListExtraParts5 = bdat.getMember("ExtraParts5");
}

unsigned int getRscMobListExtraParts5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListExtraParts5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListExtraParts5, id, 1);
    }
    return 0;
}

void initRscMobListExtraParts6(const CBdatWrapper& bdat) {
    s_memberRscMobListExtraParts6 = bdat.getMember("ExtraParts6");
}

unsigned int getRscMobListExtraParts6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscMobListExtraParts6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRscMobListExtraParts6, id, 1);
    }
    return 0;
}

void initRSC_MapObjListModel(const CBdatWrapper& bdat) {
    s_memberRSC_MapObjListModel = bdat.getMember("Model");
}

const char* getRSC_MapObjListModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_MapObjListModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_MapObjListModel, id, 7);
    }
    return nullptr;
}

void initRSC_MapObjListMotion(const CBdatWrapper& bdat) {
    s_memberRSC_MapObjListMotion = bdat.getMember("Motion");
}

const char* getRSC_MapObjListMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_MapObjListMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_MapObjListMotion, id, 7);
    }
    return nullptr;
}

void initRSC_MapObjListComp_Eff(const CBdatWrapper& bdat) {
    s_memberRSC_MapObjListComp_Eff = bdat.getMember("Comp_Eff");
}

void initRSC_MapObjListSE(const CBdatWrapper& bdat) {
    s_memberRSC_MapObjListSE = bdat.getMember("SE");
}

void initRSC_MapObjListSeEnv(const CBdatWrapper& bdat) {
    s_memberRSC_MapObjListSeEnv = bdat.getMember("SeEnv");
}

void initRSC_MapObjListflagBigObj(const CBdatWrapper& bdat) {
    s_memberRSC_MapObjListflagBigObjFlag = bdat.getMember("flag");
    s_memberRSC_MapObjListflagBigObj = bdat.getMember("BigObj");
}

void initRSC_MapObjListExtraParts1(const CBdatWrapper& bdat) {
    s_memberRSC_MapObjListExtraParts1 = bdat.getMember("ExtraParts1");
}

unsigned int getRSC_MapObjListExtraParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_MapObjListExtraParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberRSC_MapObjListExtraParts1, id, 1);
    }
    return 0;
}

void initRSC_TboxListModel(const CBdatWrapper& bdat) {
    s_memberRSC_TboxListModel = bdat.getMember("Model");
}

const char* getRSC_TboxListModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_TboxListModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_TboxListModel, id, 7);
    }
    return nullptr;
}

void initRSC_TboxListMotion(const CBdatWrapper& bdat) {
    s_memberRSC_TboxListMotion = bdat.getMember("Motion");
}

const char* getRSC_TboxListMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_TboxListMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_TboxListMotion, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnModel(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnModel = bdat.getMember("Model");
}

const char* getRSC_PcWpnModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnModel, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMotion(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMotion = bdat.getMember("Motion");
}

const char* getRSC_PcWpnMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMotion, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMenuImageID(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMenuImageID = bdat.getMember("MenuImageID");
}

unsigned int getRSC_PcWpnMenuImageID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMenuImageID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRSC_PcWpnMenuImageID, id, 2);
    }
    return 0;
}

void initRSC_PcWpnMountWpn01rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn01rIn = bdat.getMember("Wpn01rIn");
}

const char* getRSC_PcWpnMountWpn01rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn01rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn01rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn01rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn01rOut = bdat.getMember("Wpn01rOut");
}

const char* getRSC_PcWpnMountWpn01rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn01rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn01rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn02rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn02rIn = bdat.getMember("Wpn02rIn");
}

const char* getRSC_PcWpnMountWpn02rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn02rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn02rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn02rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn02rOut = bdat.getMember("Wpn02rOut");
}

const char* getRSC_PcWpnMountWpn02rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn02rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn02rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn03rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn03rIn = bdat.getMember("Wpn03rIn");
}

const char* getRSC_PcWpnMountWpn03rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn03rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn03rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn03rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn03rOut = bdat.getMember("Wpn03rOut");
}

const char* getRSC_PcWpnMountWpn03rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn03rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn03rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn03lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn03lIn = bdat.getMember("Wpn03lIn");
}

const char* getRSC_PcWpnMountWpn03lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn03lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn03lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn03lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn03lOut = bdat.getMember("Wpn03lOut");
}

const char* getRSC_PcWpnMountWpn03lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn03lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn03lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn04rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn04rIn = bdat.getMember("Wpn04rIn");
}

const char* getRSC_PcWpnMountWpn04rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn04rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn04rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn04rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn04rOut = bdat.getMember("Wpn04rOut");
}

const char* getRSC_PcWpnMountWpn04rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn04rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn04rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn05rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn05rIn = bdat.getMember("Wpn05rIn");
}

const char* getRSC_PcWpnMountWpn05rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn05rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn05rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn05rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn05rOut = bdat.getMember("Wpn05rOut");
}

const char* getRSC_PcWpnMountWpn05rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn05rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn05rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn05lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn05lIn = bdat.getMember("Wpn05lIn");
}

const char* getRSC_PcWpnMountWpn05lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn05lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn05lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn05lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn05lOut = bdat.getMember("Wpn05lOut");
}

const char* getRSC_PcWpnMountWpn05lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn05lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn05lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn06rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn06rIn = bdat.getMember("Wpn06rIn");
}

const char* getRSC_PcWpnMountWpn06rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn06rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn06rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn06rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn06rOut = bdat.getMember("Wpn06rOut");
}

const char* getRSC_PcWpnMountWpn06rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn06rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn06rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn07rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn07rIn = bdat.getMember("Wpn07rIn");
}

const char* getRSC_PcWpnMountWpn07rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn07rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn07rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn07rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn07rOut = bdat.getMember("Wpn07rOut");
}

const char* getRSC_PcWpnMountWpn07rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn07rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn07rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn07lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn07lIn = bdat.getMember("Wpn07lIn");
}

const char* getRSC_PcWpnMountWpn07lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn07lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn07lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn07lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn07lOut = bdat.getMember("Wpn07lOut");
}

const char* getRSC_PcWpnMountWpn07lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn07lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn07lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn08rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn08rIn = bdat.getMember("Wpn08rIn");
}

const char* getRSC_PcWpnMountWpn08rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn08rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn08rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn08rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn08rOut = bdat.getMember("Wpn08rOut");
}

const char* getRSC_PcWpnMountWpn08rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn08rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn08rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn09rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn09rIn = bdat.getMember("Wpn09rIn");
}

const char* getRSC_PcWpnMountWpn09rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn09rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn09rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn09rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn09rOut = bdat.getMember("Wpn09rOut");
}

const char* getRSC_PcWpnMountWpn09rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn09rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn09rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn09lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn09lIn = bdat.getMember("Wpn09lIn");
}

const char* getRSC_PcWpnMountWpn09lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn09lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn09lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn09lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn09lOut = bdat.getMember("Wpn09lOut");
}

const char* getRSC_PcWpnMountWpn09lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn09lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn09lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn10rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn10rIn = bdat.getMember("Wpn10rIn");
}

const char* getRSC_PcWpnMountWpn10rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn10rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn10rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn10rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn10rOut = bdat.getMember("Wpn10rOut");
}

const char* getRSC_PcWpnMountWpn10rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn10rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn10rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn10lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn10lIn = bdat.getMember("Wpn10lIn");
}

const char* getRSC_PcWpnMountWpn10lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn10lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn10lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn10lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn10lOut = bdat.getMember("Wpn10lOut");
}

const char* getRSC_PcWpnMountWpn10lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn10lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn10lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn11rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn11rIn = bdat.getMember("Wpn11rIn");
}

const char* getRSC_PcWpnMountWpn11rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn11rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn11rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn11rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn11rOut = bdat.getMember("Wpn11rOut");
}

const char* getRSC_PcWpnMountWpn11rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn11rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn11rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn12rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn12rIn = bdat.getMember("Wpn12rIn");
}

const char* getRSC_PcWpnMountWpn12rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn12rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn12rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn12rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn12rOut = bdat.getMember("Wpn12rOut");
}

const char* getRSC_PcWpnMountWpn12rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn12rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn12rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn12lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn12lIn = bdat.getMember("Wpn12lIn");
}

const char* getRSC_PcWpnMountWpn12lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn12lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn12lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn12lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn12lOut = bdat.getMember("Wpn12lOut");
}

const char* getRSC_PcWpnMountWpn12lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn12lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn12lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn13rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn13rIn = bdat.getMember("Wpn13rIn");
}

const char* getRSC_PcWpnMountWpn13rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn13rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn13rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn13rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn13rOut = bdat.getMember("Wpn13rOut");
}

const char* getRSC_PcWpnMountWpn13rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn13rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn13rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn14rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn14rIn = bdat.getMember("Wpn14rIn");
}

const char* getRSC_PcWpnMountWpn14rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn14rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn14rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn14rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn14rOut = bdat.getMember("Wpn14rOut");
}

const char* getRSC_PcWpnMountWpn14rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn14rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn14rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn15rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn15rIn = bdat.getMember("Wpn15rIn");
}

const char* getRSC_PcWpnMountWpn15rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn15rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn15rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn15rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn15rOut = bdat.getMember("Wpn15rOut");
}

const char* getRSC_PcWpnMountWpn15rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn15rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn15rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn16rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn16rIn = bdat.getMember("Wpn16rIn");
}

const char* getRSC_PcWpnMountWpn16rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn16rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn16rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn16rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn16rOut = bdat.getMember("Wpn16rOut");
}

const char* getRSC_PcWpnMountWpn16rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn16rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn16rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn16lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn16lIn = bdat.getMember("Wpn16lIn");
}

const char* getRSC_PcWpnMountWpn16lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn16lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn16lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn16lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn16lOut = bdat.getMember("Wpn16lOut");
}

const char* getRSC_PcWpnMountWpn16lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn16lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn16lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn17rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn17rIn = bdat.getMember("Wpn17rIn");
}

const char* getRSC_PcWpnMountWpn17rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn17rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn17rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn17rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn17rOut = bdat.getMember("Wpn17rOut");
}

const char* getRSC_PcWpnMountWpn17rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn17rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn17rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn18rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn18rIn = bdat.getMember("Wpn18rIn");
}

const char* getRSC_PcWpnMountWpn18rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn18rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn18rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn18rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn18rOut = bdat.getMember("Wpn18rOut");
}

const char* getRSC_PcWpnMountWpn18rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn18rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn18rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn19rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn19rIn = bdat.getMember("Wpn19rIn");
}

const char* getRSC_PcWpnMountWpn19rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn19rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn19rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn19rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn19rOut = bdat.getMember("Wpn19rOut");
}

const char* getRSC_PcWpnMountWpn19rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn19rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn19rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn20rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn20rIn = bdat.getMember("Wpn20rIn");
}

const char* getRSC_PcWpnMountWpn20rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn20rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn20rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn20rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn20rOut = bdat.getMember("Wpn20rOut");
}

const char* getRSC_PcWpnMountWpn20rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn20rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn20rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn20lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn20lIn = bdat.getMember("Wpn20lIn");
}

const char* getRSC_PcWpnMountWpn20lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn20lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn20lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn20lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn20lOut = bdat.getMember("Wpn20lOut");
}

const char* getRSC_PcWpnMountWpn20lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn20lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn20lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn21rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn21rIn = bdat.getMember("Wpn21rIn");
}

const char* getRSC_PcWpnMountWpn21rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn21rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn21rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn21rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn21rOut = bdat.getMember("Wpn21rOut");
}

const char* getRSC_PcWpnMountWpn21rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn21rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn21rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn22rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn22rIn = bdat.getMember("Wpn22rIn");
}

const char* getRSC_PcWpnMountWpn22rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn22rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn22rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn22rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn22rOut = bdat.getMember("Wpn22rOut");
}

const char* getRSC_PcWpnMountWpn22rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn22rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn22rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn22lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn22lIn = bdat.getMember("Wpn22lIn");
}

const char* getRSC_PcWpnMountWpn22lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn22lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn22lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn22lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn22lOut = bdat.getMember("Wpn22lOut");
}

const char* getRSC_PcWpnMountWpn22lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn22lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn22lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn23rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn23rIn = bdat.getMember("Wpn23rIn");
}

const char* getRSC_PcWpnMountWpn23rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn23rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn23rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn23rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn23rOut = bdat.getMember("Wpn23rOut");
}

const char* getRSC_PcWpnMountWpn23rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn23rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn23rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn23lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn23lIn = bdat.getMember("Wpn23lIn");
}

const char* getRSC_PcWpnMountWpn23lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn23lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn23lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn23lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn23lOut = bdat.getMember("Wpn23lOut");
}

const char* getRSC_PcWpnMountWpn23lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn23lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn23lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn24rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn24rIn = bdat.getMember("Wpn24rIn");
}

const char* getRSC_PcWpnMountWpn24rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn24rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn24rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn24rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn24rOut = bdat.getMember("Wpn24rOut");
}

const char* getRSC_PcWpnMountWpn24rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn24rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn24rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn24lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn24lIn = bdat.getMember("Wpn24lIn");
}

const char* getRSC_PcWpnMountWpn24lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn24lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn24lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn24lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn24lOut = bdat.getMember("Wpn24lOut");
}

const char* getRSC_PcWpnMountWpn24lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn24lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn24lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn25rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn25rIn = bdat.getMember("Wpn25rIn");
}

const char* getRSC_PcWpnMountWpn25rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn25rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn25rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn25rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn25rOut = bdat.getMember("Wpn25rOut");
}

const char* getRSC_PcWpnMountWpn25rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn25rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn25rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn25lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn25lIn = bdat.getMember("Wpn25lIn");
}

const char* getRSC_PcWpnMountWpn25lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn25lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn25lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn25lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn25lOut = bdat.getMember("Wpn25lOut");
}

const char* getRSC_PcWpnMountWpn25lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn25lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn25lOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn26rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn26rIn = bdat.getMember("Wpn26rIn");
}

const char* getRSC_PcWpnMountWpn26rIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn26rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn26rIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn26rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn26rOut = bdat.getMember("Wpn26rOut");
}

const char* getRSC_PcWpnMountWpn26rOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn26rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn26rOut, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn26lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn26lIn = bdat.getMember("Wpn26lIn");
}

const char* getRSC_PcWpnMountWpn26lIn(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn26lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn26lIn, id, 7);
    }
    return nullptr;
}

void initRSC_PcWpnMountWpn26lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn26lOut = bdat.getMember("Wpn26lOut");
}

const char* getRSC_PcWpnMountWpn26lOut(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn26lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn26lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn28rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn28rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn28rIn = bdat.getMember("Wpn28rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn28rIn column (const char*) of a row, as the init function above found it.
const char* fn_71002105F8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn28rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn28rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn28rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn28rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn28rOut = bdat.getMember("Wpn28rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn28rOut column (const char*) of a row, as the init function above found it.
const char* fn_710021067C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn28rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn28rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn28lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn28lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn28lIn = bdat.getMember("Wpn28lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn28lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210700(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn28lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn28lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn28lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn28lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn28lOut = bdat.getMember("Wpn28lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn28lOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210784(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn28lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn28lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn29rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn29rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn29rIn = bdat.getMember("Wpn29rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn29rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210808(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn29rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn29rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn29rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn29rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn29rOut = bdat.getMember("Wpn29rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn29rOut column (const char*) of a row, as the init function above found it.
const char* fn_710021088C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn29rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn29rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn29lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn29lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn29lIn = bdat.getMember("Wpn29lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn29lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210910(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn29lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn29lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn29lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn29lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn29lOut = bdat.getMember("Wpn29lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn29lOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210994(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn29lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn29lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn30rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn30rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn30rIn = bdat.getMember("Wpn30rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn30rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210A18(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn30rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn30rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn30rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn30rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn30rOut = bdat.getMember("Wpn30rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn30rOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210A9C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn30rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn30rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn30lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn30lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn30lIn = bdat.getMember("Wpn30lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn30lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210B20(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn30lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn30lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn30lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn30lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn30lOut = bdat.getMember("Wpn30lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn30lOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210BA4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn30lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn30lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn31rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn31rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn31rIn = bdat.getMember("Wpn31rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn31rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210C28(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn31rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn31rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn31rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn31rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn31rOut = bdat.getMember("Wpn31rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn31rOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210CAC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn31rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn31rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn31lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn31lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn31lIn = bdat.getMember("Wpn31lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn31lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210D30(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn31lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn31lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn31lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn31lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn31lOut = bdat.getMember("Wpn31lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn31lOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210DB4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn31lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn31lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn32rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn32rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn32rIn = bdat.getMember("Wpn32rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn32rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210E38(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn32rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn32rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn32rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn32rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn32rOut = bdat.getMember("Wpn32rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn32rOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210EBC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn32rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn32rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn32lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn32lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn32lIn = bdat.getMember("Wpn32lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn32lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100210F40(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn32lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn32lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn32lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn32lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn32lOut = bdat.getMember("Wpn32lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn32lOut column (const char*) of a row, as the init function above found it.
const char* fn_7100210FC4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn32lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn32lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn33rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn33rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn33rIn = bdat.getMember("Wpn33rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn33rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100211048(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn33rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn33rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn33rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn33rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn33rOut = bdat.getMember("Wpn33rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn33rOut column (const char*) of a row, as the init function above found it.
const char* fn_71002110CC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn33rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn33rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn33lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn33lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn33lIn = bdat.getMember("Wpn33lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn33lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100211150(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn33lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn33lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn33lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn33lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn33lOut = bdat.getMember("Wpn33lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn33lOut column (const char*) of a row, as the init function above found it.
const char* fn_71002111D4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn33lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn33lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn34rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn34rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn34rIn = bdat.getMember("Wpn34rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn34rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100211258(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn34rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn34rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn34rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn34rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn34rOut = bdat.getMember("Wpn34rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn34rOut column (const char*) of a row, as the init function above found it.
const char* fn_71002112DC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn34rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn34rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn34lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn34lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn34lIn = bdat.getMember("Wpn34lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn34lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100211360(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn34lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn34lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn34lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn34lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn34lOut = bdat.getMember("Wpn34lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn34lOut column (const char*) of a row, as the init function above found it.
const char* fn_71002113E4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn34lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn34lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn35rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn35rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn35rIn = bdat.getMember("Wpn35rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn35rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100211468(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn35rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn35rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn35rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn35rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn35rOut = bdat.getMember("Wpn35rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn35rOut column (const char*) of a row, as the init function above found it.
const char* fn_71002114EC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn35rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn35rOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn35lIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn35lIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn35lIn = bdat.getMember("Wpn35lIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn35lIn column (const char*) of a row, as the init function above found it.
const char* fn_7100211570(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn35lIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn35lIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn35lOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn35lOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn35lOut = bdat.getMember("Wpn35lOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn35lOut column (const char*) of a row, as the init function above found it.
const char* fn_71002115F4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn35lOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn35lOut, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn36rIn accessors (the name is not the original's)
void initRSC_PcWpnMountWpn36rIn(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn36rIn = bdat.getMember("Wpn36rIn");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn36rIn column (const char*) of a row, as the init function above found it.
const char* fn_7100211678(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn36rIn != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn36rIn, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no RSC_PcWpnMountWpn36rOut accessors (the name is not the original's)
void initRSC_PcWpnMountWpn36rOut(const CBdatWrapper& bdat) {
    s_memberRSC_PcWpnMountWpn36rOut = bdat.getMember("Wpn36rOut");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of RSC_PcWpnMount getters holds it.
// What it does: reads the Wpn36rOut column (const char*) of a row, as the init function above found it.
const char* fn_71002116FC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRSC_PcWpnMountWpn36rOut != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRSC_PcWpnMountWpn36rOut, id, 7);
    }
    return nullptr;
}

void initRscEnWpnModel(const CBdatWrapper& bdat) {
    s_memberRscEnWpnModel = bdat.getMember("Model");
}

const char* getRscEnWpnModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWpnModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnWpnModel, id, 7);
    }
    return nullptr;
}

void initRscEnWpnScale(const CBdatWrapper& bdat) {
    s_memberRscEnWpnScale = bdat.getMember("Scale");
}

unsigned int getRscEnWpnScale(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWpnScale != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberRscEnWpnScale, id, 2);
    }
    return 0;
}

void initRscEnWpnMotion(const CBdatWrapper& bdat) {
    s_memberRscEnWpnMotion = bdat.getMember("Motion");
}

const char* getRscEnWpnMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWpnMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnWpnMotion, id, 7);
    }
    return nullptr;
}

void initRscEnWpnMtpInChara(const CBdatWrapper& bdat) {
    s_memberRscEnWpnMtpInChara = bdat.getMember("MtpInChara");
}

const char* getRscEnWpnMtpInChara(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWpnMtpInChara != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnWpnMtpInChara, id, 7);
    }
    return nullptr;
}

void initRscEnWpnMtpInWpn(const CBdatWrapper& bdat) {
    s_memberRscEnWpnMtpInWpn = bdat.getMember("MtpInWpn");
}

void initRscEnWpnMtpOutChara(const CBdatWrapper& bdat) {
    s_memberRscEnWpnMtpOutChara = bdat.getMember("MtpOutChara");
}

const char* getRscEnWpnMtpOutChara(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscEnWpnMtpOutChara != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscEnWpnMtpOutChara, id, 7);
    }
    return nullptr;
}

void initRscEnWpnMtpOutWpn(const CBdatWrapper& bdat) {
    s_memberRscEnWpnMtpOutWpn = bdat.getMember("MtpOutWpn");
}

void initRscNpcWpnModel(const CBdatWrapper& bdat) {
    s_memberRscNpcWpnModel = bdat.getMember("Model");
}

const char* getRscNpcWpnModel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcWpnModel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscNpcWpnModel, id, 7);
    }
    return nullptr;
}

void initRscNpcWpnMotion(const CBdatWrapper& bdat) {
    s_memberRscNpcWpnMotion = bdat.getMember("Motion");
}

const char* getRscNpcWpnMotion(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberRscNpcWpnMotion != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberRscNpcWpnMotion, id, 7);
    }
    return nullptr;
}

void initDriverParamExtMountNpc(const CBdatWrapper& bdat) {
    s_memberDriverParamExtMountNpc = bdat.getMember("ExtMountNpc");
}

unsigned int getDriverParamExtMountNpc(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberDriverParamExtMountNpc != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberDriverParamExtMountNpc, id, 2);
    }
    return 0;
}

void initDriverParamExtMountBone(const CBdatWrapper& bdat) {
    s_memberDriverParamExtMountBone = bdat.getMember("ExtMountBone");
}

const char* getDriverParamExtMountBone(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberDriverParamExtMountBone != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberDriverParamExtMountBone, id, 7);
    }
    return nullptr;
}

void initDriverParamExtMountCond(const CBdatWrapper& bdat) {
    s_memberDriverParamExtMountCond = bdat.getMember("ExtMountCond");
}

unsigned int getDriverParamExtMountCond(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberDriverParamExtMountCond != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberDriverParamExtMountCond, id, 2);
    }
    return 0;
}

void initVoiceTableDriver1(const CBdatWrapper& bdat) {
    s_memberVoiceTableDriver1 = bdat.getMember("Driver1");
}

const char* getVoiceTableDriver1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableDriver1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableDriver1, id, 7);
    }
    return nullptr;
}

void initVoiceTableDriver2(const CBdatWrapper& bdat) {
    s_memberVoiceTableDriver2 = bdat.getMember("Driver2");
}

const char* getVoiceTableDriver2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableDriver2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableDriver2, id, 7);
    }
    return nullptr;
}

void initVoiceTableDriver3(const CBdatWrapper& bdat) {
    s_memberVoiceTableDriver3 = bdat.getMember("Driver3");
}

const char* getVoiceTableDriver3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableDriver3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableDriver3, id, 7);
    }
    return nullptr;
}

void initVoiceTableDriver4(const CBdatWrapper& bdat) {
    s_memberVoiceTableDriver4 = bdat.getMember("Driver4");
}

const char* getVoiceTableDriver4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableDriver4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableDriver4, id, 7);
    }
    return nullptr;
}

void initVoiceTableDriver5(const CBdatWrapper& bdat) {
    s_memberVoiceTableDriver5 = bdat.getMember("Driver5");
}

const char* getVoiceTableDriver5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableDriver5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableDriver5, id, 7);
    }
    return nullptr;
}

void initVoiceTableDriver6(const CBdatWrapper& bdat) {
    s_memberVoiceTableDriver6 = bdat.getMember("Driver6");
}

const char* getVoiceTableDriver6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableDriver6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableDriver6, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra1 accessors (the name is not the original's)
void initVoiceTableIra1(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra1 = bdat.getMember("Ira1");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira1 column (const char*) of a row, as the init function above found it.
const char* fn_7100211A98(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra1, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra2 accessors (the name is not the original's)
void initVoiceTableIra2(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra2 = bdat.getMember("Ira2");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira2 column (const char*) of a row, as the init function above found it.
const char* fn_7100211B1C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra2, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra3 accessors (the name is not the original's)
void initVoiceTableIra3(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra3 = bdat.getMember("Ira3");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira3 column (const char*) of a row, as the init function above found it.
const char* fn_7100211BA0(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra3, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra4 accessors (the name is not the original's)
void initVoiceTableIra4(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra4 = bdat.getMember("Ira4");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira4 column (const char*) of a row, as the init function above found it.
const char* fn_7100211C24(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra4, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra5 accessors (the name is not the original's)
void initVoiceTableIra5(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra5 = bdat.getMember("Ira5");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira5 column (const char*) of a row, as the init function above found it.
const char* fn_7100211CA8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra5, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra6 accessors (the name is not the original's)
void initVoiceTableIra6(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra6 = bdat.getMember("Ira6");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira6 column (const char*) of a row, as the init function above found it.
const char* fn_7100211D2C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra6, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra7 accessors (the name is not the original's)
void initVoiceTableIra7(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra7 = bdat.getMember("Ira7");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira7 column (const char*) of a row, as the init function above found it.
const char* fn_7100211DB0(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra7, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra8 accessors (the name is not the original's)
void initVoiceTableIra8(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra8 = bdat.getMember("Ira8");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira8 column (const char*) of a row, as the init function above found it.
const char* fn_7100211E34(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra8, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableIra9 accessors (the name is not the original's)
void initVoiceTableIra9(const CBdatWrapper& bdat) {
    s_memberVoiceTableIra9 = bdat.getMember("Ira9");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTable getters holds it.
// What it does: reads the Ira9 column (const char*) of a row, as the init function above found it.
const char* fn_7100211EB8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableIra9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableIra9, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade1(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade1 = bdat.getMember("Blade1");
}

const char* getVoiceTableBladeBlade1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade1, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade2(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade2 = bdat.getMember("Blade2");
}

const char* getVoiceTableBladeBlade2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade2, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade3(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade3 = bdat.getMember("Blade3");
}

const char* getVoiceTableBladeBlade3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade3, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade4(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade4 = bdat.getMember("Blade4");
}

const char* getVoiceTableBladeBlade4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade4, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade5(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade5 = bdat.getMember("Blade5");
}

const char* getVoiceTableBladeBlade5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade5, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade6(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade6 = bdat.getMember("Blade6");
}

const char* getVoiceTableBladeBlade6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade6, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade7(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade7 = bdat.getMember("Blade7");
}

const char* getVoiceTableBladeBlade7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade7, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade8(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade8 = bdat.getMember("Blade8");
}

const char* getVoiceTableBladeBlade8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade8, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade9(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade9 = bdat.getMember("Blade9");
}

const char* getVoiceTableBladeBlade9(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade9, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade10(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade10 = bdat.getMember("Blade10");
}

const char* getVoiceTableBladeBlade10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade10, id, 7);
    }
    return nullptr;
}

void initVoiceTableBladeBlade11(const CBdatWrapper& bdat) {
    s_memberVoiceTableBladeBlade11 = bdat.getMember("Blade11");
}

const char* getVoiceTableBladeBlade11(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableBladeBlade11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableBladeBlade11, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade1(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade1 = bdat.getMember("RareBlade1");
}

const char* getVoiceTableRareRareBlade1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade1, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade2(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade2 = bdat.getMember("RareBlade2");
}

const char* getVoiceTableRareRareBlade2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade2, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade3(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade3 = bdat.getMember("RareBlade3");
}

const char* getVoiceTableRareRareBlade3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade3, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade4(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade4 = bdat.getMember("RareBlade4");
}

const char* getVoiceTableRareRareBlade4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade4, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade5(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade5 = bdat.getMember("RareBlade5");
}

const char* getVoiceTableRareRareBlade5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade5, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade6(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade6 = bdat.getMember("RareBlade6");
}

const char* getVoiceTableRareRareBlade6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade6, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade7(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade7 = bdat.getMember("RareBlade7");
}

const char* getVoiceTableRareRareBlade7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade7, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade8(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade8 = bdat.getMember("RareBlade8");
}

const char* getVoiceTableRareRareBlade8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade8, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade9(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade9 = bdat.getMember("RareBlade9");
}

const char* getVoiceTableRareRareBlade9(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade9, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade10(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade10 = bdat.getMember("RareBlade10");
}

const char* getVoiceTableRareRareBlade10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade10, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade11(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade11 = bdat.getMember("RareBlade11");
}

const char* getVoiceTableRareRareBlade11(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade11, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade12(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade12 = bdat.getMember("RareBlade12");
}

const char* getVoiceTableRareRareBlade12(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade12, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade13(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade13 = bdat.getMember("RareBlade13");
}

const char* getVoiceTableRareRareBlade13(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade13 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade13, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade14(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade14 = bdat.getMember("RareBlade14");
}

const char* getVoiceTableRareRareBlade14(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade14 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade14, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade15(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade15 = bdat.getMember("RareBlade15");
}

const char* getVoiceTableRareRareBlade15(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade15 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade15, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade16(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade16 = bdat.getMember("RareBlade16");
}

const char* getVoiceTableRareRareBlade16(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade16 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade16, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade17(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade17 = bdat.getMember("RareBlade17");
}

const char* getVoiceTableRareRareBlade17(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade17 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade17, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade18(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade18 = bdat.getMember("RareBlade18");
}

const char* getVoiceTableRareRareBlade18(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade18 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade18, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade19(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade19 = bdat.getMember("RareBlade19");
}

const char* getVoiceTableRareRareBlade19(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade19 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade19, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade20(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade20 = bdat.getMember("RareBlade20");
}

const char* getVoiceTableRareRareBlade20(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade20 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade20, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade21(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade21 = bdat.getMember("RareBlade21");
}

const char* getVoiceTableRareRareBlade21(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade21 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade21, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade22(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade22 = bdat.getMember("RareBlade22");
}

const char* getVoiceTableRareRareBlade22(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade22 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade22, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade23(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade23 = bdat.getMember("RareBlade23");
}

const char* getVoiceTableRareRareBlade23(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade23 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade23, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade24(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade24 = bdat.getMember("RareBlade24");
}

const char* getVoiceTableRareRareBlade24(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade24 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade24, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade25(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade25 = bdat.getMember("RareBlade25");
}

const char* getVoiceTableRareRareBlade25(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade25 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade25, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade26(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade26 = bdat.getMember("RareBlade26");
}

const char* getVoiceTableRareRareBlade26(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade26 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade26, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade27(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade27 = bdat.getMember("RareBlade27");
}

const char* getVoiceTableRareRareBlade27(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade27 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade27, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade28(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade28 = bdat.getMember("RareBlade28");
}

const char* getVoiceTableRareRareBlade28(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade28 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade28, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade29(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade29 = bdat.getMember("RareBlade29");
}

const char* getVoiceTableRareRareBlade29(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade29 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade29, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade30(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade30 = bdat.getMember("RareBlade30");
}

const char* getVoiceTableRareRareBlade30(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade30 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade30, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade31(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade31 = bdat.getMember("RareBlade31");
}

const char* getVoiceTableRareRareBlade31(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade31 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade31, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade32(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade32 = bdat.getMember("RareBlade32");
}

const char* getVoiceTableRareRareBlade32(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade32 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade32, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade33(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade33 = bdat.getMember("RareBlade33");
}

const char* getVoiceTableRareRareBlade33(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade33 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade33, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade34(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade34 = bdat.getMember("RareBlade34");
}

const char* getVoiceTableRareRareBlade34(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade34 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade34, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade35(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade35 = bdat.getMember("RareBlade35");
}

const char* getVoiceTableRareRareBlade35(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade35 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade35, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade36(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade36 = bdat.getMember("RareBlade36");
}

const char* getVoiceTableRareRareBlade36(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade36 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade36, id, 7);
    }
    return nullptr;
}

void initVoiceTableRareRareBlade37(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade37 = bdat.getMember("RareBlade37");
}

const char* getVoiceTableRareRareBlade37(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade37 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade37, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableRareRareBlade38 accessors (the name is not the original's)
void initVoiceTableRareRareBlade38(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade38 = bdat.getMember("RareBlade38");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTableRare getters holds it.
// What it does: reads the RareBlade38 column (const char*) of a row, as the init function above found it.
const char* fn_71002137FC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade38 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade38, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableRareRareBlade39 accessors (the name is not the original's)
void initVoiceTableRareRareBlade39(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade39 = bdat.getMember("RareBlade39");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTableRare getters holds it.
// What it does: reads the RareBlade39 column (const char*) of a row, as the init function above found it.
const char* fn_7100213880(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade39 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade39, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableRareRareBlade40 accessors (the name is not the original's)
void initVoiceTableRareRareBlade40(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade40 = bdat.getMember("RareBlade40");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTableRare getters holds it.
// What it does: reads the RareBlade40 column (const char*) of a row, as the init function above found it.
const char* fn_7100213904(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade40 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade40, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableRareRareBlade41 accessors (the name is not the original's)
void initVoiceTableRareRareBlade41(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade41 = bdat.getMember("RareBlade41");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTableRare getters holds it.
// What it does: reads the RareBlade41 column (const char*) of a row, as the init function above found it.
const char* fn_7100213988(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade41 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade41, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableRareRareBlade42 accessors (the name is not the original's)
void initVoiceTableRareRareBlade42(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade42 = bdat.getMember("RareBlade42");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTableRare getters holds it.
// What it does: reads the RareBlade42 column (const char*) of a row, as the init function above found it.
const char* fn_7100213A0C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade42 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade42, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableRareRareBlade43 accessors (the name is not the original's)
void initVoiceTableRareRareBlade43(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade43 = bdat.getMember("RareBlade43");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTableRare getters holds it.
// What it does: reads the RareBlade43 column (const char*) of a row, as the init function above found it.
const char* fn_7100213A90(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade43 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade43, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no VoiceTableRareRareBlade44 accessors (the name is not the original's)
void initVoiceTableRareRareBlade44(const CBdatWrapper& bdat) {
    s_memberVoiceTableRareRareBlade44 = bdat.getMember("RareBlade44");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; the table of VoiceTableRare getters holds it.
// What it does: reads the RareBlade44 column (const char*) of a row, as the init function above found it.
const char* fn_7100213B14(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableRareRareBlade44 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableRareRareBlade44, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade1(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade1 = bdat.getMember("CommonBlade1");
}

const char* getVoiceTableCommonCommonBlade1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade1, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade2(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade2 = bdat.getMember("CommonBlade2");
}

const char* getVoiceTableCommonCommonBlade2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade2, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade3(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade3 = bdat.getMember("CommonBlade3");
}

const char* getVoiceTableCommonCommonBlade3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade3, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade4(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade4 = bdat.getMember("CommonBlade4");
}

const char* getVoiceTableCommonCommonBlade4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade4, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade5(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade5 = bdat.getMember("CommonBlade5");
}

const char* getVoiceTableCommonCommonBlade5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade5, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade6(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade6 = bdat.getMember("CommonBlade6");
}

const char* getVoiceTableCommonCommonBlade6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade6, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade7(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade7 = bdat.getMember("CommonBlade7");
}

const char* getVoiceTableCommonCommonBlade7(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade7, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade8(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade8 = bdat.getMember("CommonBlade8");
}

const char* getVoiceTableCommonCommonBlade8(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade8, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade9(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade9 = bdat.getMember("CommonBlade9");
}

const char* getVoiceTableCommonCommonBlade9(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade9, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade10(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade10 = bdat.getMember("CommonBlade10");
}

const char* getVoiceTableCommonCommonBlade10(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade10, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade11(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade11 = bdat.getMember("CommonBlade11");
}

const char* getVoiceTableCommonCommonBlade11(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade11, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade12(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade12 = bdat.getMember("CommonBlade12");
}

const char* getVoiceTableCommonCommonBlade12(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade12, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade13(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade13 = bdat.getMember("CommonBlade13");
}

const char* getVoiceTableCommonCommonBlade13(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade13 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade13, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade14(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade14 = bdat.getMember("CommonBlade14");
}

const char* getVoiceTableCommonCommonBlade14(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade14 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade14, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade15(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade15 = bdat.getMember("CommonBlade15");
}

const char* getVoiceTableCommonCommonBlade15(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade15 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade15, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade16(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade16 = bdat.getMember("CommonBlade16");
}

const char* getVoiceTableCommonCommonBlade16(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade16 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade16, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade17(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade17 = bdat.getMember("CommonBlade17");
}

const char* getVoiceTableCommonCommonBlade17(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade17 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade17, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade18(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade18 = bdat.getMember("CommonBlade18");
}

const char* getVoiceTableCommonCommonBlade18(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade18 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade18, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade19(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade19 = bdat.getMember("CommonBlade19");
}

const char* getVoiceTableCommonCommonBlade19(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade19 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade19, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade20(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade20 = bdat.getMember("CommonBlade20");
}

const char* getVoiceTableCommonCommonBlade20(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade20 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade20, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade21(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade21 = bdat.getMember("CommonBlade21");
}

const char* getVoiceTableCommonCommonBlade21(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade21 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade21, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade22(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade22 = bdat.getMember("CommonBlade22");
}

const char* getVoiceTableCommonCommonBlade22(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade22 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade22, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade23(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade23 = bdat.getMember("CommonBlade23");
}

const char* getVoiceTableCommonCommonBlade23(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade23 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade23, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade24(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade24 = bdat.getMember("CommonBlade24");
}

const char* getVoiceTableCommonCommonBlade24(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade24 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade24, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade25(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade25 = bdat.getMember("CommonBlade25");
}

const char* getVoiceTableCommonCommonBlade25(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade25 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade25, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade26(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade26 = bdat.getMember("CommonBlade26");
}

const char* getVoiceTableCommonCommonBlade26(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade26 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade26, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade27(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade27 = bdat.getMember("CommonBlade27");
}

const char* getVoiceTableCommonCommonBlade27(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade27 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade27, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade28(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade28 = bdat.getMember("CommonBlade28");
}

const char* getVoiceTableCommonCommonBlade28(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade28 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade28, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade29(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade29 = bdat.getMember("CommonBlade29");
}

const char* getVoiceTableCommonCommonBlade29(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade29 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade29, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade30(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade30 = bdat.getMember("CommonBlade30");
}

const char* getVoiceTableCommonCommonBlade30(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade30 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade30, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade31(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade31 = bdat.getMember("CommonBlade31");
}

const char* getVoiceTableCommonCommonBlade31(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade31 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade31, id, 7);
    }
    return nullptr;
}

void initVoiceTableCommonCommonBlade32(const CBdatWrapper& bdat) {
    s_memberVoiceTableCommonCommonBlade32 = bdat.getMember("CommonBlade32");
}

const char* getVoiceTableCommonCommonBlade32(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVoiceTableCommonCommonBlade32 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVoiceTableCommonCommonBlade32, id, 7);
    }
    return nullptr;
}

void initFLD_actorSELOD(const CBdatWrapper& bdat) {
    s_memberFLD_actorSELOD = bdat.getMember("LOD");
}

const char* getFLD_actorSELOD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSELOD != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberFLD_actorSELOD, id, 7);
    }
    return nullptr;
}

void initFLD_actorSEse_type(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEse_type = bdat.getMember("se_type");
}

unsigned int getFLD_actorSEse_type(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEse_type != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFLD_actorSEse_type, id, 1);
    }
    return 0;
}

void initFLD_actorSEseName(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEseName = bdat.getMember("seName");
}

unsigned int getFLD_actorSEseName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEseName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberFLD_actorSEseName, id, 2);
    }
    return 0;
}

void initFLD_actorSEmax_volume_Dist(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEmax_volume_Dist = bdat.getMember("max_volume_Dist");
}

float getFLD_actorSEmax_volume_Dist(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEmax_volume_Dist != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberFLD_actorSEmax_volume_Dist, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initFLD_actorSEmin_volume_Dist(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEmin_volume_Dist = bdat.getMember("min_volume_Dist");
}

float getFLD_actorSEmin_volume_Dist(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEmin_volume_Dist != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberFLD_actorSEmin_volume_Dist, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initFLD_actorSEvolumeMAX(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEvolumeMAX = bdat.getMember("volumeMAX");
}

unsigned int getFLD_actorSEvolumeMAX(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEvolumeMAX != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFLD_actorSEvolumeMAX, id, 1);
    }
    return 0;
}

void initFLD_actorSEvolumeMIN(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEvolumeMIN = bdat.getMember("volumeMIN");
}

unsigned int getFLD_actorSEvolumeMIN(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEvolumeMIN != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberFLD_actorSEvolumeMIN, id, 1);
    }
    return 0;
}

void initFLD_actorSEoffsetX(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEoffsetX = bdat.getMember("offsetX");
}

float getFLD_actorSEoffsetX(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEoffsetX != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberFLD_actorSEoffsetX, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initFLD_actorSEoffsetY(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEoffsetY = bdat.getMember("offsetY");
}

float getFLD_actorSEoffsetY(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEoffsetY != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberFLD_actorSEoffsetY, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initFLD_actorSEoffsetZ(const CBdatWrapper& bdat) {
    s_memberFLD_actorSEoffsetZ = bdat.getMember("offsetZ");
}

float getFLD_actorSEoffsetZ(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberFLD_actorSEoffsetZ != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberFLD_actorSEoffsetZ, id, 8);
        return val.value;
    }
    return 0.0f;
}

// 3.0.1's column: 1.0.0 has no NoRetargetAnoRetarget accessors (the name is not the original's)
void initNoRetargetAnoRetarget(const CBdatWrapper& bdat) {
    s_memberNoRetargetAnoRetarget = bdat.getMember("noRetarget");
}

// 3.0.1's column: 1.0.0 has no NoRetargetBnoRetarget accessors (the name is not the original's)
void initNoRetargetBnoRetarget(const CBdatWrapper& bdat) {
    s_memberNoRetargetBnoRetarget = bdat.getMember("noRetarget");
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data, null checks kept): clang 3.9 makes a static table constant unless its address is passed on before inlining,
// so its slot getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbrs

GfBdatRsc::GfBdatRsc() {
    m_fpRscEn = nullptr;
    m_fpRscEnGenus = nullptr;
    m_fpRscEnUnd = nullptr;
    m_fpRscNpcList = nullptr;
    m_fpRscNpcWpn = nullptr;
    m_fpRscMobList = nullptr;
    m_fpRSC_PcWpn = nullptr;
    m_fpRSC_PcWpnMount = nullptr;
    m_fpRscEnWpn = nullptr;
    m_fpRSC_TboxList = nullptr;
    m_fpRSC_MapObjList = nullptr;
    m_fpDriverParam = nullptr;
    m_fpVoiceTable = nullptr;
    m_fpVoiceTableBlade = nullptr;
    m_fpVoiceTableRare = nullptr;
    m_fpVoiceTableCommon = nullptr;
    m_fpFLD_actorSE = nullptr;
    m_fpNoRetargetA = nullptr;
    m_fpNoRetargetB = nullptr;
    bdatRefresh();
}

GfBdatRsc::~GfBdatRsc() {
    destroyFP();
}

void GfBdatRsc::destroyFP() {
    if (m_fpRscEn != nullptr) {
        delete m_fpRscEn;
        m_fpRscEn = nullptr;
    }
    if (m_fpRscEnGenus != nullptr) {
        delete m_fpRscEnGenus;
        m_fpRscEnGenus = nullptr;
    }
    if (m_fpRscEnUnd != nullptr) {
        delete m_fpRscEnUnd;
        m_fpRscEnUnd = nullptr;
    }
    if (m_fpRscNpcList != nullptr) {
        delete m_fpRscNpcList;
        m_fpRscNpcList = nullptr;
    }
    if (m_fpRscNpcWpn != nullptr) {
        delete m_fpRscNpcWpn;
        m_fpRscNpcWpn = nullptr;
    }
    if (m_fpRscMobList != nullptr) {
        delete m_fpRscMobList;
        m_fpRscMobList = nullptr;
    }
    if (m_fpRSC_PcWpn != nullptr) {
        delete m_fpRSC_PcWpn;
        m_fpRSC_PcWpn = nullptr;
    }
    if (m_fpRSC_PcWpnMount != nullptr) {
        delete m_fpRSC_PcWpnMount;
        m_fpRSC_PcWpnMount = nullptr;
    }
    if (m_fpRscEnWpn != nullptr) {
        delete m_fpRscEnWpn;
        m_fpRscEnWpn = nullptr;
    }
    if (m_fpRSC_TboxList != nullptr) {
        delete m_fpRSC_TboxList;
        m_fpRSC_TboxList = nullptr;
    }
    if (m_fpRSC_MapObjList != nullptr) {
        delete m_fpRSC_MapObjList;
        m_fpRSC_MapObjList = nullptr;
    }
    if (m_fpDriverParam != nullptr) {
        delete m_fpDriverParam;
        m_fpDriverParam = nullptr;
    }
    if (m_fpVoiceTable != nullptr) {
        delete m_fpVoiceTable;
        m_fpVoiceTable = nullptr;
    }
    if (m_fpVoiceTableBlade != nullptr) {
        delete m_fpVoiceTableBlade;
        m_fpVoiceTableBlade = nullptr;
    }
    if (m_fpVoiceTableRare != nullptr) {
        delete m_fpVoiceTableRare;
        m_fpVoiceTableRare = nullptr;
    }
    if (m_fpVoiceTableCommon != nullptr) {
        delete m_fpVoiceTableCommon;
        m_fpVoiceTableCommon = nullptr;
    }
    if (m_fpFLD_actorSE != nullptr) {
        delete m_fpFLD_actorSE;
        m_fpFLD_actorSE = nullptr;
    }
    if (m_fpNoRetargetA != nullptr) {
        delete m_fpNoRetargetA;
        m_fpNoRetargetA = nullptr;
    }
    if (m_fpNoRetargetB != nullptr) {
        delete m_fpNoRetargetB;
        m_fpNoRetargetB = nullptr;
    }
}

void GfBdatRsc::createFP() {
#line 291
    m_fpRscEn = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA5));
    m_fpRscEnGenus = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA6));
    m_fpRscEnUnd = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA7));
    m_fpRscNpcList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA8));
    m_fpRscNpcWpn = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xA9));
    m_fpRscMobList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xAA));
    m_fpRSC_PcWpn = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xAD));
    m_fpRSC_PcWpnMount = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xAE));
    m_fpRscEnWpn = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xAF));
    m_fpRSC_TboxList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xAC));
    m_fpRSC_MapObjList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xAB));
    m_fpDriverParam = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x90));
    m_fpVoiceTable = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x83));
    m_fpVoiceTableBlade = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x84));
    m_fpVoiceTableRare = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x85));
    m_fpVoiceTableCommon = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x86));
    m_fpFLD_actorSE = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x87));
    m_fpNoRetargetA = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE8));
    m_fpNoRetargetB = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE9));
}

void GfBdatRsc::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbrs::initRscEnDebugName(*m_fpRscEn);
    _gfbrs::initRscEnTypeFamily(*m_fpRscEn);
    _gfbrs::initRscEnTypeGenus(*m_fpRscEn);
    _gfbrs::initRscEnActType(*m_fpRscEn);
    _gfbrs::initRscEnFlyHeight(*m_fpRscEn);
    _gfbrs::initRscEnFldMoveType(*m_fpRscEn);
    _gfbrs::initRscEnMaterial(*m_fpRscEn);
    _gfbrs::initRscEnProxyID(*m_fpRscEn);
    _gfbrs::initRscEnEnRadius(*m_fpRscEn);
    _gfbrs::initRscEnEnRadius2(*m_fpRscEn);
    _gfbrs::initRscEnChestHeight(*m_fpRscEn);
    _gfbrs::initRscEnChestHeight2(*m_fpRscEn);
    _gfbrs::initRscEnBallRadius(*m_fpRscEn);
    _gfbrs::initRscEnBallHeight(*m_fpRscEn);
    _gfbrs::initRscEnCharColli(*m_fpRscEn);
    _gfbrs::initRscEnoffsetID(*m_fpRscEn);
    _gfbrs::initRscEnEyeRot(*m_fpRscEn);
    _gfbrs::initRscEnSearchBaseBone(*m_fpRscEn);
    _gfbrs::initRscEnCenterBone(*m_fpRscEn);
    _gfbrs::initRscEnCamBone(*m_fpRscEn);
    _gfbrs::initRscEnFrontAngle(*m_fpRscEn);
    _gfbrs::initRscEnTurnAngleSmall(*m_fpRscEn);
    _gfbrs::initRscEnTurnAngleBig(*m_fpRscEn);
    _gfbrs::initRscEnUnduration(*m_fpRscEn);
    _gfbrs::initRscEnModel(*m_fpRscEn);
    _gfbrs::initRscEnChrFile(*m_fpRscEn);
    _gfbrs::initRscEnMotion(*m_fpRscEn);
    _gfbrs::initRscEnRefMotion(*m_fpRscEn);
    _gfbrs::initRscEnEffectPack(*m_fpRscEn);
    _gfbrs::initRscEnLoopEffect(*m_fpRscEn);
    _gfbrs::initRscEnSePack(*m_fpRscEn);
    _gfbrs::initRscEnVoice(*m_fpRscEn);
    _gfbrs::initRscEnVoiceEx(*m_fpRscEn);
    _gfbrs::initRscEnClipEvent(*m_fpRscEn);
    _gfbrs::initRscEnComp_Eff(*m_fpRscEn);
    _gfbrs::initRscEnComp_Se(*m_fpRscEn);
    _gfbrs::initRscEnComp_Vo(*m_fpRscEn);
    _gfbrs::initRscEnFlagNoEcSkip(*m_fpRscEn);
    _gfbrs::initRscEnFlagMap(*m_fpRscEn);
    _gfbrs::initRscEnFlagEvt(*m_fpRscEn);
    _gfbrs::initRscEnFlagNoWinVo(*m_fpRscEn);
    _gfbrs::initRscEnFlagBait(*m_fpRscEn);
    _gfbrs::initRscEnFlagUseSearchBone(*m_fpRscEn);
    _gfbrs::initRscEnFlagNoVanish(*m_fpRscEn);
    _gfbrs::initRscEnFlagNoCamera(*m_fpRscEn);
    _gfbrs::initRscEnFlagWeaponDrawDisp(*m_fpRscEn);
    _gfbrs::initRscEnFlagJoinAll(*m_fpRscEn);
    _gfbrs::initRscEnFlagDeathMotion(*m_fpRscEn);
    _gfbrs::initRscEnWeaponNum1(*m_fpRscEn);
    _gfbrs::initRscEnWeaponNum2(*m_fpRscEn);
    _gfbrs::initRscEnWeaponNum3(*m_fpRscEn);
    _gfbrs::initRscEnWeaponNum4(*m_fpRscEn);
    _gfbrs::initRscEnWeaponNum5(*m_fpRscEn);
    _gfbrs::initRscEnMemorySlot(*m_fpRscEn);
    _gfbrs::initRscEnRace(*m_fpRscEn);
    _gfbrs::initRscEnDrType(*m_fpRscEn);
    _gfbrs::initRscEnGoldDivideRev(*m_fpRscEn);
    _gfbrs::initRscEnFootStep(*m_fpRscEn);
    _gfbrs::initRscEnFootStepEffect(*m_fpRscEn);
    _gfbrs::initRscEnRotateX(*m_fpRscEn);
    _gfbrs::initRscEnRotateY(*m_fpRscEn);
    _gfbrs::initRscEnRotateZ(*m_fpRscEn);
    _gfbrs::initRscEnRotateDeg(*m_fpRscEn);
    _gfbrs::initRscEnRotEffScale(*m_fpRscEn);
    _gfbrs::initRscEnExtraParts1(*m_fpRscEn);
    _gfbrs::initRscEnExtraParts2(*m_fpRscEn);
    _gfbrs::initRscEnExtraParts3(*m_fpRscEn);
    _gfbrs::initRscEnExtraParts4(*m_fpRscEn);
    _gfbrs::initRscEnExtraParts5(*m_fpRscEn);
    _gfbrs::initRscEnExtraParts6(*m_fpRscEn);
    _gfbrs::initRscEnDeadSeNum(*m_fpRscEn);
    _gfbrs::initRscEnRotateBone(*m_fpRscEn);
    _gfbrs::initRscEnGenusNAME(*m_fpRscEnGenus);
    _gfbrs::initRscEnGenusCAPTION(*m_fpRscEnGenus);
    _gfbrs::initRscEnGenusFlaggimmicktype(*m_fpRscEnGenus);
    _gfbrs::initRscEnUndFlagUndX(*m_fpRscEnUnd);
    _gfbrs::initRscEnUndFlagUndZ(*m_fpRscEnUnd);
    _gfbrs::initRscEnUndUndMinX(*m_fpRscEnUnd);
    _gfbrs::initRscEnUndUndMaxX(*m_fpRscEnUnd);
    _gfbrs::initRscEnUndUndMinZ(*m_fpRscEnUnd);
    _gfbrs::initRscEnUndUndMaxZ(*m_fpRscEnUnd);
    _gfbrs::initRscEnUndUndDeg(*m_fpRscEnUnd);
    _gfbrs::initRscNpcListModel(*m_fpRscNpcList);
    _gfbrs::initRscNpcListMotion(*m_fpRscNpcList);
    _gfbrs::initRscNpcListAddMotion(*m_fpRscNpcList);
    _gfbrs::initRscNpcListEvtRetarget(*m_fpRscNpcList);
    _gfbrs::initRscNpcListComp_Eff(*m_fpRscNpcList);
    _gfbrs::initRscNpcListCollisionId(*m_fpRscNpcList);
    _gfbrs::initRscNpcListSE(*m_fpRscNpcList);
    _gfbrs::initRscNpcListSeEnv(*m_fpRscNpcList);
    _gfbrs::initRscNpcListRace(*m_fpRscNpcList);
    _gfbrs::initRscNpcListFootStep(*m_fpRscNpcList);
    _gfbrs::initRscNpcListFootStepEffect(*m_fpRscNpcList);
    _gfbrs::initRscNpcListRoots(*m_fpRscNpcList);
    _gfbrs::initRscNpcListGender(*m_fpRscNpcList);
    _gfbrs::initRscNpcListName(*m_fpRscNpcList);
    _gfbrs::initRscNpcListOffsetID(*m_fpRscNpcList);
    _gfbrs::initRscNpcListEyeRot(*m_fpRscNpcList);
    _gfbrs::initRscNpcListExtraParts1(*m_fpRscNpcList);
    _gfbrs::initRscNpcListExtraParts2(*m_fpRscNpcList);
    _gfbrs::initRscNpcListExtraParts3(*m_fpRscNpcList);
    _gfbrs::initRscNpcListExtraParts4(*m_fpRscNpcList);
    _gfbrs::initRscNpcListExtraParts5(*m_fpRscNpcList);
    _gfbrs::initRscNpcListExtraParts6(*m_fpRscNpcList);
    _gfbrs::initRscNpcListScale(*m_fpRscNpcList);
    _gfbrs::initRscNpcListEventAsset(*m_fpRscNpcList);
    _gfbrs::initRscNpcListJob(*m_fpRscNpcList);
    _gfbrs::initRscNpcListHitonowaFlag(*m_fpRscNpcList);
    _gfbrs::initRscNpcListNpcMeetFlag(*m_fpRscNpcList);
    _gfbrs::initRscNpcListMSGID(*m_fpRscNpcList);
    _gfbrs::initRscNpcListCondition1(*m_fpRscNpcList);
    _gfbrs::initRscNpcListMSGID2(*m_fpRscNpcList);
    _gfbrs::initRscNpcListCondition2(*m_fpRscNpcList);
    _gfbrs::initRscNpcListMSGID3(*m_fpRscNpcList);
    _gfbrs::initRscNpcListresult(*m_fpRscNpcList);
    _gfbrs::initRscMobListModel(*m_fpRscMobList);
    _gfbrs::initRscMobListMotion(*m_fpRscMobList);
    _gfbrs::initRscMobListAddMotion(*m_fpRscMobList);
    _gfbrs::initRscMobListComp_Eff(*m_fpRscMobList);
    _gfbrs::initRscMobListCollisionId(*m_fpRscMobList);
    _gfbrs::initRscMobListSE(*m_fpRscMobList);
    _gfbrs::initRscMobListSeEnv(*m_fpRscMobList);
    _gfbrs::initRscMobListRace(*m_fpRscMobList);
    _gfbrs::initRscMobListFootStep(*m_fpRscMobList);
    _gfbrs::initRscMobListFootStepEffect(*m_fpRscMobList);
    _gfbrs::initRscMobListOffsetID(*m_fpRscMobList);
    _gfbrs::initRscMobListExtraParts1(*m_fpRscMobList);
    _gfbrs::initRscMobListExtraParts2(*m_fpRscMobList);
    _gfbrs::initRscMobListExtraParts3(*m_fpRscMobList);
    _gfbrs::initRscMobListExtraParts4(*m_fpRscMobList);
    _gfbrs::initRscMobListExtraParts5(*m_fpRscMobList);
    _gfbrs::initRscMobListExtraParts6(*m_fpRscMobList);
    _gfbrs::initRSC_MapObjListModel(*m_fpRSC_MapObjList);
    _gfbrs::initRSC_MapObjListMotion(*m_fpRSC_MapObjList);
    _gfbrs::initRSC_MapObjListComp_Eff(*m_fpRSC_MapObjList);
    _gfbrs::initRSC_MapObjListSE(*m_fpRSC_MapObjList);
    _gfbrs::initRSC_MapObjListSeEnv(*m_fpRSC_MapObjList);
    _gfbrs::initRSC_MapObjListflagBigObj(*m_fpRSC_MapObjList);
    _gfbrs::initRSC_MapObjListExtraParts1(*m_fpRSC_MapObjList);
    _gfbrs::initRSC_TboxListModel(*m_fpRSC_TboxList);
    _gfbrs::initRSC_TboxListMotion(*m_fpRSC_TboxList);
    _gfbrs::initRSC_PcWpnModel(*m_fpRSC_PcWpn);
    _gfbrs::initRSC_PcWpnMotion(*m_fpRSC_PcWpn);
    _gfbrs::initRSC_PcWpnMenuImageID(*m_fpRSC_PcWpn);
    _gfbrs::initRSC_PcWpnMountWpn01rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn01rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn02rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn02rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn03rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn03rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn03lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn03lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn04rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn04rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn05rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn05rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn05lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn05lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn06rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn06rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn07rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn07rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn07lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn07lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn08rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn08rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn09rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn09rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn09lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn09lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn10rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn10rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn10lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn10lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn11rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn11rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn12rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn12rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn12lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn12lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn13rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn13rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn14rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn14rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn15rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn15rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn16rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn16rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn16lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn16lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn17rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn17rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn18rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn18rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn19rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn19rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn20rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn20rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn20lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn20lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn21rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn21rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn22rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn22rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn22lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn22lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn23rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn23rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn23lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn23lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn24rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn24rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn24lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn24lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn25rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn25rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn25lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn25lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn26rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn26rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn26lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn26lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn28rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn28rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn28lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn28lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn29rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn29rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn29lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn29lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn30rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn30rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn30lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn30lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn31rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn31rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn31lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn31lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn32rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn32rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn32lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn32lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn33rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn33rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn33lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn33lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn34rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn34rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn34lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn34lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn35rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn35rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn35lIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn35lOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn36rIn(*m_fpRSC_PcWpnMount);
    _gfbrs::initRSC_PcWpnMountWpn36rOut(*m_fpRSC_PcWpnMount);
    _gfbrs::initRscEnWpnModel(*m_fpRscEnWpn);
    _gfbrs::initRscEnWpnScale(*m_fpRscEnWpn);
    _gfbrs::initRscEnWpnMotion(*m_fpRscEnWpn);
    _gfbrs::initRscEnWpnMtpInChara(*m_fpRscEnWpn);
    _gfbrs::initRscEnWpnMtpInWpn(*m_fpRscEnWpn);
    _gfbrs::initRscEnWpnMtpOutChara(*m_fpRscEnWpn);
    _gfbrs::initRscEnWpnMtpOutWpn(*m_fpRscEnWpn);
    _gfbrs::initRscNpcWpnModel(*m_fpRscNpcWpn);
    _gfbrs::initRscNpcWpnMotion(*m_fpRscNpcWpn);
    _gfbrs::initDriverParamExtMountNpc(*m_fpDriverParam);
    _gfbrs::initDriverParamExtMountBone(*m_fpDriverParam);
    _gfbrs::initDriverParamExtMountCond(*m_fpDriverParam);
    _gfbrs::initVoiceTableDriver1(*m_fpVoiceTable);
    _gfbrs::initVoiceTableDriver2(*m_fpVoiceTable);
    _gfbrs::initVoiceTableDriver3(*m_fpVoiceTable);
    _gfbrs::initVoiceTableDriver4(*m_fpVoiceTable);
    _gfbrs::initVoiceTableDriver5(*m_fpVoiceTable);
    _gfbrs::initVoiceTableDriver6(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra1(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra2(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra3(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra4(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra5(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra6(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra7(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra8(*m_fpVoiceTable);
    _gfbrs::initVoiceTableIra9(*m_fpVoiceTable);
    _gfbrs::initVoiceTableBladeBlade1(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade2(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade3(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade4(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade5(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade6(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade7(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade8(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade9(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade10(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableBladeBlade11(*m_fpVoiceTableBlade);
    _gfbrs::initVoiceTableRareRareBlade1(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade2(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade3(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade4(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade5(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade6(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade7(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade8(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade9(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade10(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade11(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade12(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade13(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade14(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade15(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade16(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade17(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade18(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade19(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade20(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade21(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade22(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade23(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade24(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade25(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade26(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade27(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade28(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade29(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade30(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade31(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade32(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade33(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade34(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade35(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade36(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade37(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade38(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade39(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade40(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade41(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade42(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade43(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableRareRareBlade44(*m_fpVoiceTableRare);
    _gfbrs::initVoiceTableCommonCommonBlade1(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade2(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade3(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade4(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade5(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade6(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade7(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade8(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade9(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade10(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade11(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade12(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade13(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade14(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade15(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade16(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade17(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade18(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade19(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade20(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade21(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade22(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade23(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade24(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade25(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade26(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade27(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade28(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade29(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade30(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade31(*m_fpVoiceTableCommon);
    _gfbrs::initVoiceTableCommonCommonBlade32(*m_fpVoiceTableCommon);
    _gfbrs::initFLD_actorSELOD(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEse_type(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEseName(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEmax_volume_Dist(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEmin_volume_Dist(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEvolumeMAX(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEvolumeMIN(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEoffsetX(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEoffsetY(*m_fpFLD_actorSE);
    _gfbrs::initFLD_actorSEoffsetZ(*m_fpFLD_actorSE);
    _gfbrs::initNoRetargetAnoRetarget(*m_fpNoRetargetA);
    _gfbrs::initNoRetargetBnoRetarget(*m_fpNoRetargetB);
}

unsigned int GfBdatRsc::getRscEnTypeFamily(unsigned int id) const {
    return _gfbrs::getRscEnTypeFamily(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnTypeGenus(unsigned int id) const {
    return _gfbrs::getRscEnTypeGenus(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnActType(unsigned int id) const {
    return _gfbrs::getRscEnActType(*m_fpRscEn, id);
}

int GfBdatRsc::getRscEnFlyHeight(unsigned int id) const {
    return _gfbrs::getRscEnFlyHeight(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnFldMoveType(unsigned int id) const {
    return _gfbrs::getRscEnFldMoveType(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnMaterial(unsigned int id) const {
    return _gfbrs::getRscEnMaterial(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnEnRadius(unsigned int id) const {
    return _gfbrs::getRscEnEnRadius(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnEnRadius2(unsigned int id) const {
    return _gfbrs::getRscEnEnRadius2(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnChestHeight(unsigned int id) const {
    return _gfbrs::getRscEnChestHeight(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnChestHeight2(unsigned int id) const {
    return _gfbrs::getRscEnChestHeight2(*m_fpRscEn, id);
}

float GfBdatRsc::getRscEnBallRadius(unsigned int id) const {
    return _gfbrs::getRscEnBallRadius(*m_fpRscEn, id);
}

float GfBdatRsc::getRscEnBallHeight(unsigned int id) const {
    return _gfbrs::getRscEnBallHeight(*m_fpRscEn, id);
}

float GfBdatRsc::getRscEnCharColli(unsigned int id) const {
    return _gfbrs::getRscEnCharColli(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnoffsetID(unsigned int id) const {
    return _gfbrs::getRscEnoffsetID(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnEyeRot(unsigned int id) const {
    return _gfbrs::getRscEnEyeRot(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnSearchBaseBone(unsigned int id) const {
    return _gfbrs::getRscEnSearchBaseBone(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnCenterBone(unsigned int id) const {
    return _gfbrs::getRscEnCenterBone(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnCamBone(unsigned int id) const {
    return _gfbrs::getRscEnCamBone(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnFrontAngle(unsigned int id) const {
    return _gfbrs::getRscEnFrontAngle(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnModel(unsigned int id) const {
    return _gfbrs::getRscEnModel(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnMotion(unsigned int id) const {
    return _gfbrs::getRscEnMotion(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnRefMotion(unsigned int id) const {
    return _gfbrs::getRscEnRefMotion(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnEffectPack(unsigned int id) const {
    return _gfbrs::getRscEnEffectPack(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnLoopEffect(unsigned int id) const {
    return _gfbrs::getRscEnLoopEffect(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnSePack(unsigned int id) const {
    return _gfbrs::getRscEnSePack(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnVoice(unsigned int id) const {
    return _gfbrs::getRscEnVoice(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnVoiceEx(unsigned int id) const {
    return _gfbrs::getRscEnVoiceEx(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnComp_Eff(unsigned int id) const {
    return _gfbrs::getRscEnComp_Eff(*m_fpRscEn, id);
}

bool GfBdatRsc::isRscEnFlagBait(unsigned int id) const {
    return _gfbrs::getRscEnFlagBait(*m_fpRscEn, id);
}

bool GfBdatRsc::isRscEnFlagNoVanish(unsigned int id) const {
    return _gfbrs::getRscEnFlagNoVanish(*m_fpRscEn, id);
}

bool GfBdatRsc::isRscEnFlagNoCamera(unsigned int id) const {
    return _gfbrs::getRscEnFlagNoCamera(*m_fpRscEn, id);
}

bool GfBdatRsc::isRscEnFlagWeaponDrawDisp(unsigned int id) const {
    return _gfbrs::getRscEnFlagWeaponDrawDisp(*m_fpRscEn, id);
}

bool GfBdatRsc::isRscEnFlagJoinAll(unsigned int id) const {
    return _gfbrs::getRscEnFlagJoinAll(*m_fpRscEn, id);
}

bool GfBdatRsc::isRscEnFlagDeathMotion(unsigned int id) const {
    return _gfbrs::getRscEnFlagDeathMotion(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnMemorySlot(unsigned int id) const {
    return _gfbrs::getRscEnMemorySlot(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnRace(unsigned int id) const {
    return _gfbrs::getRscEnRace(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnDrType(unsigned int id) const {
    return _gfbrs::getRscEnDrType(*m_fpRscEn, id);
}

int GfBdatRsc::getRscEnGoldDivideRev(unsigned int id) const {
    return _gfbrs::getRscEnGoldDivideRev(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnFootStep(unsigned int id) const {
    return _gfbrs::getRscEnFootStep(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnFootStepEffect(unsigned int id) const {
    return _gfbrs::getRscEnFootStepEffect(*m_fpRscEn, id);
}

int GfBdatRsc::getRscEnRotateX(unsigned int id) const {
    return _gfbrs::getRscEnRotateX(*m_fpRscEn, id);
}

int GfBdatRsc::getRscEnRotateY(unsigned int id) const {
    return _gfbrs::getRscEnRotateY(*m_fpRscEn, id);
}

int GfBdatRsc::getRscEnRotateZ(unsigned int id) const {
    return _gfbrs::getRscEnRotateZ(*m_fpRscEn, id);
}

int GfBdatRsc::getRscEnRotateDeg(unsigned int id) const {
    return _gfbrs::getRscEnRotateDeg(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnRotEffScale(unsigned int id) const {
    return _gfbrs::getRscEnRotEffScale(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::fn_710021903C(unsigned int id) const {
    return _gfbrs::fn_710020D650(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::fn_71002190C4(unsigned int id) const {
    return _gfbrs::fn_710020D6D8(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnDeadSeNum(unsigned int id) const {
    return _gfbrs::getRscEnDeadSeNum(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnWeaponNum(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getRscEnWeaponNum1,
        _gfbrs::getRscEnWeaponNum2,
        _gfbrs::getRscEnWeaponNum3,
        _gfbrs::getRscEnWeaponNum4,
        _gfbrs::getRscEnWeaponNum5,
    };
    return _gfbrs::getSlot(s_getters, slot)(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnExtraParts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getRscEnExtraParts1,
        _gfbrs::getRscEnExtraParts2,
        _gfbrs::getRscEnExtraParts3,
        _gfbrs::getRscEnExtraParts4,
        _gfbrs::fn_710020D650,
        _gfbrs::fn_710020D6D8,
    };
    return _gfbrs::getSlot(s_getters, slot)(*m_fpRscEn, id);
}

const char* GfBdatRsc::getRscEnRotateBone(unsigned int id) const {
    return _gfbrs::getRscEnRotateBone(*m_fpRscEn, id);
}

unsigned int GfBdatRsc::getRscEnGenusNAME(unsigned int id) const {
    return _gfbrs::getRscEnGenusNAME(*m_fpRscEnGenus, id);
}

bool GfBdatRsc::isRscEnGenusFlaggimmicktype(unsigned int id) const {
    return _gfbrs::getRscEnGenusFlaggimmicktype(*m_fpRscEnGenus, id);
}

unsigned int GfBdatRsc::getRscNpcListStart() const {
    return Bdat::getIdTop(m_fpRscNpcList->m_fp);
}

unsigned int GfBdatRsc::getRscNpcListEnd() const {
    return Bdat::getIdTop(m_fpRscNpcList->m_fp) + Bdat::getIdCount(m_fpRscNpcList->m_fp);
}

const char* GfBdatRsc::getRscNpcListModel(unsigned int id) const {
    return _gfbrs::getRscNpcListModel(*m_fpRscNpcList, id);
}

const char* GfBdatRsc::getRscNpcListMotion(unsigned int id) const {
    return _gfbrs::getRscNpcListMotion(*m_fpRscNpcList, id);
}

const char* GfBdatRsc::getRscNpcListAddMotion(unsigned int id) const {
    return _gfbrs::getRscNpcListAddMotion(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219574(unsigned int id) const {
    return _gfbrs::getRscNpcListEvtRetarget(*m_fpRscNpcList, id);
}

const char* GfBdatRsc::getRscNpcListComp_Eff(unsigned int id) const {
    return _gfbrs::getRscNpcListComp_Eff(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListCollisionId(unsigned int id) const {
    return _gfbrs::getRscNpcListCollisionId(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListRace(unsigned int id) const {
    return _gfbrs::getRscNpcListRace(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListFootStep(unsigned int id) const {
    return _gfbrs::getRscNpcListFootStep(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListFootStepEffect(unsigned int id) const {
    return _gfbrs::getRscNpcListFootStepEffect(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListRoots(unsigned int id) const {
    return _gfbrs::getRscNpcListRoots(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListGender(unsigned int id) const {
    return _gfbrs::getRscNpcListGender(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListName(unsigned int id) const {
    return _gfbrs::getRscNpcListName(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListOffsetID(unsigned int id) const {
    return _gfbrs::getRscNpcListOffsetID(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListEyeRot(unsigned int id) const {
    return _gfbrs::getRscNpcListEyeRot(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListScale(unsigned int id) const {
    return _gfbrs::getRscNpcListScale(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219BD0(unsigned int id) const {
    return _gfbrs::getRscNpcListJob(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219C58(unsigned int id) const {
    return _gfbrs::getRscNpcListHitonowaFlag(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219CE0(unsigned int id) const {
    return _gfbrs::getRscNpcListNpcMeetFlag(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219D68(unsigned int id) const {
    return _gfbrs::getRscNpcListMSGID(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219DF0(unsigned int id) const {
    return _gfbrs::getRscNpcListCondition1(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219E78(unsigned int id) const {
    return _gfbrs::getRscNpcListMSGID2(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219F00(unsigned int id) const {
    return _gfbrs::getRscNpcListCondition2(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_7100219F88(unsigned int id) const {
    return _gfbrs::getRscNpcListMSGID3(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::fn_710021A010(unsigned int id) const {
    return _gfbrs::getRscNpcListresult(*m_fpRscNpcList, id);
}

unsigned int GfBdatRsc::getRscNpcListExtraParts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getRscNpcListExtraParts1,
        _gfbrs::getRscNpcListExtraParts2,
        _gfbrs::getRscNpcListExtraParts3,
        _gfbrs::getRscNpcListExtraParts4,
        _gfbrs::getRscNpcListExtraParts5,
        _gfbrs::getRscNpcListExtraParts6,
    };
    return _gfbrs::getSlot(s_getters, slot)(*m_fpRscNpcList, id);
}

const char* GfBdatRsc::getRscMobListModel(unsigned int id) const {
    return _gfbrs::getRscMobListModel(*m_fpRscMobList, id);
}

const char* GfBdatRsc::getRscMobListMotion(unsigned int id) const {
    return _gfbrs::getRscMobListMotion(*m_fpRscMobList, id);
}

const char* GfBdatRsc::getRscMobListAddMotion(unsigned int id) const {
    return _gfbrs::getRscMobListAddMotion(*m_fpRscMobList, id);
}

const char* GfBdatRsc::getRscMobListComp_Eff(unsigned int id) const {
    return _gfbrs::getRscMobListComp_Eff(*m_fpRscMobList, id);
}

unsigned int GfBdatRsc::getRscMobListRace(unsigned int id) const {
    return _gfbrs::getRscMobListRace(*m_fpRscMobList, id);
}

unsigned int GfBdatRsc::getRscMobListFootStep(unsigned int id) const {
    return _gfbrs::getRscMobListFootStep(*m_fpRscMobList, id);
}

unsigned int GfBdatRsc::getRscMobListFootStepEffect(unsigned int id) const {
    return _gfbrs::getRscMobListFootStepEffect(*m_fpRscMobList, id);
}

unsigned int GfBdatRsc::getRscMobListOffsetID(unsigned int id) const {
    return _gfbrs::getRscMobListOffsetID(*m_fpRscMobList, id);
}

unsigned int GfBdatRsc::getRscMobListExtraParts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getRscMobListExtraParts1,
        _gfbrs::getRscMobListExtraParts2,
        _gfbrs::getRscMobListExtraParts3,
        _gfbrs::getRscMobListExtraParts4,
        _gfbrs::getRscMobListExtraParts5,
        _gfbrs::getRscMobListExtraParts6,
    };
    return _gfbrs::getSlot(s_getters, slot)(*m_fpRscMobList, id);
}

const char* GfBdatRsc::getRSC_MapObjListModel(unsigned int id) const {
    return _gfbrs::getRSC_MapObjListModel(*m_fpRSC_MapObjList, id);
}

const char* GfBdatRsc::getRSC_MapObjListMotion(unsigned int id) const {
    return _gfbrs::getRSC_MapObjListMotion(*m_fpRSC_MapObjList, id);
}

unsigned int GfBdatRsc::getRSC_MapObjListExtraParts1(unsigned int id) const {
    return _gfbrs::getRSC_MapObjListExtraParts1(*m_fpRSC_MapObjList, id);
}

const char* GfBdatRsc::getRSC_TboxListModel(unsigned int id) const {
    return _gfbrs::getRSC_TboxListModel(*m_fpRSC_TboxList, id);
}

const char* GfBdatRsc::getRSC_TboxListMotion(unsigned int id) const {
    return _gfbrs::getRSC_TboxListMotion(*m_fpRSC_TboxList, id);
}

const char* GfBdatRsc::getRSC_PcWpnModel(unsigned int id) const {
    return _gfbrs::getRSC_PcWpnModel(*m_fpRSC_PcWpn, id);
}

const char* GfBdatRsc::getRSC_PcWpnMotion(unsigned int id) const {
    return _gfbrs::getRSC_PcWpnMotion(*m_fpRSC_PcWpn, id);
}

int GfBdatRsc::getRSC_PcWpnMenuImageID(unsigned int id) const {
    return _gfbrs::getRSC_PcWpnMenuImageID(*m_fpRSC_PcWpn, id);
}

const char* GfBdatRsc::getRSC_PcWpnMountWpnInR(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn01rIn,
        _gfbrs::getRSC_PcWpnMountWpn02rIn,
        _gfbrs::getRSC_PcWpnMountWpn03rIn,
        _gfbrs::getRSC_PcWpnMountWpn04rIn,
        _gfbrs::getRSC_PcWpnMountWpn05rIn,
        _gfbrs::getRSC_PcWpnMountWpn06rIn,
        _gfbrs::getRSC_PcWpnMountWpn07rIn,
        _gfbrs::getRSC_PcWpnMountWpn08rIn,
        _gfbrs::getRSC_PcWpnMountWpn09rIn,
        _gfbrs::getRSC_PcWpnMountWpn10rIn,
        _gfbrs::getRSC_PcWpnMountWpn11rIn,
        _gfbrs::getRSC_PcWpnMountWpn12rIn,
        _gfbrs::getRSC_PcWpnMountWpn13rIn,
        _gfbrs::getRSC_PcWpnMountWpn14rIn,
        _gfbrs::getRSC_PcWpnMountWpn15rIn,
        _gfbrs::getRSC_PcWpnMountWpn16rIn,
        _gfbrs::getRSC_PcWpnMountWpn17rIn,
        _gfbrs::getRSC_PcWpnMountWpn18rIn,
        _gfbrs::getRSC_PcWpnMountWpn19rIn,
        _gfbrs::getRSC_PcWpnMountWpn20rIn,
        _gfbrs::getRSC_PcWpnMountWpn21rIn,
        _gfbrs::getRSC_PcWpnMountWpn22rIn,
        _gfbrs::getRSC_PcWpnMountWpn23rIn,
        _gfbrs::getRSC_PcWpnMountWpn24rIn,
        _gfbrs::getRSC_PcWpnMountWpn25rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::fn_71002105F8,
        _gfbrs::fn_7100210808,
        _gfbrs::fn_7100210A18,
        _gfbrs::fn_7100210C28,
        _gfbrs::fn_7100210E38,
        _gfbrs::fn_7100211048,
        _gfbrs::fn_7100211258,
        _gfbrs::fn_7100211468,
        _gfbrs::fn_7100211678,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
        _gfbrs::getRSC_PcWpnMountWpn26rIn,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpRSC_PcWpnMount, id);
    }
    return "";
}

const char* GfBdatRsc::getRSC_PcWpnMountWpnInL(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        nullptr,
        nullptr,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn03lIn,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn05lIn,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn07lIn,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn09lIn,
        _gfbrs::getRSC_PcWpnMountWpn10lIn,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn12lIn,
        nullptr,
        nullptr,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn16lIn,
        nullptr,
        nullptr,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn20lIn,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn22lIn,
        _gfbrs::getRSC_PcWpnMountWpn23lIn,
        _gfbrs::getRSC_PcWpnMountWpn24lIn,
        _gfbrs::getRSC_PcWpnMountWpn25lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        nullptr,
        _gfbrs::fn_7100210700,
        _gfbrs::fn_7100210910,
        _gfbrs::fn_7100210B20,
        _gfbrs::fn_7100210D30,
        _gfbrs::fn_7100210F40,
        _gfbrs::fn_7100211150,
        _gfbrs::fn_7100211360,
        _gfbrs::fn_7100211570,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
        _gfbrs::getRSC_PcWpnMountWpn26lIn,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpRSC_PcWpnMount, id);
    }
    return "";
}

const char* GfBdatRsc::getRSC_PcWpnMountWpnOutR(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn01rOut,
        _gfbrs::getRSC_PcWpnMountWpn02rOut,
        _gfbrs::getRSC_PcWpnMountWpn03rOut,
        _gfbrs::getRSC_PcWpnMountWpn04rOut,
        _gfbrs::getRSC_PcWpnMountWpn05rOut,
        _gfbrs::getRSC_PcWpnMountWpn06rOut,
        _gfbrs::getRSC_PcWpnMountWpn07rOut,
        _gfbrs::getRSC_PcWpnMountWpn08rOut,
        _gfbrs::getRSC_PcWpnMountWpn09rOut,
        _gfbrs::getRSC_PcWpnMountWpn10rOut,
        _gfbrs::getRSC_PcWpnMountWpn11rOut,
        _gfbrs::getRSC_PcWpnMountWpn12rOut,
        _gfbrs::getRSC_PcWpnMountWpn13rOut,
        _gfbrs::getRSC_PcWpnMountWpn14rOut,
        _gfbrs::getRSC_PcWpnMountWpn15rOut,
        _gfbrs::getRSC_PcWpnMountWpn16rOut,
        _gfbrs::getRSC_PcWpnMountWpn17rOut,
        _gfbrs::getRSC_PcWpnMountWpn18rOut,
        _gfbrs::getRSC_PcWpnMountWpn19rOut,
        _gfbrs::getRSC_PcWpnMountWpn20rOut,
        _gfbrs::getRSC_PcWpnMountWpn21rOut,
        _gfbrs::getRSC_PcWpnMountWpn22rOut,
        _gfbrs::getRSC_PcWpnMountWpn23rOut,
        _gfbrs::getRSC_PcWpnMountWpn24rOut,
        _gfbrs::getRSC_PcWpnMountWpn25rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::fn_710021067C,
        _gfbrs::fn_710021088C,
        _gfbrs::fn_7100210A9C,
        _gfbrs::fn_7100210CAC,
        _gfbrs::fn_7100210EBC,
        _gfbrs::fn_71002110CC,
        _gfbrs::fn_71002112DC,
        _gfbrs::fn_71002114EC,
        _gfbrs::fn_71002116FC,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
        _gfbrs::getRSC_PcWpnMountWpn26rOut,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpRSC_PcWpnMount, id);
    }
    return "";
}

const char* GfBdatRsc::getRSC_PcWpnMountWpnOutL(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        nullptr,
        nullptr,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn03lOut,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn05lOut,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn07lOut,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn09lOut,
        _gfbrs::getRSC_PcWpnMountWpn10lOut,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn12lOut,
        nullptr,
        nullptr,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn16lOut,
        nullptr,
        nullptr,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn20lOut,
        nullptr,
        _gfbrs::getRSC_PcWpnMountWpn22lOut,
        _gfbrs::getRSC_PcWpnMountWpn23lOut,
        _gfbrs::getRSC_PcWpnMountWpn24lOut,
        _gfbrs::getRSC_PcWpnMountWpn25lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        nullptr,
        _gfbrs::fn_7100210784,
        _gfbrs::fn_7100210994,
        _gfbrs::fn_7100210BA4,
        _gfbrs::fn_7100210DB4,
        _gfbrs::fn_7100210FC4,
        _gfbrs::fn_71002111D4,
        _gfbrs::fn_71002113E4,
        _gfbrs::fn_71002115F4,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
        _gfbrs::getRSC_PcWpnMountWpn26lOut,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpRSC_PcWpnMount, id);
    }
    return "";
}

const char* GfBdatRsc::getRscEnWpnModel(unsigned int id) const {
    return _gfbrs::getRscEnWpnModel(*m_fpRscEnWpn, id);
}

unsigned int GfBdatRsc::getRscEnWpnScale(unsigned int id) const {
    return _gfbrs::getRscEnWpnScale(*m_fpRscEnWpn, id);
}

const char* GfBdatRsc::getRscEnWpnMotion(unsigned int id) const {
    return _gfbrs::getRscEnWpnMotion(*m_fpRscEnWpn, id);
}

const char* GfBdatRsc::getRscEnWpnMtpInChara(unsigned int id) const {
    return _gfbrs::getRscEnWpnMtpInChara(*m_fpRscEnWpn, id);
}

const char* GfBdatRsc::getRscEnWpnMtpOutChara(unsigned int id) const {
    return _gfbrs::getRscEnWpnMtpOutChara(*m_fpRscEnWpn, id);
}

const char* GfBdatRsc::getRscNpcWpnModel(unsigned int id) const {
    return _gfbrs::getRscNpcWpnModel(*m_fpRscNpcWpn, id);
}

const char* GfBdatRsc::getRscNpcWpnMotion(unsigned int id) const {
    return _gfbrs::getRscNpcWpnMotion(*m_fpRscNpcWpn, id);
}

unsigned int GfBdatRsc::getDriverParamExtMountNpc(unsigned int id) const {
    return _gfbrs::getDriverParamExtMountNpc(*m_fpDriverParam, id);
}

const char* GfBdatRsc::getDriverParamExtMountBone(unsigned int id) const {
    return _gfbrs::getDriverParamExtMountBone(*m_fpDriverParam, id);
}

unsigned int GfBdatRsc::getDriverParamExtMountCond(unsigned int id) const {
    return _gfbrs::getDriverParamExtMountCond(*m_fpDriverParam, id);
}

const char* GfBdatRsc::getVoiceTableDriver(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getVoiceTableDriver1,
        _gfbrs::getVoiceTableDriver2,
        _gfbrs::getVoiceTableDriver3,
        _gfbrs::getVoiceTableDriver4,
        _gfbrs::getVoiceTableDriver5,
        _gfbrs::getVoiceTableDriver6,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpVoiceTable, id);
    }
    return "";
}

const char* GfBdatRsc::fn_710021AF00(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::fn_7100211A98,
        _gfbrs::fn_7100211B1C,
        _gfbrs::fn_7100211BA0,
        _gfbrs::fn_7100211C24,
        _gfbrs::fn_7100211CA8,
        _gfbrs::fn_7100211D2C,
        _gfbrs::fn_7100211DB0,
        _gfbrs::fn_7100211E34,
        _gfbrs::fn_7100211EB8,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpVoiceTable, id);
    }
    return "";
}

const char* GfBdatRsc::getVoiceTableBladeBlade(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getVoiceTableBladeBlade1,
        _gfbrs::getVoiceTableBladeBlade2,
        _gfbrs::getVoiceTableBladeBlade3,
        _gfbrs::getVoiceTableBladeBlade4,
        _gfbrs::getVoiceTableBladeBlade5,
        _gfbrs::getVoiceTableBladeBlade6,
        _gfbrs::getVoiceTableBladeBlade7,
        _gfbrs::getVoiceTableBladeBlade8,
        _gfbrs::getVoiceTableBladeBlade9,
        _gfbrs::getVoiceTableBladeBlade10,
        _gfbrs::getVoiceTableBladeBlade11,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpVoiceTableBlade, id);
    }
    return "";
}

const char* GfBdatRsc::getVoiceTableRareBlade(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getVoiceTableRareRareBlade1,
        _gfbrs::getVoiceTableRareRareBlade2,
        _gfbrs::getVoiceTableRareRareBlade3,
        _gfbrs::getVoiceTableRareRareBlade4,
        _gfbrs::getVoiceTableRareRareBlade5,
        _gfbrs::getVoiceTableRareRareBlade6,
        _gfbrs::getVoiceTableRareRareBlade7,
        _gfbrs::getVoiceTableRareRareBlade8,
        _gfbrs::getVoiceTableRareRareBlade9,
        _gfbrs::getVoiceTableRareRareBlade10,
        _gfbrs::getVoiceTableRareRareBlade11,
        _gfbrs::getVoiceTableRareRareBlade12,
        _gfbrs::getVoiceTableRareRareBlade13,
        _gfbrs::getVoiceTableRareRareBlade14,
        _gfbrs::getVoiceTableRareRareBlade15,
        _gfbrs::getVoiceTableRareRareBlade16,
        _gfbrs::getVoiceTableRareRareBlade17,
        _gfbrs::getVoiceTableRareRareBlade18,
        _gfbrs::getVoiceTableRareRareBlade19,
        _gfbrs::getVoiceTableRareRareBlade20,
        _gfbrs::getVoiceTableRareRareBlade21,
        _gfbrs::getVoiceTableRareRareBlade22,
        _gfbrs::getVoiceTableRareRareBlade23,
        _gfbrs::getVoiceTableRareRareBlade24,
        _gfbrs::getVoiceTableRareRareBlade25,
        _gfbrs::getVoiceTableRareRareBlade26,
        _gfbrs::getVoiceTableRareRareBlade27,
        _gfbrs::getVoiceTableRareRareBlade28,
        _gfbrs::getVoiceTableRareRareBlade29,
        _gfbrs::getVoiceTableRareRareBlade30,
        _gfbrs::getVoiceTableRareRareBlade31,
        _gfbrs::getVoiceTableRareRareBlade32,
        _gfbrs::getVoiceTableRareRareBlade33,
        _gfbrs::getVoiceTableRareRareBlade34,
        _gfbrs::getVoiceTableRareRareBlade35,
        _gfbrs::getVoiceTableRareRareBlade36,
        _gfbrs::getVoiceTableRareRareBlade37,
        _gfbrs::fn_71002137FC,
        _gfbrs::fn_7100213880,
        _gfbrs::fn_7100213904,
        _gfbrs::fn_7100213988,
        _gfbrs::fn_7100213A0C,
        _gfbrs::fn_7100213A90,
        _gfbrs::fn_7100213B14,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpVoiceTableRare, id);
    }
    return "";
}

const char* GfBdatRsc::getVoiceTableCommonCommonBlade(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static const char* (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbrs::getVoiceTableCommonCommonBlade1,
        _gfbrs::getVoiceTableCommonCommonBlade2,
        _gfbrs::getVoiceTableCommonCommonBlade3,
        _gfbrs::getVoiceTableCommonCommonBlade4,
        _gfbrs::getVoiceTableCommonCommonBlade5,
        _gfbrs::getVoiceTableCommonCommonBlade6,
        _gfbrs::getVoiceTableCommonCommonBlade7,
        _gfbrs::getVoiceTableCommonCommonBlade8,
        _gfbrs::getVoiceTableCommonCommonBlade9,
        _gfbrs::getVoiceTableCommonCommonBlade10,
        _gfbrs::getVoiceTableCommonCommonBlade11,
        _gfbrs::getVoiceTableCommonCommonBlade12,
        _gfbrs::getVoiceTableCommonCommonBlade13,
        _gfbrs::getVoiceTableCommonCommonBlade14,
        _gfbrs::getVoiceTableCommonCommonBlade15,
        _gfbrs::getVoiceTableCommonCommonBlade16,
        _gfbrs::getVoiceTableCommonCommonBlade17,
        _gfbrs::getVoiceTableCommonCommonBlade18,
        _gfbrs::getVoiceTableCommonCommonBlade19,
        _gfbrs::getVoiceTableCommonCommonBlade20,
        _gfbrs::getVoiceTableCommonCommonBlade21,
        _gfbrs::getVoiceTableCommonCommonBlade22,
        _gfbrs::getVoiceTableCommonCommonBlade23,
        _gfbrs::getVoiceTableCommonCommonBlade24,
        _gfbrs::getVoiceTableCommonCommonBlade25,
        _gfbrs::getVoiceTableCommonCommonBlade26,
        _gfbrs::getVoiceTableCommonCommonBlade27,
        _gfbrs::getVoiceTableCommonCommonBlade28,
        _gfbrs::getVoiceTableCommonCommonBlade29,
        _gfbrs::getVoiceTableCommonCommonBlade30,
        _gfbrs::getVoiceTableCommonCommonBlade31,
        _gfbrs::getVoiceTableCommonCommonBlade32,
        nullptr,
        nullptr,
    };
    const char* (*getter)(const CBdatWrapper&, unsigned int) = _gfbrs::getSlot(s_getters, slot);
    if (getter != nullptr) {
        return getter(*m_fpVoiceTableCommon, id);
    }
    return "";
}

unsigned int GfBdatRsc::getFLD_actorSEStart() const {
    return Bdat::getIdTop(m_fpFLD_actorSE->m_fp);
}

unsigned int GfBdatRsc::getFLD_actorSEEnd() const {
    return Bdat::getIdTop(m_fpFLD_actorSE->m_fp) + Bdat::getIdCount(m_fpFLD_actorSE->m_fp);
}

const char* GfBdatRsc::getFLD_actorSELOD(unsigned int id) const {
    return _gfbrs::getFLD_actorSELOD(*m_fpFLD_actorSE, id);
}

unsigned int GfBdatRsc::getFLD_actorSEse_type(unsigned int id) const {
    return _gfbrs::getFLD_actorSEse_type(*m_fpFLD_actorSE, id);
}

unsigned int GfBdatRsc::getFLD_actorSEseName(unsigned int id) const {
    return _gfbrs::getFLD_actorSEseName(*m_fpFLD_actorSE, id);
}

float GfBdatRsc::getFLD_actorSEmax_volume_Dist(unsigned int id) const {
    return _gfbrs::getFLD_actorSEmax_volume_Dist(*m_fpFLD_actorSE, id);
}

float GfBdatRsc::getFLD_actorSEmin_volume_Dist(unsigned int id) const {
    return _gfbrs::getFLD_actorSEmin_volume_Dist(*m_fpFLD_actorSE, id);
}

unsigned int GfBdatRsc::getFLD_actorSEvolumeMAX(unsigned int id) const {
    return _gfbrs::getFLD_actorSEvolumeMAX(*m_fpFLD_actorSE, id);
}

unsigned int GfBdatRsc::getFLD_actorSEvolumeMIN(unsigned int id) const {
    return _gfbrs::getFLD_actorSEvolumeMIN(*m_fpFLD_actorSE, id);
}

float GfBdatRsc::getFLD_actorSEoffsetX(unsigned int id) const {
    return _gfbrs::getFLD_actorSEoffsetX(*m_fpFLD_actorSE, id);
}

float GfBdatRsc::getFLD_actorSEoffsetY(unsigned int id) const {
    return _gfbrs::getFLD_actorSEoffsetY(*m_fpFLD_actorSE, id);
}

float GfBdatRsc::getFLD_actorSEoffsetZ(unsigned int id) const {
    return _gfbrs::getFLD_actorSEoffsetZ(*m_fpFLD_actorSE, id);
}

}  // namespace gf
