#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatBtl.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the battle tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked
// up once (init) and a row's value read through it (get)
namespace _gfbbt {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberArtsDrName;
static unsigned char* s_memberArtsDrDebugName;
static unsigned char* s_memberArtsDrCaption;
static unsigned char* s_memberArtsDrCondCap;
static unsigned char* s_memberArtsDrTalentCap;
static unsigned char* s_memberArtsDrDriver;
static unsigned char* s_memberArtsDrWpnType;
static unsigned char* s_memberArtsDrIrType;
static unsigned char* s_memberArtsDrCondition;
static unsigned char* s_memberArtsDrActNo;
static unsigned char* s_memberArtsDrArtsType;
static unsigned char* s_memberArtsDrArtsBuff;
static unsigned char* s_memberArtsDrAtrType;
static unsigned char* s_memberArtsDrFlagNormalFlag;
static unsigned char* s_memberArtsDrFlagNormal;
static unsigned char* s_memberArtsDrFlagPierceFlag;
static unsigned char* s_memberArtsDrFlagPierce;
static unsigned char* s_memberArtsDrFlagNoRepelledFlag;
static unsigned char* s_memberArtsDrFlagNoRepelled;
static unsigned char* s_memberArtsDrNextArts;
static unsigned char* s_memberArtsDrTarget;
static unsigned char* s_memberArtsDrDistance;
static unsigned char* s_memberArtsDrRangeType;
static unsigned char* s_memberArtsDrRadius;
static unsigned char* s_memberArtsDrLength;
static unsigned char* s_memberArtsDrHate;
static unsigned char* s_memberArtsDrHitRevise;
static unsigned char* s_memberArtsDrCriRevise;
static unsigned char* s_memberArtsDrBulletID;
static unsigned char* s_memberArtsDrBulletNum;
static unsigned char* s_memberArtsDrHitFrm1;
static unsigned char* s_memberArtsDrHitFrm2;
static unsigned char* s_memberArtsDrHitFrm3;
static unsigned char* s_memberArtsDrHitFrm4;
static unsigned char* s_memberArtsDrHitFrm5;
static unsigned char* s_memberArtsDrHitFrm6;
static unsigned char* s_memberArtsDrHitFrm7;
static unsigned char* s_memberArtsDrHitFrm8;
static unsigned char* s_memberArtsDrHitFrm9;
static unsigned char* s_memberArtsDrHitFrm10;
static unsigned char* s_memberArtsDrHitFrm11;
static unsigned char* s_memberArtsDrHitFrm12;
static unsigned char* s_memberArtsDrHitFrm13;
static unsigned char* s_memberArtsDrHitFrm14;
static unsigned char* s_memberArtsDrHitFrm15;
static unsigned char* s_memberArtsDrHitFrm16;
static unsigned char* s_memberArtsDrEfp1;
static unsigned char* s_memberArtsDrEfp2;
static unsigned char* s_memberArtsDrEfp3;
static unsigned char* s_memberArtsDrEfp4;
static unsigned char* s_memberArtsDrEfp5;
static unsigned char* s_memberArtsDrEfp6;
static unsigned char* s_memberArtsDrEfp7;
static unsigned char* s_memberArtsDrEfp8;
static unsigned char* s_memberArtsDrEfp9;
static unsigned char* s_memberArtsDrEfp10;
static unsigned char* s_memberArtsDrEfp11;
static unsigned char* s_memberArtsDrEfp12;
static unsigned char* s_memberArtsDrEfp13;
static unsigned char* s_memberArtsDrEfp14;
static unsigned char* s_memberArtsDrEfp15;
static unsigned char* s_memberArtsDrEfp16;
static unsigned char* s_memberArtsDrHitDirID1;
static unsigned char* s_memberArtsDrHitDirID2;
static unsigned char* s_memberArtsDrHitDirID3;
static unsigned char* s_memberArtsDrHitDirID4;
static unsigned char* s_memberArtsDrHitDirID5;
static unsigned char* s_memberArtsDrHitDirID6;
static unsigned char* s_memberArtsDrHitDirID7;
static unsigned char* s_memberArtsDrHitDirID8;
static unsigned char* s_memberArtsDrHitDirID9;
static unsigned char* s_memberArtsDrHitDirID10;
static unsigned char* s_memberArtsDrHitDirID11;
static unsigned char* s_memberArtsDrHitDirID12;
static unsigned char* s_memberArtsDrHitDirID13;
static unsigned char* s_memberArtsDrHitDirID14;
static unsigned char* s_memberArtsDrHitDirID15;
static unsigned char* s_memberArtsDrHitDirID16;
static unsigned char* s_memberArtsDrDmgRt1;
static unsigned char* s_memberArtsDrDmgRt2;
static unsigned char* s_memberArtsDrDmgRt3;
static unsigned char* s_memberArtsDrDmgRt4;
static unsigned char* s_memberArtsDrDmgRt5;
static unsigned char* s_memberArtsDrDmgRt6;
static unsigned char* s_memberArtsDrDmgRt7;
static unsigned char* s_memberArtsDrDmgRt8;
static unsigned char* s_memberArtsDrDmgRt9;
static unsigned char* s_memberArtsDrDmgRt10;
static unsigned char* s_memberArtsDrDmgRt11;
static unsigned char* s_memberArtsDrDmgRt12;
static unsigned char* s_memberArtsDrDmgRt13;
static unsigned char* s_memberArtsDrDmgRt14;
static unsigned char* s_memberArtsDrDmgRt15;
static unsigned char* s_memberArtsDrDmgRt16;
static unsigned char* s_memberArtsDrReAct1;
static unsigned char* s_memberArtsDrReAct2;
static unsigned char* s_memberArtsDrReAct3;
static unsigned char* s_memberArtsDrReAct4;
static unsigned char* s_memberArtsDrReAct5;
static unsigned char* s_memberArtsDrReAct6;
static unsigned char* s_memberArtsDrReAct7;
static unsigned char* s_memberArtsDrReAct8;
static unsigned char* s_memberArtsDrReAct9;
static unsigned char* s_memberArtsDrReAct10;
static unsigned char* s_memberArtsDrReAct11;
static unsigned char* s_memberArtsDrReAct12;
static unsigned char* s_memberArtsDrReAct13;
static unsigned char* s_memberArtsDrReAct14;
static unsigned char* s_memberArtsDrReAct15;
static unsigned char* s_memberArtsDrReAct16;
static unsigned char* s_memberArtsDrMoveCancelFrm;
static unsigned char* s_memberArtsDrDmgMgn1;
static unsigned char* s_memberArtsDrDmgMgn2;
static unsigned char* s_memberArtsDrDmgMgn3;
static unsigned char* s_memberArtsDrDmgMgn4;
static unsigned char* s_memberArtsDrDmgMgn5;
static unsigned char* s_memberArtsDrDmgMgn6;
static unsigned char* s_memberArtsDrRecast1;
static unsigned char* s_memberArtsDrRecast2;
static unsigned char* s_memberArtsDrRecast3;
static unsigned char* s_memberArtsDrRecast4;
static unsigned char* s_memberArtsDrRecast5;
static unsigned char* s_memberArtsDrRecast6;
static unsigned char* s_memberArtsDrAtrNum;
static unsigned char* s_memberArtsDrEnhance1;
static unsigned char* s_memberArtsDrEnhance2;
static unsigned char* s_memberArtsDrEnhance3;
static unsigned char* s_memberArtsDrEnhance4;
static unsigned char* s_memberArtsDrEnhance5;
static unsigned char* s_memberArtsDrEnhance6;
static unsigned char* s_memberArtsDrReleaseLv1;
static unsigned char* s_memberArtsDrReleaseLv2;
static unsigned char* s_memberArtsDrReleaseLv3;
static unsigned char* s_memberArtsDrReleaseLv4;
static unsigned char* s_memberArtsDrReleaseLv5;
static unsigned char* s_memberArtsDrNeedWP2;
static unsigned char* s_memberArtsDrNeedWP3;
static unsigned char* s_memberArtsDrNeedWP4;
static unsigned char* s_memberArtsDrNeedWP5;
static unsigned char* s_memberArtsDrUI;
static unsigned char* s_memberArtsDrPriority;
static unsigned char* s_memberArtsBlName;
static unsigned char* s_memberArtsBlDebugName;
static unsigned char* s_memberArtsBlCaption;
static unsigned char* s_memberArtsBlWpnType;
static unsigned char* s_memberArtsBlCmnBlType;
static unsigned char* s_memberArtsBlSpLv;
static unsigned char* s_memberArtsBlActNo;
static unsigned char* s_memberArtsBlArtsType;
static unsigned char* s_memberArtsBlArtsBuff;
static unsigned char* s_memberArtsBlFlagcommonFlag;
static unsigned char* s_memberArtsBlFlagcommon;
static unsigned char* s_memberArtsBlFlagPierceFlag;
static unsigned char* s_memberArtsBlFlagPierce;
static unsigned char* s_memberArtsBlTarget;
static unsigned char* s_memberArtsBlDistance;
static unsigned char* s_memberArtsBlRangeType;
static unsigned char* s_memberArtsBlRadius;
static unsigned char* s_memberArtsBlLength;
static unsigned char* s_memberArtsBlAtr;
static unsigned char* s_memberArtsBlHate;
static unsigned char* s_memberArtsBlHitRevise;
static unsigned char* s_memberArtsBlCriRevise;
static unsigned char* s_memberArtsBlBulletID;
static unsigned char* s_memberArtsBlBulletNum;
static unsigned char* s_memberArtsBlHitFrm1;
static unsigned char* s_memberArtsBlHitFrm2;
static unsigned char* s_memberArtsBlHitFrm3;
static unsigned char* s_memberArtsBlHitFrm4;
static unsigned char* s_memberArtsBlHitFrm5;
static unsigned char* s_memberArtsBlHitFrm6;
static unsigned char* s_memberArtsBlHitFrm7;
static unsigned char* s_memberArtsBlHitFrm8;
static unsigned char* s_memberArtsBlHitFrm9;
static unsigned char* s_memberArtsBlHitFrm10;
static unsigned char* s_memberArtsBlHitFrm11;
static unsigned char* s_memberArtsBlHitFrm12;
static unsigned char* s_memberArtsBlHitFrm13;
static unsigned char* s_memberArtsBlHitFrm14;
static unsigned char* s_memberArtsBlHitFrm15;
static unsigned char* s_memberArtsBlHitFrm16;
static unsigned char* s_memberArtsBlEfp1;
static unsigned char* s_memberArtsBlEfp2;
static unsigned char* s_memberArtsBlEfp3;
static unsigned char* s_memberArtsBlEfp4;
static unsigned char* s_memberArtsBlEfp5;
static unsigned char* s_memberArtsBlEfp6;
static unsigned char* s_memberArtsBlEfp7;
static unsigned char* s_memberArtsBlEfp8;
static unsigned char* s_memberArtsBlEfp9;
static unsigned char* s_memberArtsBlEfp10;
static unsigned char* s_memberArtsBlEfp11;
static unsigned char* s_memberArtsBlEfp12;
static unsigned char* s_memberArtsBlEfp13;
static unsigned char* s_memberArtsBlEfp14;
static unsigned char* s_memberArtsBlEfp15;
static unsigned char* s_memberArtsBlEfp16;
static unsigned char* s_memberArtsBlHitDirID1;
static unsigned char* s_memberArtsBlHitDirID2;
static unsigned char* s_memberArtsBlHitDirID3;
static unsigned char* s_memberArtsBlHitDirID4;
static unsigned char* s_memberArtsBlHitDirID5;
static unsigned char* s_memberArtsBlHitDirID6;
static unsigned char* s_memberArtsBlHitDirID7;
static unsigned char* s_memberArtsBlHitDirID8;
static unsigned char* s_memberArtsBlHitDirID9;
static unsigned char* s_memberArtsBlHitDirID10;
static unsigned char* s_memberArtsBlHitDirID11;
static unsigned char* s_memberArtsBlHitDirID12;
static unsigned char* s_memberArtsBlHitDirID13;
static unsigned char* s_memberArtsBlHitDirID14;
static unsigned char* s_memberArtsBlHitDirID15;
static unsigned char* s_memberArtsBlHitDirID16;
static unsigned char* s_memberArtsBlDmgRt1;
static unsigned char* s_memberArtsBlDmgRt2;
static unsigned char* s_memberArtsBlDmgRt3;
static unsigned char* s_memberArtsBlDmgRt4;
static unsigned char* s_memberArtsBlDmgRt5;
static unsigned char* s_memberArtsBlDmgRt6;
static unsigned char* s_memberArtsBlDmgRt7;
static unsigned char* s_memberArtsBlDmgRt8;
static unsigned char* s_memberArtsBlDmgRt9;
static unsigned char* s_memberArtsBlDmgRt10;
static unsigned char* s_memberArtsBlDmgRt11;
static unsigned char* s_memberArtsBlDmgRt12;
static unsigned char* s_memberArtsBlDmgRt13;
static unsigned char* s_memberArtsBlDmgRt14;
static unsigned char* s_memberArtsBlDmgRt15;
static unsigned char* s_memberArtsBlDmgRt16;
static unsigned char* s_memberArtsBlReAct1;
static unsigned char* s_memberArtsBlReAct2;
static unsigned char* s_memberArtsBlReAct3;
static unsigned char* s_memberArtsBlReAct4;
static unsigned char* s_memberArtsBlReAct5;
static unsigned char* s_memberArtsBlReAct6;
static unsigned char* s_memberArtsBlReAct7;
static unsigned char* s_memberArtsBlReAct8;
static unsigned char* s_memberArtsBlReAct9;
static unsigned char* s_memberArtsBlReAct10;
static unsigned char* s_memberArtsBlReAct11;
static unsigned char* s_memberArtsBlReAct12;
static unsigned char* s_memberArtsBlReAct13;
static unsigned char* s_memberArtsBlReAct14;
static unsigned char* s_memberArtsBlReAct15;
static unsigned char* s_memberArtsBlReAct16;
static unsigned char* s_memberArtsBlDmgMgn1;
static unsigned char* s_memberArtsBlDmgMgn2;
static unsigned char* s_memberArtsBlDmgMgn3;
static unsigned char* s_memberArtsBlDmgMgn4;
static unsigned char* s_memberArtsBlDmgMgn5;
static unsigned char* s_memberArtsBlDmgMgn6;
static unsigned char* s_memberArtsBlAtrNum;
static unsigned char* s_memberArtsBlEnhance1;
static unsigned char* s_memberArtsBlEnhance2;
static unsigned char* s_memberArtsBlEnhance3;
static unsigned char* s_memberArtsBlEnhance4;
static unsigned char* s_memberArtsBlEnhance5;
static unsigned char* s_memberArtsBlEnhance6;
static unsigned char* s_memberArtsBlBtnType;
static unsigned char* s_memberArtsBlBtnChal1;
static unsigned char* s_memberArtsBlUI;
static unsigned char* s_memberArtsBlSpName;
static unsigned char* s_memberArtsBlSpDebugName;
static unsigned char* s_memberArtsBlSpCaption;
static unsigned char* s_memberArtsBlSpWpnType;
static unsigned char* s_memberArtsBlSpCondition;
static unsigned char* s_memberArtsBlSpCmnBlType;
static unsigned char* s_memberArtsBlSpActNoDr;
static unsigned char* s_memberArtsBlSpActNoBl;
static unsigned char* s_memberArtsBlSpActNoBl2;
static unsigned char* s_memberArtsBlSpBuddyDr;
static unsigned char* s_memberArtsBlSpAddBl;
static unsigned char* s_memberArtsBlSpActType;
static unsigned char* s_memberArtsBlSpPC01;
static unsigned char* s_memberArtsBlSpPC02;
static unsigned char* s_memberArtsBlSpPC03;
static unsigned char* s_memberArtsBlSpPC06;
static unsigned char* s_memberArtsBlSpArtsType;
static unsigned char* s_memberArtsBlSpArtsBuff;
static unsigned char* s_memberArtsBlSpFlagPierceFlag;
static unsigned char* s_memberArtsBlSpFlagPierce;
static unsigned char* s_memberArtsBlSpFlagNoMoveFlag;
static unsigned char* s_memberArtsBlSpFlagNoMove;
static unsigned char* s_memberArtsBlSpTarget;
static unsigned char* s_memberArtsBlSpDistance;
static unsigned char* s_memberArtsBlSpRangeType;
static unsigned char* s_memberArtsBlSpRadius;
static unsigned char* s_memberArtsBlSpLength;
static unsigned char* s_memberArtsBlSpAtr;
static unsigned char* s_memberArtsBlSpHate;
static unsigned char* s_memberArtsBlSpHitRevise;
static unsigned char* s_memberArtsBlSpCriRevise;
static unsigned char* s_memberArtsBlSpBulletID;
static unsigned char* s_memberArtsBlSpBulletEffID;
static unsigned char* s_memberArtsBlSpBulletNum;
static unsigned char* s_memberArtsBlSpHitFrm1;
static unsigned char* s_memberArtsBlSpHitFrm2;
static unsigned char* s_memberArtsBlSpHitFrm3;
static unsigned char* s_memberArtsBlSpHitFrm4;
static unsigned char* s_memberArtsBlSpHitFrm5;
static unsigned char* s_memberArtsBlSpHitFrm6;
static unsigned char* s_memberArtsBlSpHitFrm7;
static unsigned char* s_memberArtsBlSpHitFrm8;
static unsigned char* s_memberArtsBlSpHitFrm9;
static unsigned char* s_memberArtsBlSpHitFrm10;
static unsigned char* s_memberArtsBlSpHitFrm11;
static unsigned char* s_memberArtsBlSpHitFrm12;
static unsigned char* s_memberArtsBlSpHitFrm13;
static unsigned char* s_memberArtsBlSpHitFrm14;
static unsigned char* s_memberArtsBlSpHitFrm15;
static unsigned char* s_memberArtsBlSpHitFrm16;
static unsigned char* s_memberArtsBlSpEfp1;
static unsigned char* s_memberArtsBlSpEfp2;
static unsigned char* s_memberArtsBlSpEfp3;
static unsigned char* s_memberArtsBlSpEfp4;
static unsigned char* s_memberArtsBlSpEfp5;
static unsigned char* s_memberArtsBlSpEfp6;
static unsigned char* s_memberArtsBlSpEfp7;
static unsigned char* s_memberArtsBlSpEfp8;
static unsigned char* s_memberArtsBlSpEfp9;
static unsigned char* s_memberArtsBlSpEfp10;
static unsigned char* s_memberArtsBlSpEfp11;
static unsigned char* s_memberArtsBlSpEfp12;
static unsigned char* s_memberArtsBlSpEfp13;
static unsigned char* s_memberArtsBlSpEfp14;
static unsigned char* s_memberArtsBlSpEfp15;
static unsigned char* s_memberArtsBlSpEfp16;
static unsigned char* s_memberArtsBlSpHitDirID1;
static unsigned char* s_memberArtsBlSpHitDirID2;
static unsigned char* s_memberArtsBlSpHitDirID3;
static unsigned char* s_memberArtsBlSpHitDirID4;
static unsigned char* s_memberArtsBlSpHitDirID5;
static unsigned char* s_memberArtsBlSpHitDirID6;
static unsigned char* s_memberArtsBlSpHitDirID7;
static unsigned char* s_memberArtsBlSpHitDirID8;
static unsigned char* s_memberArtsBlSpHitDirID9;
static unsigned char* s_memberArtsBlSpHitDirID10;
static unsigned char* s_memberArtsBlSpHitDirID11;
static unsigned char* s_memberArtsBlSpHitDirID12;
static unsigned char* s_memberArtsBlSpHitDirID13;
static unsigned char* s_memberArtsBlSpHitDirID14;
static unsigned char* s_memberArtsBlSpHitDirID15;
static unsigned char* s_memberArtsBlSpHitDirID16;
static unsigned char* s_memberArtsBlSpDmgRt1;
static unsigned char* s_memberArtsBlSpDmgRt2;
static unsigned char* s_memberArtsBlSpDmgRt3;
static unsigned char* s_memberArtsBlSpDmgRt4;
static unsigned char* s_memberArtsBlSpDmgRt5;
static unsigned char* s_memberArtsBlSpDmgRt6;
static unsigned char* s_memberArtsBlSpDmgRt7;
static unsigned char* s_memberArtsBlSpDmgRt8;
static unsigned char* s_memberArtsBlSpDmgRt9;
static unsigned char* s_memberArtsBlSpDmgRt10;
static unsigned char* s_memberArtsBlSpDmgRt11;
static unsigned char* s_memberArtsBlSpDmgRt12;
static unsigned char* s_memberArtsBlSpDmgRt13;
static unsigned char* s_memberArtsBlSpDmgRt14;
static unsigned char* s_memberArtsBlSpDmgRt15;
static unsigned char* s_memberArtsBlSpDmgRt16;
static unsigned char* s_memberArtsBlSpReAct1;
static unsigned char* s_memberArtsBlSpReAct2;
static unsigned char* s_memberArtsBlSpReAct3;
static unsigned char* s_memberArtsBlSpReAct4;
static unsigned char* s_memberArtsBlSpReAct5;
static unsigned char* s_memberArtsBlSpReAct6;
static unsigned char* s_memberArtsBlSpReAct7;
static unsigned char* s_memberArtsBlSpReAct8;
static unsigned char* s_memberArtsBlSpReAct9;
static unsigned char* s_memberArtsBlSpReAct10;
static unsigned char* s_memberArtsBlSpReAct11;
static unsigned char* s_memberArtsBlSpReAct12;
static unsigned char* s_memberArtsBlSpReAct13;
static unsigned char* s_memberArtsBlSpReAct14;
static unsigned char* s_memberArtsBlSpReAct15;
static unsigned char* s_memberArtsBlSpReAct16;
static unsigned char* s_memberArtsBlSpDmgMgn;
static unsigned char* s_memberArtsBlSpRecast;
static unsigned char* s_memberArtsBlSpAtrNum;
static unsigned char* s_memberArtsBlSpEnhance;
static unsigned char* s_memberArtsBlSpBtnType;
static unsigned char* s_memberArtsBlSpBtnChal1;
static unsigned char* s_memberArtsBlSpCamera1;
static unsigned char* s_memberArtsBlSpCamera2;
static unsigned char* s_memberArtsBlSpCamera3;
static unsigned char* s_memberArtsBlSpCameraCT1;
static unsigned char* s_memberArtsBlSpCameraCT2;
static unsigned char* s_memberArtsBlSpCameraEndf;
static unsigned char* s_memberArtsBlSpHitEff;
static unsigned char* s_memberGrowLevelExp;
static unsigned char* s_memberGrowLevelExp2;
static unsigned char* s_memberGrowEnemyExp;
static unsigned char* s_memberGrowEnemyWP;
static unsigned char* s_memberGrowEnemySP;
static unsigned char* s_memberGrowEnemyGold;
static unsigned char* s_memberGrowGoldDivide;
static unsigned char* s_memberLv_RevExpRevHigh;
static unsigned char* s_memberLv_RevExpRevLow;
static unsigned char* s_memberLv_RevDamageRevHigh;
static unsigned char* s_memberLv_RevDamageRevLow;
static unsigned char* s_memberWpn_EnRscR;
static unsigned char* s_memberWpn_EnRscL;
static unsigned char* s_memberWpn_EnTypeRange;
static unsigned char* s_memberWpn_EnDamage;
static unsigned char* s_memberWpn_EnStability;
static unsigned char* s_memberBTL_ClassName;
static unsigned char* s_memberBTL_ClassRole1;
static unsigned char* s_memberBTL_ClassRole2;
static unsigned char* s_memberBTL_ClassRole3;
static unsigned char* s_memberBTL_ClassDamageDown;
static unsigned char* s_memberBTL_ClassDamageUP;
static unsigned char* s_memberBTL_ClassHealUP;
static unsigned char* s_memberBTL_ClassAutoHate;
static unsigned char* s_memberBTL_ClassArtsHate;
static unsigned char* s_memberBTL_EnhanceEnhanceEffect;
static unsigned char* s_memberBTL_EnhanceParam1;
static unsigned char* s_memberBTL_EnhanceParam2;
static unsigned char* s_memberBTL_EnhanceCaption;
static unsigned char* s_memberBTL_EnhanceCaption2;
static unsigned char* s_memberBTL_EnhanceEffCategory;
static unsigned char* s_memberBTL_EnhanceEffIcon;
static unsigned char* s_memberBTL_EnhanceEffFlagConditionFlag;
static unsigned char* s_memberBTL_EnhanceEffFlagCondition;
static unsigned char* s_memberBTL_EnhanceEffFlagUIFlag;
static unsigned char* s_memberBTL_EnhanceEffFlagUI;
static unsigned char* s_memberBTL_EnhanceEffParam;
static unsigned char* s_memberBTL_EnhanceEffName;
static unsigned char* s_memberBTL_EnhanceEffDirect;
static unsigned char* s_memberBTL_EnhanceEffSortCat;
static unsigned char* s_memberBTL_Skill_BlName;
static unsigned char* s_memberBTL_Skill_BlDebugName;
static unsigned char* s_memberBTL_Skill_BlEnhance1;
static unsigned char* s_memberBTL_Skill_BlEnhance2;
static unsigned char* s_memberBTL_Skill_BlEnhance3;
static unsigned char* s_memberBTL_Skill_BlEnhance4;
static unsigned char* s_memberBTL_Skill_BlEnhance5;
static unsigned char* s_memberBTL_Skill_BlFlagcommonFlag;
static unsigned char* s_memberBTL_Skill_BlFlagcommon;
static unsigned char* s_memberBTL_Skill_BlTank;
static unsigned char* s_memberBTL_Skill_BlAttacker;
static unsigned char* s_memberBTL_Skill_BlHealer;
static unsigned char* s_memberBTL_Skill_BlUI;
static unsigned char* s_memberBTL_Skill_DrName;
static unsigned char* s_memberBTL_Skill_DrDebugName;
static unsigned char* s_memberBTL_Skill_DrEnhance;
static unsigned char* s_memberBTL_Skill_DrUI;
static unsigned char* s_memberBTL_BuffName;
static unsigned char* s_memberBTL_BuffDebugName;
static unsigned char* s_memberBTL_BuffCaption;
static unsigned char* s_memberBTL_BuffBaseNum;
static unsigned char* s_memberBTL_BuffBaseTime;
static unsigned char* s_memberBTL_BuffBaseRecast;
static unsigned char* s_memberBTL_BuffBaseProb;
static unsigned char* s_memberBTL_BuffInterval;
static unsigned char* s_memberBTL_BuffEffect;
static unsigned char* s_memberBTL_BuffIcon;
static unsigned char* s_memberBTL_Bl_PersonalityFlagcommonFlag;
static unsigned char* s_memberBTL_Bl_PersonalityFlagcommon;
static unsigned char* s_memberBTL_Bl_PersonalityKizunaBase;
static unsigned char* s_memberBTL_Bl_PersonalityVoiceID;
static unsigned char* s_memberBTL_Bl_KizunaLinkLinkNum;
static unsigned char* s_memberBTL_Bl_KizunaLinkDeadNum;
static unsigned char* s_memberBTL_Bl_KizunaLinkAppStNum;
static unsigned char* s_memberBTL_Bl_KizunaLinkAppEndNum;
static unsigned char* s_memberBTL_Bl_KizunaLinkAppCond;
static unsigned char* s_memberBTL_Bl_KizunaLinkAppCondNum;
static unsigned char* s_memberBTL_Bl_KizunaLinkReJudgef;
static unsigned char* s_memberBTL_Bl_KizunaLinkSpActType;
static unsigned char* s_memberBTL_Bl_KizunaLinkSpActNum;
static unsigned char* s_memberBTL_Bl_KizunaLinkSpActf;
static unsigned char* s_memberBTL_Bl_KizunaLinkStandDir;
static unsigned char* s_memberBTL_Bl_KizunaLinkSetKizunaLink1;
static unsigned char* s_memberBTL_Bl_KizunaLinkSetKizunaLink2;
static unsigned char* s_memberBTL_Bl_KizunaLinkSetLinkChType;
static unsigned char* s_memberBTL_Bl_KizunaLinkSetLinkChNum;
static unsigned char* s_memberBTL_Bl_KizunaLinkSetVoiceID;
static unsigned char* s_memberBTL_TestSettingDr1;
static unsigned char* s_memberBTL_TestSettingDr1Lv;
static unsigned char* s_memberBTL_TestSettingDr1Bl1;
static unsigned char* s_memberBTL_TestSettingDr1Bl2;
static unsigned char* s_memberBTL_TestSettingDr1Bl3;
static unsigned char* s_memberBTL_TestSettingDr2;
static unsigned char* s_memberBTL_TestSettingDr2Lv;
static unsigned char* s_memberBTL_TestSettingDr2Bl1;
static unsigned char* s_memberBTL_TestSettingDr2Bl2;
static unsigned char* s_memberBTL_TestSettingDr2Bl3;
static unsigned char* s_memberBTL_TestSettingDr3;
static unsigned char* s_memberBTL_TestSettingDr3Lv;
static unsigned char* s_memberBTL_TestSettingDr3Bl1;
static unsigned char* s_memberBTL_TestSettingDr3Bl2;
static unsigned char* s_memberBTL_TestSettingDr3Bl3;
static unsigned char* s_memberBTL_HanaBaseNCondNum;
static unsigned char* s_memberBTL_HanaBaseECondNum;
static unsigned char* s_memberBTL_HanaBaseNArtsNum;
static unsigned char* s_memberBTL_HanaBaseCircuit1Num;
static unsigned char* s_memberBTL_HanaBaseCircuit2Num;
static unsigned char* s_memberBTL_HanaBaseCircuit3Num;
static unsigned char* s_memberBTL_HanaBaseCircuit4Num;
static unsigned char* s_memberBTL_HanaBaseCircuit5Num;
static unsigned char* s_memberBTL_HanaBaseCircuit6Num;
static unsigned char* s_memberBTL_HanaBaseUI;
static unsigned char* s_memberBTL_HanaPowerPowerNum1;
static unsigned char* s_memberBTL_HanaPowerPowerNum2;
static unsigned char* s_memberBTL_HanaPowerPowerNum3;
static unsigned char* s_memberBTL_HanaPowerEtherNum1;
static unsigned char* s_memberBTL_HanaPowerEtherNum2;
static unsigned char* s_memberBTL_HanaPowerEtherNum3;
static unsigned char* s_memberBTL_HanaChipsetRoleParts;
static unsigned char* s_memberBTL_HanaChipsetAtrParts;
static unsigned char* s_memberBTL_HanaChipsetNArtsParts1;
static unsigned char* s_memberBTL_HanaChipsetNArtsParts2;
static unsigned char* s_memberBTL_HanaChipsetNArtsParts3;
static unsigned char* s_memberBTL_HanaChipsetNCondParts1;
static unsigned char* s_memberBTL_HanaChipsetNCondParts2;
static unsigned char* s_memberBTL_HanaChipsetNCondParts3;
static unsigned char* s_memberBTL_HanaChipsetUI;
static unsigned char* s_memberWildcardDatavalueF4;
static unsigned char* s_memberWildcardDatavalueU2;
static unsigned char* s_memberVo_Field_FilterTargetFile;
static unsigned char* s_memberVo_Field_FilterCondition;
static unsigned char* s_memberVo_Field_FilterChangeFile;
static unsigned char* s_memberBTL_DifSettingDebugName;
static unsigned char* s_memberBTL_DifSettingParamMin;
static unsigned char* s_memberBTL_DifSettingParamMax;
static unsigned char* s_memberBTL_DifSettingInterval;
static unsigned char* s_memberBTL_DifSettingNormal;
static unsigned char* s_memberBTL_DifSettingEasy;
static unsigned char* s_memberBTL_DifSettingHard;
static unsigned char* s_memberBTL_DifSettingUlt;
static unsigned char* s_memberBTL_DifSettingConditionOri;
static unsigned char* s_memberBTL_DifSettingConditionIra;
static unsigned char* s_memberBTL_DifSettingFlagOriFlag;
static unsigned char* s_memberBTL_DifSettingFlagOri;
static unsigned char* s_memberBTL_DifSettingFlagIraFlag;
static unsigned char* s_memberBTL_DifSettingFlagIra;
static unsigned char* s_memberBTL_ChBtlRewardSetGoldMin;
static unsigned char* s_memberBTL_ChBtlRewardSetGoldMax;
static unsigned char* s_memberBTL_ChBtlRewardSetGoldPopMin;
static unsigned char* s_memberBTL_ChBtlRewardSetGoldPopMax;
static unsigned char* s_memberBTL_ChBtlRewardSetItemNumMin;
static unsigned char* s_memberBTL_ChBtlRewardSetItemNumMax;
static unsigned char* s_memberBTL_ChBtlRewardSetItemValueMin;
static unsigned char* s_memberBTL_ChBtlRewardSetItemValueMax;
static unsigned char* s_memberBTL_ChBtlRewardSetUpCategory1;
static unsigned char* s_memberBTL_ChBtlRewardSetUpCategory2;
static unsigned char* s_memberBTL_ChBtlRewardSetDownCategory1;
static unsigned char* s_memberBTL_ChBtlRewardSetDownCategory2;
static unsigned char* s_memberBTL_ChBtlRewardSetUpItemID1;
static unsigned char* s_memberBTL_ChBtlRewardSetUpItemID2;
static unsigned char* s_memberBTL_ChBtlRewardSetUpItemID3;
static unsigned char* s_memberBTL_ChBtlRewardSetUpItemID4;
static unsigned char* s_memberBTL_ChBtlRewardSetDownItemID1;
static unsigned char* s_memberBTL_ChBtlRewardSetDownItemID2;
static unsigned char* s_memberBTL_ChBtlRewardSetDownItemID3;
static unsigned char* s_memberBTL_ChBtlRewardSetDownItemID4;
static unsigned char* s_memberBTL_ChBtlRewardItemItemID;
static unsigned char* s_memberBTL_ChBtlRewardItemItemValue;
static unsigned char* s_memberBTL_ChBtlRewardItemParam1;
static unsigned char* s_memberBTL_ChBtlName;
static unsigned char* s_memberBTL_ChBtlDebugName;
static unsigned char* s_memberBTL_ChBtlListNum;
static unsigned char* s_memberBTL_ChBtlDifficult;
static unsigned char* s_memberBTL_ChBtlWave;
static unsigned char* s_memberBTL_ChBtlCaption;
static unsigned char* s_memberBTL_ChBtlMapJump;
static unsigned char* s_memberBTL_ChBtlWeather;
static unsigned char* s_memberBTL_ChBtlType;
static unsigned char* s_memberBTL_ChBtlNeedDefeat;
static unsigned char* s_memberBTL_ChBtlMaxLevel;
static unsigned char* s_memberBTL_ChBtlMaxWpnRank;
static unsigned char* s_memberBTL_ChBtlWpnRevTable;
static unsigned char* s_memberBTL_ChBtlTimeLimit;
static unsigned char* s_memberBTL_ChBtlJoinNumber;
static unsigned char* s_memberBTL_ChBtlDriver1;
static unsigned char* s_memberBTL_ChBtlDriver2;
static unsigned char* s_memberBTL_ChBtlDriver3;
static unsigned char* s_memberBTL_ChBtlNeedItem;
static unsigned char* s_memberBTL_ChBtlCondition;
static unsigned char* s_memberBTL_ChBtlConditionCap;
static unsigned char* s_memberBTL_ChBtlCondition2;
static unsigned char* s_memberBTL_ChBtlConditionCap2;
static unsigned char* s_memberBTL_ChBtlHideCondition;
static unsigned char* s_memberBTL_ChBtlFlagHideFlag;
static unsigned char* s_memberBTL_ChBtlFlagHide;
static unsigned char* s_memberBTL_ChBtlTresureSet1;
static unsigned char* s_memberBTL_ChBtlTresureSet2;
static unsigned char* s_memberBTL_ChBtlTresureSet3;
static unsigned char* s_memberBTL_ChBtlTresureNeed1;
static unsigned char* s_memberBTL_ChBtlTresureNeed2;
static unsigned char* s_memberBTL_ChBtlTresureNeed3;
static unsigned char* s_memberBTL_ChBtlTresureResource1;
static unsigned char* s_memberBTL_ChBtlTresureResource2;
static unsigned char* s_memberBTL_ChBtlTresureResource3;
static unsigned char* s_memberBTL_ChBtlClearReward;
static unsigned char* s_memberBTL_ChBtlEvent;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg1;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg2;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg3;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg4;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg5;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg6;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg7;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg8;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg9;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg10;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg11;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg12;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg13;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg14;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg15;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg16;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg17;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg18;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg19;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg20;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg21;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg22;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg23;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg24;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg25;
static unsigned char* s_memberBTL_ChBtlWpnRevWpnDmg26;
static unsigned char* s_memberBTL_IrGroupRevGroupRev1;
static unsigned char* s_memberBTL_IrGroupRevGroupRev2;
static unsigned char* s_memberBTL_IrGroupRevGroupRev3;

void initArtsDrName(const CBdatWrapper& bdat) {
    s_memberArtsDrName = bdat.getMember("Name");
}

unsigned int getArtsDrName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrName, id, 2);
    }
    return 0;
}

void initArtsDrDebugName(const CBdatWrapper& bdat) {
    s_memberArtsDrDebugName = bdat.getMember("DebugName");
}

void initArtsDrCaption(const CBdatWrapper& bdat) {
    s_memberArtsDrCaption = bdat.getMember("Caption");
}

unsigned int getArtsDrCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrCaption, id, 2);
    }
    return 0;
}

void initArtsDrCondCap(const CBdatWrapper& bdat) {
    s_memberArtsDrCondCap = bdat.getMember("CondCap");
}

unsigned int getArtsDrCondCap(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrCondCap != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrCondCap, id, 2);
    }
    return 0;
}

void initArtsDrTalentCap(const CBdatWrapper& bdat) {
    s_memberArtsDrTalentCap = bdat.getMember("TalentCap");
}

unsigned int getArtsDrTalentCap(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrTalentCap != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrTalentCap, id, 2);
    }
    return 0;
}

void initArtsDrDriver(const CBdatWrapper& bdat) {
    s_memberArtsDrDriver = bdat.getMember("Driver");
}

unsigned int getArtsDrDriver(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrDriver != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrDriver, id, 1);
    }
    return 0;
}

void initArtsDrWpnType(const CBdatWrapper& bdat) {
    s_memberArtsDrWpnType = bdat.getMember("WpnType");
}

unsigned int getArtsDrWpnType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrWpnType, id, 1);
    }
    return 0;
}

void initArtsDrIrType(const CBdatWrapper& bdat) {
    s_memberArtsDrIrType = bdat.getMember("IrType");
}

unsigned int getArtsDrIrType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrIrType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrIrType, id, 1);
    }
    return 0;
}

void initArtsDrCondition(const CBdatWrapper& bdat) {
    s_memberArtsDrCondition = bdat.getMember("Condition");
}

void initArtsDrActNo(const CBdatWrapper& bdat) {
    s_memberArtsDrActNo = bdat.getMember("ActNo");
}

void initArtsDrArtsType(const CBdatWrapper& bdat) {
    s_memberArtsDrArtsType = bdat.getMember("ArtsType");
}

unsigned int getArtsDrArtsType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrArtsType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrArtsType, id, 1);
    }
    return 0;
}

void initArtsDrArtsBuff(const CBdatWrapper& bdat) {
    s_memberArtsDrArtsBuff = bdat.getMember("ArtsBuff");
}

void initArtsDrAtrType(const CBdatWrapper& bdat) {
    s_memberArtsDrAtrType = bdat.getMember("AtrType");
}

void initArtsDrFlagNormal(const CBdatWrapper& bdat) {
    s_memberArtsDrFlagNormalFlag = bdat.getMember("Flag");
    s_memberArtsDrFlagNormal = bdat.getMember("Normal");
}
bool isArtsDrFlagNormal(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrFlagNormalFlag != nullptr && s_memberArtsDrFlagNormal != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberArtsDrFlagNormalFlag, id, s_memberArtsDrFlagNormal) != 0;
    }
    return false;
}


void initArtsDrFlagPierce(const CBdatWrapper& bdat) {
    s_memberArtsDrFlagPierceFlag = bdat.getMember("Flag");
    s_memberArtsDrFlagPierce = bdat.getMember("Pierce");
}
bool isArtsDrFlagPierce(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrFlagPierceFlag != nullptr && s_memberArtsDrFlagPierce != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberArtsDrFlagPierceFlag, id, s_memberArtsDrFlagPierce) != 0;
    }
    return false;
}


void initArtsDrFlagNoRepelled(const CBdatWrapper& bdat) {
    s_memberArtsDrFlagNoRepelledFlag = bdat.getMember("Flag");
    s_memberArtsDrFlagNoRepelled = bdat.getMember("NoRepelled");
}
bool isArtsDrFlagNoRepelled(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrFlagNoRepelledFlag != nullptr && s_memberArtsDrFlagNoRepelled != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberArtsDrFlagNoRepelledFlag, id, s_memberArtsDrFlagNoRepelled) != 0;
    }
    return false;
}


void initArtsDrNextArts(const CBdatWrapper& bdat) {
    s_memberArtsDrNextArts = bdat.getMember("NextArts");
}

void initArtsDrTarget(const CBdatWrapper& bdat) {
    s_memberArtsDrTarget = bdat.getMember("Target");
}

void initArtsDrDistance(const CBdatWrapper& bdat) {
    s_memberArtsDrDistance = bdat.getMember("Distance");
}

void initArtsDrRangeType(const CBdatWrapper& bdat) {
    s_memberArtsDrRangeType = bdat.getMember("RangeType");
}

void initArtsDrRadius(const CBdatWrapper& bdat) {
    s_memberArtsDrRadius = bdat.getMember("Radius");
}

void initArtsDrLength(const CBdatWrapper& bdat) {
    s_memberArtsDrLength = bdat.getMember("Length");
}

void initArtsDrHate(const CBdatWrapper& bdat) {
    s_memberArtsDrHate = bdat.getMember("Hate");
}

void initArtsDrHitRevise(const CBdatWrapper& bdat) {
    s_memberArtsDrHitRevise = bdat.getMember("HitRevise");
}

void initArtsDrCriRevise(const CBdatWrapper& bdat) {
    s_memberArtsDrCriRevise = bdat.getMember("CriRevise");
}

void initArtsDrBulletID(const CBdatWrapper& bdat) {
    s_memberArtsDrBulletID = bdat.getMember("BulletID");
}

void initArtsDrBulletNum(const CBdatWrapper& bdat) {
    s_memberArtsDrBulletNum = bdat.getMember("BulletNum");
}

void initArtsDrHitFrm1(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm1 = bdat.getMember("HitFrm1");
}

void initArtsDrHitFrm2(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm2 = bdat.getMember("HitFrm2");
}

void initArtsDrHitFrm3(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm3 = bdat.getMember("HitFrm3");
}

void initArtsDrHitFrm4(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm4 = bdat.getMember("HitFrm4");
}

void initArtsDrHitFrm5(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm5 = bdat.getMember("HitFrm5");
}

void initArtsDrHitFrm6(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm6 = bdat.getMember("HitFrm6");
}

void initArtsDrHitFrm7(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm7 = bdat.getMember("HitFrm7");
}

void initArtsDrHitFrm8(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm8 = bdat.getMember("HitFrm8");
}

void initArtsDrHitFrm9(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm9 = bdat.getMember("HitFrm9");
}

void initArtsDrHitFrm10(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm10 = bdat.getMember("HitFrm10");
}

void initArtsDrHitFrm11(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm11 = bdat.getMember("HitFrm11");
}

void initArtsDrHitFrm12(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm12 = bdat.getMember("HitFrm12");
}

void initArtsDrHitFrm13(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm13 = bdat.getMember("HitFrm13");
}

void initArtsDrHitFrm14(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm14 = bdat.getMember("HitFrm14");
}

void initArtsDrHitFrm15(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm15 = bdat.getMember("HitFrm15");
}

void initArtsDrHitFrm16(const CBdatWrapper& bdat) {
    s_memberArtsDrHitFrm16 = bdat.getMember("HitFrm16");
}

void initArtsDrEfp1(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp1 = bdat.getMember("Efp1");
}

void initArtsDrEfp2(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp2 = bdat.getMember("Efp2");
}

void initArtsDrEfp3(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp3 = bdat.getMember("Efp3");
}

void initArtsDrEfp4(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp4 = bdat.getMember("Efp4");
}

void initArtsDrEfp5(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp5 = bdat.getMember("Efp5");
}

void initArtsDrEfp6(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp6 = bdat.getMember("Efp6");
}

void initArtsDrEfp7(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp7 = bdat.getMember("Efp7");
}

void initArtsDrEfp8(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp8 = bdat.getMember("Efp8");
}

void initArtsDrEfp9(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp9 = bdat.getMember("Efp9");
}

void initArtsDrEfp10(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp10 = bdat.getMember("Efp10");
}

void initArtsDrEfp11(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp11 = bdat.getMember("Efp11");
}

void initArtsDrEfp12(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp12 = bdat.getMember("Efp12");
}

void initArtsDrEfp13(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp13 = bdat.getMember("Efp13");
}

void initArtsDrEfp14(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp14 = bdat.getMember("Efp14");
}

void initArtsDrEfp15(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp15 = bdat.getMember("Efp15");
}

void initArtsDrEfp16(const CBdatWrapper& bdat) {
    s_memberArtsDrEfp16 = bdat.getMember("Efp16");
}

void initArtsDrHitDirID1(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID1 = bdat.getMember("HitDirID1");
}

void initArtsDrHitDirID2(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID2 = bdat.getMember("HitDirID2");
}

void initArtsDrHitDirID3(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID3 = bdat.getMember("HitDirID3");
}

void initArtsDrHitDirID4(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID4 = bdat.getMember("HitDirID4");
}

void initArtsDrHitDirID5(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID5 = bdat.getMember("HitDirID5");
}

void initArtsDrHitDirID6(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID6 = bdat.getMember("HitDirID6");
}

void initArtsDrHitDirID7(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID7 = bdat.getMember("HitDirID7");
}

void initArtsDrHitDirID8(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID8 = bdat.getMember("HitDirID8");
}

void initArtsDrHitDirID9(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID9 = bdat.getMember("HitDirID9");
}

void initArtsDrHitDirID10(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID10 = bdat.getMember("HitDirID10");
}

void initArtsDrHitDirID11(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID11 = bdat.getMember("HitDirID11");
}

void initArtsDrHitDirID12(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID12 = bdat.getMember("HitDirID12");
}

void initArtsDrHitDirID13(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID13 = bdat.getMember("HitDirID13");
}

void initArtsDrHitDirID14(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID14 = bdat.getMember("HitDirID14");
}

void initArtsDrHitDirID15(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID15 = bdat.getMember("HitDirID15");
}

void initArtsDrHitDirID16(const CBdatWrapper& bdat) {
    s_memberArtsDrHitDirID16 = bdat.getMember("HitDirID16");
}

void initArtsDrDmgRt1(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt1 = bdat.getMember("DmgRt1");
}

void initArtsDrDmgRt2(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt2 = bdat.getMember("DmgRt2");
}

void initArtsDrDmgRt3(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt3 = bdat.getMember("DmgRt3");
}

void initArtsDrDmgRt4(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt4 = bdat.getMember("DmgRt4");
}

void initArtsDrDmgRt5(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt5 = bdat.getMember("DmgRt5");
}

void initArtsDrDmgRt6(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt6 = bdat.getMember("DmgRt6");
}

void initArtsDrDmgRt7(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt7 = bdat.getMember("DmgRt7");
}

void initArtsDrDmgRt8(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt8 = bdat.getMember("DmgRt8");
}

void initArtsDrDmgRt9(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt9 = bdat.getMember("DmgRt9");
}

void initArtsDrDmgRt10(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt10 = bdat.getMember("DmgRt10");
}

void initArtsDrDmgRt11(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt11 = bdat.getMember("DmgRt11");
}

void initArtsDrDmgRt12(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt12 = bdat.getMember("DmgRt12");
}

void initArtsDrDmgRt13(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt13 = bdat.getMember("DmgRt13");
}

void initArtsDrDmgRt14(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt14 = bdat.getMember("DmgRt14");
}

void initArtsDrDmgRt15(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt15 = bdat.getMember("DmgRt15");
}

void initArtsDrDmgRt16(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgRt16 = bdat.getMember("DmgRt16");
}

void initArtsDrReAct1(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct1 = bdat.getMember("ReAct1");
}

void initArtsDrReAct2(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct2 = bdat.getMember("ReAct2");
}

void initArtsDrReAct3(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct3 = bdat.getMember("ReAct3");
}

void initArtsDrReAct4(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct4 = bdat.getMember("ReAct4");
}

void initArtsDrReAct5(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct5 = bdat.getMember("ReAct5");
}

void initArtsDrReAct6(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct6 = bdat.getMember("ReAct6");
}

void initArtsDrReAct7(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct7 = bdat.getMember("ReAct7");
}

void initArtsDrReAct8(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct8 = bdat.getMember("ReAct8");
}

void initArtsDrReAct9(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct9 = bdat.getMember("ReAct9");
}

void initArtsDrReAct10(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct10 = bdat.getMember("ReAct10");
}

void initArtsDrReAct11(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct11 = bdat.getMember("ReAct11");
}

void initArtsDrReAct12(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct12 = bdat.getMember("ReAct12");
}

void initArtsDrReAct13(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct13 = bdat.getMember("ReAct13");
}

void initArtsDrReAct14(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct14 = bdat.getMember("ReAct14");
}

void initArtsDrReAct15(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct15 = bdat.getMember("ReAct15");
}

void initArtsDrReAct16(const CBdatWrapper& bdat) {
    s_memberArtsDrReAct16 = bdat.getMember("ReAct16");
}

void initArtsDrMoveCancelFrm(const CBdatWrapper& bdat) {
    s_memberArtsDrMoveCancelFrm = bdat.getMember("MoveCancelFrm");
}

void initArtsDrDmgMgn1(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgMgn1 = bdat.getMember("DmgMgn1");
}

unsigned int getArtsDrDmgMgn1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrDmgMgn1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrDmgMgn1, id, 2);
    }
    return 0;
}

void initArtsDrDmgMgn2(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgMgn2 = bdat.getMember("DmgMgn2");
}

unsigned int getArtsDrDmgMgn2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrDmgMgn2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrDmgMgn2, id, 2);
    }
    return 0;
}

void initArtsDrDmgMgn3(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgMgn3 = bdat.getMember("DmgMgn3");
}

unsigned int getArtsDrDmgMgn3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrDmgMgn3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrDmgMgn3, id, 2);
    }
    return 0;
}

void initArtsDrDmgMgn4(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgMgn4 = bdat.getMember("DmgMgn4");
}

unsigned int getArtsDrDmgMgn4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrDmgMgn4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrDmgMgn4, id, 2);
    }
    return 0;
}

void initArtsDrDmgMgn5(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgMgn5 = bdat.getMember("DmgMgn5");
}

unsigned int getArtsDrDmgMgn5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrDmgMgn5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrDmgMgn5, id, 2);
    }
    return 0;
}

void initArtsDrDmgMgn6(const CBdatWrapper& bdat) {
    s_memberArtsDrDmgMgn6 = bdat.getMember("DmgMgn6");
}

unsigned int getArtsDrDmgMgn6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrDmgMgn6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrDmgMgn6, id, 2);
    }
    return 0;
}

void initArtsDrRecast1(const CBdatWrapper& bdat) {
    s_memberArtsDrRecast1 = bdat.getMember("Recast1");
}

unsigned int getArtsDrRecast1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrRecast1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrRecast1, id, 2);
    }
    return 0;
}

void initArtsDrRecast2(const CBdatWrapper& bdat) {
    s_memberArtsDrRecast2 = bdat.getMember("Recast2");
}

unsigned int getArtsDrRecast2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrRecast2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrRecast2, id, 2);
    }
    return 0;
}

void initArtsDrRecast3(const CBdatWrapper& bdat) {
    s_memberArtsDrRecast3 = bdat.getMember("Recast3");
}

unsigned int getArtsDrRecast3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrRecast3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrRecast3, id, 2);
    }
    return 0;
}

void initArtsDrRecast4(const CBdatWrapper& bdat) {
    s_memberArtsDrRecast4 = bdat.getMember("Recast4");
}

unsigned int getArtsDrRecast4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrRecast4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrRecast4, id, 2);
    }
    return 0;
}

void initArtsDrRecast5(const CBdatWrapper& bdat) {
    s_memberArtsDrRecast5 = bdat.getMember("Recast5");
}

unsigned int getArtsDrRecast5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrRecast5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrRecast5, id, 2);
    }
    return 0;
}

void initArtsDrRecast6(const CBdatWrapper& bdat) {
    s_memberArtsDrRecast6 = bdat.getMember("Recast6");
}

unsigned int getArtsDrRecast6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrRecast6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrRecast6, id, 2);
    }
    return 0;
}

void initArtsDrAtrNum(const CBdatWrapper& bdat) {
    s_memberArtsDrAtrNum = bdat.getMember("AtrNum");
}

void initArtsDrEnhance1(const CBdatWrapper& bdat) {
    s_memberArtsDrEnhance1 = bdat.getMember("Enhance1");
}

unsigned int getArtsDrEnhance1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrEnhance1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrEnhance1, id, 2);
    }
    return 0;
}

void initArtsDrEnhance2(const CBdatWrapper& bdat) {
    s_memberArtsDrEnhance2 = bdat.getMember("Enhance2");
}

unsigned int getArtsDrEnhance2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrEnhance2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrEnhance2, id, 2);
    }
    return 0;
}

void initArtsDrEnhance3(const CBdatWrapper& bdat) {
    s_memberArtsDrEnhance3 = bdat.getMember("Enhance3");
}

unsigned int getArtsDrEnhance3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrEnhance3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrEnhance3, id, 2);
    }
    return 0;
}

void initArtsDrEnhance4(const CBdatWrapper& bdat) {
    s_memberArtsDrEnhance4 = bdat.getMember("Enhance4");
}

unsigned int getArtsDrEnhance4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrEnhance4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrEnhance4, id, 2);
    }
    return 0;
}

void initArtsDrEnhance5(const CBdatWrapper& bdat) {
    s_memberArtsDrEnhance5 = bdat.getMember("Enhance5");
}

unsigned int getArtsDrEnhance5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrEnhance5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrEnhance5, id, 2);
    }
    return 0;
}

void initArtsDrEnhance6(const CBdatWrapper& bdat) {
    s_memberArtsDrEnhance6 = bdat.getMember("Enhance6");
}

unsigned int getArtsDrEnhance6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrEnhance6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrEnhance6, id, 2);
    }
    return 0;
}

void initArtsDrReleaseLv1(const CBdatWrapper& bdat) {
    s_memberArtsDrReleaseLv1 = bdat.getMember("ReleaseLv1");
}

unsigned int getArtsDrReleaseLv1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrReleaseLv1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrReleaseLv1, id, 1);
    }
    return 0;
}

void initArtsDrReleaseLv2(const CBdatWrapper& bdat) {
    s_memberArtsDrReleaseLv2 = bdat.getMember("ReleaseLv2");
}

unsigned int getArtsDrReleaseLv2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrReleaseLv2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrReleaseLv2, id, 1);
    }
    return 0;
}

void initArtsDrReleaseLv3(const CBdatWrapper& bdat) {
    s_memberArtsDrReleaseLv3 = bdat.getMember("ReleaseLv3");
}

unsigned int getArtsDrReleaseLv3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrReleaseLv3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrReleaseLv3, id, 1);
    }
    return 0;
}

void initArtsDrReleaseLv4(const CBdatWrapper& bdat) {
    s_memberArtsDrReleaseLv4 = bdat.getMember("ReleaseLv4");
}

unsigned int getArtsDrReleaseLv4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrReleaseLv4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrReleaseLv4, id, 1);
    }
    return 0;
}

void initArtsDrReleaseLv5(const CBdatWrapper& bdat) {
    s_memberArtsDrReleaseLv5 = bdat.getMember("ReleaseLv5");
}

unsigned int getArtsDrReleaseLv5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrReleaseLv5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrReleaseLv5, id, 1);
    }
    return 0;
}

void initArtsDrNeedWP2(const CBdatWrapper& bdat) {
    s_memberArtsDrNeedWP2 = bdat.getMember("NeedWP2");
}

unsigned int getArtsDrNeedWP2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrNeedWP2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrNeedWP2, id, 2);
    }
    return 0;
}

void initArtsDrNeedWP3(const CBdatWrapper& bdat) {
    s_memberArtsDrNeedWP3 = bdat.getMember("NeedWP3");
}

unsigned int getArtsDrNeedWP3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrNeedWP3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrNeedWP3, id, 2);
    }
    return 0;
}

void initArtsDrNeedWP4(const CBdatWrapper& bdat) {
    s_memberArtsDrNeedWP4 = bdat.getMember("NeedWP4");
}

unsigned int getArtsDrNeedWP4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrNeedWP4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrNeedWP4, id, 2);
    }
    return 0;
}

void initArtsDrNeedWP5(const CBdatWrapper& bdat) {
    s_memberArtsDrNeedWP5 = bdat.getMember("NeedWP5");
}

unsigned int getArtsDrNeedWP5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrNeedWP5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsDrNeedWP5, id, 2);
    }
    return 0;
}

void initArtsDrUI(const CBdatWrapper& bdat) {
    s_memberArtsDrUI = bdat.getMember("UI");
}

void initArtsDrPriority(const CBdatWrapper& bdat) {
    s_memberArtsDrPriority = bdat.getMember("Priority");
}

unsigned int getArtsDrPriority(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsDrPriority != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsDrPriority, id, 1);
    }
    return 0;
}

void initArtsBlName(const CBdatWrapper& bdat) {
    s_memberArtsBlName = bdat.getMember("Name");
}

unsigned int getArtsBlName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlName, id, 2);
    }
    return 0;
}

void initArtsBlDebugName(const CBdatWrapper& bdat) {
    s_memberArtsBlDebugName = bdat.getMember("DebugName");
}

const char* getArtsBlDebugName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlDebugName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberArtsBlDebugName, id, 7);
    }
    return nullptr;
}

void initArtsBlCaption(const CBdatWrapper& bdat) {
    s_memberArtsBlCaption = bdat.getMember("Caption");
}

unsigned int getArtsBlCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlCaption, id, 2);
    }
    return 0;
}

void initArtsBlWpnType(const CBdatWrapper& bdat) {
    s_memberArtsBlWpnType = bdat.getMember("WpnType");
}

unsigned int getArtsBlWpnType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsBlWpnType, id, 1);
    }
    return 0;
}

void initArtsBlCmnBlType(const CBdatWrapper& bdat) {
    s_memberArtsBlCmnBlType = bdat.getMember("CmnBlType");
}

unsigned int getArtsBlCmnBlType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlCmnBlType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsBlCmnBlType, id, 1);
    }
    return 0;
}

void initArtsBlSpLv(const CBdatWrapper& bdat) {
    s_memberArtsBlSpLv = bdat.getMember("SpLv");
}

unsigned int getArtsBlSpLv(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlSpLv != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsBlSpLv, id, 1);
    }
    return 0;
}

void initArtsBlActNo(const CBdatWrapper& bdat) {
    s_memberArtsBlActNo = bdat.getMember("ActNo");
}

void initArtsBlArtsType(const CBdatWrapper& bdat) {
    s_memberArtsBlArtsType = bdat.getMember("ArtsType");
}

void initArtsBlArtsBuff(const CBdatWrapper& bdat) {
    s_memberArtsBlArtsBuff = bdat.getMember("ArtsBuff");
}

void initArtsBlFlagcommon(const CBdatWrapper& bdat) {
    s_memberArtsBlFlagcommonFlag = bdat.getMember("Flag");
    s_memberArtsBlFlagcommon = bdat.getMember("common");
}
bool isArtsBlFlagcommon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlFlagcommonFlag != nullptr && s_memberArtsBlFlagcommon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberArtsBlFlagcommonFlag, id, s_memberArtsBlFlagcommon) != 0;
    }
    return false;
}


void initArtsBlFlagPierce(const CBdatWrapper& bdat) {
    s_memberArtsBlFlagPierceFlag = bdat.getMember("Flag");
    s_memberArtsBlFlagPierce = bdat.getMember("Pierce");
}
bool isArtsBlFlagPierce(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlFlagPierceFlag != nullptr && s_memberArtsBlFlagPierce != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberArtsBlFlagPierceFlag, id, s_memberArtsBlFlagPierce) != 0;
    }
    return false;
}


void initArtsBlTarget(const CBdatWrapper& bdat) {
    s_memberArtsBlTarget = bdat.getMember("Target");
}

void initArtsBlDistance(const CBdatWrapper& bdat) {
    s_memberArtsBlDistance = bdat.getMember("Distance");
}

void initArtsBlRangeType(const CBdatWrapper& bdat) {
    s_memberArtsBlRangeType = bdat.getMember("RangeType");
}

void initArtsBlRadius(const CBdatWrapper& bdat) {
    s_memberArtsBlRadius = bdat.getMember("Radius");
}

void initArtsBlLength(const CBdatWrapper& bdat) {
    s_memberArtsBlLength = bdat.getMember("Length");
}

void initArtsBlAtr(const CBdatWrapper& bdat) {
    s_memberArtsBlAtr = bdat.getMember("Atr");
}

void initArtsBlHate(const CBdatWrapper& bdat) {
    s_memberArtsBlHate = bdat.getMember("Hate");
}

void initArtsBlHitRevise(const CBdatWrapper& bdat) {
    s_memberArtsBlHitRevise = bdat.getMember("HitRevise");
}

void initArtsBlCriRevise(const CBdatWrapper& bdat) {
    s_memberArtsBlCriRevise = bdat.getMember("CriRevise");
}

void initArtsBlBulletID(const CBdatWrapper& bdat) {
    s_memberArtsBlBulletID = bdat.getMember("BulletID");
}

void initArtsBlBulletNum(const CBdatWrapper& bdat) {
    s_memberArtsBlBulletNum = bdat.getMember("BulletNum");
}

void initArtsBlHitFrm1(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm1 = bdat.getMember("HitFrm1");
}

void initArtsBlHitFrm2(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm2 = bdat.getMember("HitFrm2");
}

void initArtsBlHitFrm3(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm3 = bdat.getMember("HitFrm3");
}

void initArtsBlHitFrm4(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm4 = bdat.getMember("HitFrm4");
}

void initArtsBlHitFrm5(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm5 = bdat.getMember("HitFrm5");
}

void initArtsBlHitFrm6(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm6 = bdat.getMember("HitFrm6");
}

void initArtsBlHitFrm7(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm7 = bdat.getMember("HitFrm7");
}

void initArtsBlHitFrm8(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm8 = bdat.getMember("HitFrm8");
}

void initArtsBlHitFrm9(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm9 = bdat.getMember("HitFrm9");
}

void initArtsBlHitFrm10(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm10 = bdat.getMember("HitFrm10");
}

void initArtsBlHitFrm11(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm11 = bdat.getMember("HitFrm11");
}

void initArtsBlHitFrm12(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm12 = bdat.getMember("HitFrm12");
}

void initArtsBlHitFrm13(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm13 = bdat.getMember("HitFrm13");
}

void initArtsBlHitFrm14(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm14 = bdat.getMember("HitFrm14");
}

void initArtsBlHitFrm15(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm15 = bdat.getMember("HitFrm15");
}

void initArtsBlHitFrm16(const CBdatWrapper& bdat) {
    s_memberArtsBlHitFrm16 = bdat.getMember("HitFrm16");
}

void initArtsBlEfp1(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp1 = bdat.getMember("Efp1");
}

void initArtsBlEfp2(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp2 = bdat.getMember("Efp2");
}

void initArtsBlEfp3(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp3 = bdat.getMember("Efp3");
}

void initArtsBlEfp4(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp4 = bdat.getMember("Efp4");
}

void initArtsBlEfp5(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp5 = bdat.getMember("Efp5");
}

void initArtsBlEfp6(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp6 = bdat.getMember("Efp6");
}

void initArtsBlEfp7(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp7 = bdat.getMember("Efp7");
}

void initArtsBlEfp8(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp8 = bdat.getMember("Efp8");
}

void initArtsBlEfp9(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp9 = bdat.getMember("Efp9");
}

void initArtsBlEfp10(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp10 = bdat.getMember("Efp10");
}

void initArtsBlEfp11(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp11 = bdat.getMember("Efp11");
}

void initArtsBlEfp12(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp12 = bdat.getMember("Efp12");
}

void initArtsBlEfp13(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp13 = bdat.getMember("Efp13");
}

void initArtsBlEfp14(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp14 = bdat.getMember("Efp14");
}

void initArtsBlEfp15(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp15 = bdat.getMember("Efp15");
}

void initArtsBlEfp16(const CBdatWrapper& bdat) {
    s_memberArtsBlEfp16 = bdat.getMember("Efp16");
}

void initArtsBlHitDirID1(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID1 = bdat.getMember("HitDirID1");
}

void initArtsBlHitDirID2(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID2 = bdat.getMember("HitDirID2");
}

void initArtsBlHitDirID3(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID3 = bdat.getMember("HitDirID3");
}

void initArtsBlHitDirID4(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID4 = bdat.getMember("HitDirID4");
}

void initArtsBlHitDirID5(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID5 = bdat.getMember("HitDirID5");
}

void initArtsBlHitDirID6(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID6 = bdat.getMember("HitDirID6");
}

void initArtsBlHitDirID7(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID7 = bdat.getMember("HitDirID7");
}

void initArtsBlHitDirID8(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID8 = bdat.getMember("HitDirID8");
}

void initArtsBlHitDirID9(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID9 = bdat.getMember("HitDirID9");
}

void initArtsBlHitDirID10(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID10 = bdat.getMember("HitDirID10");
}

void initArtsBlHitDirID11(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID11 = bdat.getMember("HitDirID11");
}

void initArtsBlHitDirID12(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID12 = bdat.getMember("HitDirID12");
}

void initArtsBlHitDirID13(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID13 = bdat.getMember("HitDirID13");
}

void initArtsBlHitDirID14(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID14 = bdat.getMember("HitDirID14");
}

void initArtsBlHitDirID15(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID15 = bdat.getMember("HitDirID15");
}

void initArtsBlHitDirID16(const CBdatWrapper& bdat) {
    s_memberArtsBlHitDirID16 = bdat.getMember("HitDirID16");
}

void initArtsBlDmgRt1(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt1 = bdat.getMember("DmgRt1");
}

void initArtsBlDmgRt2(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt2 = bdat.getMember("DmgRt2");
}

void initArtsBlDmgRt3(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt3 = bdat.getMember("DmgRt3");
}

void initArtsBlDmgRt4(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt4 = bdat.getMember("DmgRt4");
}

void initArtsBlDmgRt5(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt5 = bdat.getMember("DmgRt5");
}

void initArtsBlDmgRt6(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt6 = bdat.getMember("DmgRt6");
}

void initArtsBlDmgRt7(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt7 = bdat.getMember("DmgRt7");
}

void initArtsBlDmgRt8(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt8 = bdat.getMember("DmgRt8");
}

void initArtsBlDmgRt9(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt9 = bdat.getMember("DmgRt9");
}

void initArtsBlDmgRt10(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt10 = bdat.getMember("DmgRt10");
}

void initArtsBlDmgRt11(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt11 = bdat.getMember("DmgRt11");
}

void initArtsBlDmgRt12(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt12 = bdat.getMember("DmgRt12");
}

void initArtsBlDmgRt13(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt13 = bdat.getMember("DmgRt13");
}

void initArtsBlDmgRt14(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt14 = bdat.getMember("DmgRt14");
}

void initArtsBlDmgRt15(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt15 = bdat.getMember("DmgRt15");
}

void initArtsBlDmgRt16(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgRt16 = bdat.getMember("DmgRt16");
}

void initArtsBlReAct1(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct1 = bdat.getMember("ReAct1");
}

void initArtsBlReAct2(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct2 = bdat.getMember("ReAct2");
}

void initArtsBlReAct3(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct3 = bdat.getMember("ReAct3");
}

void initArtsBlReAct4(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct4 = bdat.getMember("ReAct4");
}

void initArtsBlReAct5(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct5 = bdat.getMember("ReAct5");
}

void initArtsBlReAct6(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct6 = bdat.getMember("ReAct6");
}

void initArtsBlReAct7(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct7 = bdat.getMember("ReAct7");
}

void initArtsBlReAct8(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct8 = bdat.getMember("ReAct8");
}

void initArtsBlReAct9(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct9 = bdat.getMember("ReAct9");
}

void initArtsBlReAct10(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct10 = bdat.getMember("ReAct10");
}

void initArtsBlReAct11(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct11 = bdat.getMember("ReAct11");
}

void initArtsBlReAct12(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct12 = bdat.getMember("ReAct12");
}

void initArtsBlReAct13(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct13 = bdat.getMember("ReAct13");
}

void initArtsBlReAct14(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct14 = bdat.getMember("ReAct14");
}

void initArtsBlReAct15(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct15 = bdat.getMember("ReAct15");
}

void initArtsBlReAct16(const CBdatWrapper& bdat) {
    s_memberArtsBlReAct16 = bdat.getMember("ReAct16");
}

void initArtsBlDmgMgn1(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgMgn1 = bdat.getMember("DmgMgn1");
}

void initArtsBlDmgMgn2(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgMgn2 = bdat.getMember("DmgMgn2");
}

void initArtsBlDmgMgn3(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgMgn3 = bdat.getMember("DmgMgn3");
}

void initArtsBlDmgMgn4(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgMgn4 = bdat.getMember("DmgMgn4");
}

void initArtsBlDmgMgn5(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgMgn5 = bdat.getMember("DmgMgn5");
}

void initArtsBlDmgMgn6(const CBdatWrapper& bdat) {
    s_memberArtsBlDmgMgn6 = bdat.getMember("DmgMgn6");
}

void initArtsBlAtrNum(const CBdatWrapper& bdat) {
    s_memberArtsBlAtrNum = bdat.getMember("AtrNum");
}

void initArtsBlEnhance1(const CBdatWrapper& bdat) {
    s_memberArtsBlEnhance1 = bdat.getMember("Enhance1");
}

unsigned int getArtsBlEnhance1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlEnhance1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlEnhance1, id, 2);
    }
    return 0;
}

void initArtsBlEnhance2(const CBdatWrapper& bdat) {
    s_memberArtsBlEnhance2 = bdat.getMember("Enhance2");
}

unsigned int getArtsBlEnhance2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlEnhance2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlEnhance2, id, 2);
    }
    return 0;
}

void initArtsBlEnhance3(const CBdatWrapper& bdat) {
    s_memberArtsBlEnhance3 = bdat.getMember("Enhance3");
}

unsigned int getArtsBlEnhance3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlEnhance3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlEnhance3, id, 2);
    }
    return 0;
}

void initArtsBlEnhance4(const CBdatWrapper& bdat) {
    s_memberArtsBlEnhance4 = bdat.getMember("Enhance4");
}

unsigned int getArtsBlEnhance4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlEnhance4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlEnhance4, id, 2);
    }
    return 0;
}

void initArtsBlEnhance5(const CBdatWrapper& bdat) {
    s_memberArtsBlEnhance5 = bdat.getMember("Enhance5");
}

unsigned int getArtsBlEnhance5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlEnhance5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlEnhance5, id, 2);
    }
    return 0;
}

void initArtsBlEnhance6(const CBdatWrapper& bdat) {
    s_memberArtsBlEnhance6 = bdat.getMember("Enhance6");
}

unsigned int getArtsBlEnhance6(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlEnhance6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlEnhance6, id, 2);
    }
    return 0;
}

void initArtsBlBtnType(const CBdatWrapper& bdat) {
    s_memberArtsBlBtnType = bdat.getMember("BtnType");
}

void initArtsBlBtnChal1(const CBdatWrapper& bdat) {
    s_memberArtsBlBtnChal1 = bdat.getMember("BtnChal1");
}

void initArtsBlUI(const CBdatWrapper& bdat) {
    s_memberArtsBlUI = bdat.getMember("UI");
}

void initArtsBlSpName(const CBdatWrapper& bdat) {
    s_memberArtsBlSpName = bdat.getMember("Name");
}

unsigned int getArtsBlSpName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlSpName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlSpName, id, 2);
    }
    return 0;
}

void initArtsBlSpDebugName(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDebugName = bdat.getMember("DebugName");
}

void initArtsBlSpCaption(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCaption = bdat.getMember("Caption");
}

unsigned int getArtsBlSpCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlSpCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberArtsBlSpCaption, id, 2);
    }
    return 0;
}

void initArtsBlSpWpnType(const CBdatWrapper& bdat) {
    s_memberArtsBlSpWpnType = bdat.getMember("WpnType");
}

unsigned int getArtsBlSpWpnType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlSpWpnType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsBlSpWpnType, id, 1);
    }
    return 0;
}

void initArtsBlSpCondition(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCondition = bdat.getMember("Condition");
}

void initArtsBlSpCmnBlType(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCmnBlType = bdat.getMember("CmnBlType");
}

unsigned int getArtsBlSpCmnBlType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlSpCmnBlType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberArtsBlSpCmnBlType, id, 1);
    }
    return 0;
}

void initArtsBlSpActNoDr(const CBdatWrapper& bdat) {
    s_memberArtsBlSpActNoDr = bdat.getMember("ActNoDr");
}

void initArtsBlSpActNoBl(const CBdatWrapper& bdat) {
    s_memberArtsBlSpActNoBl = bdat.getMember("ActNoBl");
}

void initArtsBlSpActNoBl2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpActNoBl2 = bdat.getMember("ActNoBl2");
}

void initArtsBlSpBuddyDr(const CBdatWrapper& bdat) {
    s_memberArtsBlSpBuddyDr = bdat.getMember("BuddyDr");
}

void initArtsBlSpAddBl(const CBdatWrapper& bdat) {
    s_memberArtsBlSpAddBl = bdat.getMember("AddBl");
}

void initArtsBlSpActType(const CBdatWrapper& bdat) {
    s_memberArtsBlSpActType = bdat.getMember("ActType");
}

void initArtsBlSpPC01(const CBdatWrapper& bdat) {
    s_memberArtsBlSpPC01 = bdat.getMember("PC01");
}

void initArtsBlSpPC02(const CBdatWrapper& bdat) {
    s_memberArtsBlSpPC02 = bdat.getMember("PC02");
}

void initArtsBlSpPC03(const CBdatWrapper& bdat) {
    s_memberArtsBlSpPC03 = bdat.getMember("PC03");
}

void initArtsBlSpPC06(const CBdatWrapper& bdat) {
    s_memberArtsBlSpPC06 = bdat.getMember("PC06");
}

void initArtsBlSpArtsType(const CBdatWrapper& bdat) {
    s_memberArtsBlSpArtsType = bdat.getMember("ArtsType");
}

void initArtsBlSpArtsBuff(const CBdatWrapper& bdat) {
    s_memberArtsBlSpArtsBuff = bdat.getMember("ArtsBuff");
}

void initArtsBlSpFlagPierce(const CBdatWrapper& bdat) {
    s_memberArtsBlSpFlagPierceFlag = bdat.getMember("Flag");
    s_memberArtsBlSpFlagPierce = bdat.getMember("Pierce");
}
bool isArtsBlSpFlagPierce(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlSpFlagPierceFlag != nullptr && s_memberArtsBlSpFlagPierce != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberArtsBlSpFlagPierceFlag, id, s_memberArtsBlSpFlagPierce) != 0;
    }
    return false;
}


void initArtsBlSpFlagNoMove(const CBdatWrapper& bdat) {
    s_memberArtsBlSpFlagNoMoveFlag = bdat.getMember("Flag");
    s_memberArtsBlSpFlagNoMove = bdat.getMember("NoMove");
}
bool isArtsBlSpFlagNoMove(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberArtsBlSpFlagNoMoveFlag != nullptr && s_memberArtsBlSpFlagNoMove != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberArtsBlSpFlagNoMoveFlag, id, s_memberArtsBlSpFlagNoMove) != 0;
    }
    return false;
}


void initArtsBlSpTarget(const CBdatWrapper& bdat) {
    s_memberArtsBlSpTarget = bdat.getMember("Target");
}

void initArtsBlSpDistance(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDistance = bdat.getMember("Distance");
}

void initArtsBlSpRangeType(const CBdatWrapper& bdat) {
    s_memberArtsBlSpRangeType = bdat.getMember("RangeType");
}

void initArtsBlSpRadius(const CBdatWrapper& bdat) {
    s_memberArtsBlSpRadius = bdat.getMember("Radius");
}

void initArtsBlSpLength(const CBdatWrapper& bdat) {
    s_memberArtsBlSpLength = bdat.getMember("Length");
}

void initArtsBlSpAtr(const CBdatWrapper& bdat) {
    s_memberArtsBlSpAtr = bdat.getMember("Atr");
}

void initArtsBlSpHate(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHate = bdat.getMember("Hate");
}

void initArtsBlSpHitRevise(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitRevise = bdat.getMember("HitRevise");
}

void initArtsBlSpCriRevise(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCriRevise = bdat.getMember("CriRevise");
}

void initArtsBlSpBulletID(const CBdatWrapper& bdat) {
    s_memberArtsBlSpBulletID = bdat.getMember("BulletID");
}

void initArtsBlSpBulletEffID(const CBdatWrapper& bdat) {
    s_memberArtsBlSpBulletEffID = bdat.getMember("BulletEffID");
}

void initArtsBlSpBulletNum(const CBdatWrapper& bdat) {
    s_memberArtsBlSpBulletNum = bdat.getMember("BulletNum");
}

void initArtsBlSpHitFrm1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm1 = bdat.getMember("HitFrm1");
}

void initArtsBlSpHitFrm2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm2 = bdat.getMember("HitFrm2");
}

void initArtsBlSpHitFrm3(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm3 = bdat.getMember("HitFrm3");
}

void initArtsBlSpHitFrm4(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm4 = bdat.getMember("HitFrm4");
}

void initArtsBlSpHitFrm5(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm5 = bdat.getMember("HitFrm5");
}

void initArtsBlSpHitFrm6(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm6 = bdat.getMember("HitFrm6");
}

void initArtsBlSpHitFrm7(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm7 = bdat.getMember("HitFrm7");
}

void initArtsBlSpHitFrm8(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm8 = bdat.getMember("HitFrm8");
}

void initArtsBlSpHitFrm9(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm9 = bdat.getMember("HitFrm9");
}

void initArtsBlSpHitFrm10(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm10 = bdat.getMember("HitFrm10");
}

void initArtsBlSpHitFrm11(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm11 = bdat.getMember("HitFrm11");
}

void initArtsBlSpHitFrm12(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm12 = bdat.getMember("HitFrm12");
}

void initArtsBlSpHitFrm13(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm13 = bdat.getMember("HitFrm13");
}

void initArtsBlSpHitFrm14(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm14 = bdat.getMember("HitFrm14");
}

void initArtsBlSpHitFrm15(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm15 = bdat.getMember("HitFrm15");
}

void initArtsBlSpHitFrm16(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitFrm16 = bdat.getMember("HitFrm16");
}

void initArtsBlSpEfp1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp1 = bdat.getMember("Efp1");
}

void initArtsBlSpEfp2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp2 = bdat.getMember("Efp2");
}

void initArtsBlSpEfp3(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp3 = bdat.getMember("Efp3");
}

void initArtsBlSpEfp4(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp4 = bdat.getMember("Efp4");
}

void initArtsBlSpEfp5(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp5 = bdat.getMember("Efp5");
}

void initArtsBlSpEfp6(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp6 = bdat.getMember("Efp6");
}

void initArtsBlSpEfp7(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp7 = bdat.getMember("Efp7");
}

void initArtsBlSpEfp8(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp8 = bdat.getMember("Efp8");
}

void initArtsBlSpEfp9(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp9 = bdat.getMember("Efp9");
}

void initArtsBlSpEfp10(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp10 = bdat.getMember("Efp10");
}

void initArtsBlSpEfp11(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp11 = bdat.getMember("Efp11");
}

void initArtsBlSpEfp12(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp12 = bdat.getMember("Efp12");
}

void initArtsBlSpEfp13(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp13 = bdat.getMember("Efp13");
}

void initArtsBlSpEfp14(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp14 = bdat.getMember("Efp14");
}

void initArtsBlSpEfp15(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp15 = bdat.getMember("Efp15");
}

void initArtsBlSpEfp16(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEfp16 = bdat.getMember("Efp16");
}

void initArtsBlSpHitDirID1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID1 = bdat.getMember("HitDirID1");
}

void initArtsBlSpHitDirID2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID2 = bdat.getMember("HitDirID2");
}

void initArtsBlSpHitDirID3(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID3 = bdat.getMember("HitDirID3");
}

void initArtsBlSpHitDirID4(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID4 = bdat.getMember("HitDirID4");
}

void initArtsBlSpHitDirID5(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID5 = bdat.getMember("HitDirID5");
}

void initArtsBlSpHitDirID6(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID6 = bdat.getMember("HitDirID6");
}

void initArtsBlSpHitDirID7(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID7 = bdat.getMember("HitDirID7");
}

void initArtsBlSpHitDirID8(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID8 = bdat.getMember("HitDirID8");
}

void initArtsBlSpHitDirID9(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID9 = bdat.getMember("HitDirID9");
}

void initArtsBlSpHitDirID10(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID10 = bdat.getMember("HitDirID10");
}

void initArtsBlSpHitDirID11(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID11 = bdat.getMember("HitDirID11");
}

void initArtsBlSpHitDirID12(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID12 = bdat.getMember("HitDirID12");
}

void initArtsBlSpHitDirID13(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID13 = bdat.getMember("HitDirID13");
}

void initArtsBlSpHitDirID14(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID14 = bdat.getMember("HitDirID14");
}

void initArtsBlSpHitDirID15(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID15 = bdat.getMember("HitDirID15");
}

void initArtsBlSpHitDirID16(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitDirID16 = bdat.getMember("HitDirID16");
}

void initArtsBlSpDmgRt1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt1 = bdat.getMember("DmgRt1");
}

void initArtsBlSpDmgRt2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt2 = bdat.getMember("DmgRt2");
}

void initArtsBlSpDmgRt3(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt3 = bdat.getMember("DmgRt3");
}

void initArtsBlSpDmgRt4(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt4 = bdat.getMember("DmgRt4");
}

void initArtsBlSpDmgRt5(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt5 = bdat.getMember("DmgRt5");
}

void initArtsBlSpDmgRt6(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt6 = bdat.getMember("DmgRt6");
}

void initArtsBlSpDmgRt7(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt7 = bdat.getMember("DmgRt7");
}

void initArtsBlSpDmgRt8(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt8 = bdat.getMember("DmgRt8");
}

void initArtsBlSpDmgRt9(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt9 = bdat.getMember("DmgRt9");
}

void initArtsBlSpDmgRt10(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt10 = bdat.getMember("DmgRt10");
}

void initArtsBlSpDmgRt11(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt11 = bdat.getMember("DmgRt11");
}

void initArtsBlSpDmgRt12(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt12 = bdat.getMember("DmgRt12");
}

void initArtsBlSpDmgRt13(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt13 = bdat.getMember("DmgRt13");
}

void initArtsBlSpDmgRt14(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt14 = bdat.getMember("DmgRt14");
}

void initArtsBlSpDmgRt15(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt15 = bdat.getMember("DmgRt15");
}

void initArtsBlSpDmgRt16(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgRt16 = bdat.getMember("DmgRt16");
}

void initArtsBlSpReAct1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct1 = bdat.getMember("ReAct1");
}

void initArtsBlSpReAct2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct2 = bdat.getMember("ReAct2");
}

void initArtsBlSpReAct3(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct3 = bdat.getMember("ReAct3");
}

void initArtsBlSpReAct4(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct4 = bdat.getMember("ReAct4");
}

void initArtsBlSpReAct5(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct5 = bdat.getMember("ReAct5");
}

void initArtsBlSpReAct6(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct6 = bdat.getMember("ReAct6");
}

void initArtsBlSpReAct7(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct7 = bdat.getMember("ReAct7");
}

void initArtsBlSpReAct8(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct8 = bdat.getMember("ReAct8");
}

void initArtsBlSpReAct9(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct9 = bdat.getMember("ReAct9");
}

void initArtsBlSpReAct10(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct10 = bdat.getMember("ReAct10");
}

void initArtsBlSpReAct11(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct11 = bdat.getMember("ReAct11");
}

void initArtsBlSpReAct12(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct12 = bdat.getMember("ReAct12");
}

void initArtsBlSpReAct13(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct13 = bdat.getMember("ReAct13");
}

void initArtsBlSpReAct14(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct14 = bdat.getMember("ReAct14");
}

void initArtsBlSpReAct15(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct15 = bdat.getMember("ReAct15");
}

void initArtsBlSpReAct16(const CBdatWrapper& bdat) {
    s_memberArtsBlSpReAct16 = bdat.getMember("ReAct16");
}

void initArtsBlSpDmgMgn(const CBdatWrapper& bdat) {
    s_memberArtsBlSpDmgMgn = bdat.getMember("DmgMgn");
}

void initArtsBlSpRecast(const CBdatWrapper& bdat) {
    s_memberArtsBlSpRecast = bdat.getMember("Recast");
}

void initArtsBlSpAtrNum(const CBdatWrapper& bdat) {
    s_memberArtsBlSpAtrNum = bdat.getMember("AtrNum");
}

void initArtsBlSpEnhance(const CBdatWrapper& bdat) {
    s_memberArtsBlSpEnhance = bdat.getMember("Enhance");
}

void initArtsBlSpBtnType(const CBdatWrapper& bdat) {
    s_memberArtsBlSpBtnType = bdat.getMember("BtnType");
}

void initArtsBlSpBtnChal1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpBtnChal1 = bdat.getMember("BtnChal1");
}

void initArtsBlSpCamera1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCamera1 = bdat.getMember("Camera1");
}

void initArtsBlSpCamera2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCamera2 = bdat.getMember("Camera2");
}

void initArtsBlSpCamera3(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCamera3 = bdat.getMember("Camera3");
}

void initArtsBlSpCameraCT1(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCameraCT1 = bdat.getMember("CameraCT1");
}

void initArtsBlSpCameraCT2(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCameraCT2 = bdat.getMember("CameraCT2");
}

void initArtsBlSpCameraEndf(const CBdatWrapper& bdat) {
    s_memberArtsBlSpCameraEndf = bdat.getMember("CameraEndf");
}

void initArtsBlSpHitEff(const CBdatWrapper& bdat) {
    s_memberArtsBlSpHitEff = bdat.getMember("HitEff");
}

void initGrowLevelExp(const CBdatWrapper& bdat) {
    s_memberGrowLevelExp = bdat.getMember("LevelExp");
}

unsigned int getGrowLevelExp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGrowLevelExp != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberGrowLevelExp, id, 3);
    }
    return 0;
}

void initGrowLevelExp2(const CBdatWrapper& bdat) {
    s_memberGrowLevelExp2 = bdat.getMember("LevelExp2");
}

unsigned int getGrowLevelExp2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGrowLevelExp2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberGrowLevelExp2, id, 3);
    }
    return 0;
}

void initGrowEnemyExp(const CBdatWrapper& bdat) {
    s_memberGrowEnemyExp = bdat.getMember("EnemyExp");
}

unsigned int getGrowEnemyExp(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGrowEnemyExp != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberGrowEnemyExp, id, 2);
    }
    return 0;
}

void initGrowEnemyWP(const CBdatWrapper& bdat) {
    s_memberGrowEnemyWP = bdat.getMember("EnemyWP");
}

unsigned int getGrowEnemyWP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGrowEnemyWP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberGrowEnemyWP, id, 2);
    }
    return 0;
}

void initGrowEnemySP(const CBdatWrapper& bdat) {
    s_memberGrowEnemySP = bdat.getMember("EnemySP");
}

unsigned int getGrowEnemySP(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGrowEnemySP != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberGrowEnemySP, id, 2);
    }
    return 0;
}

void initGrowEnemyGold(const CBdatWrapper& bdat) {
    s_memberGrowEnemyGold = bdat.getMember("EnemyGold");
}

unsigned int getGrowEnemyGold(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGrowEnemyGold != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberGrowEnemyGold, id, 3);
    }
    return 0;
}

void initGrowGoldDivide(const CBdatWrapper& bdat) {
    s_memberGrowGoldDivide = bdat.getMember("GoldDivide");
}

unsigned int getGrowGoldDivide(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberGrowGoldDivide != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberGrowGoldDivide, id, 1);
    }
    return 0;
}

void initLv_RevExpRevHigh(const CBdatWrapper& bdat) {
    s_memberLv_RevExpRevHigh = bdat.getMember("ExpRevHigh");
}

void initLv_RevExpRevLow(const CBdatWrapper& bdat) {
    s_memberLv_RevExpRevLow = bdat.getMember("ExpRevLow");
}

void initLv_RevDamageRevHigh(const CBdatWrapper& bdat) {
    s_memberLv_RevDamageRevHigh = bdat.getMember("DamageRevHigh");
}

void initLv_RevDamageRevLow(const CBdatWrapper& bdat) {
    s_memberLv_RevDamageRevLow = bdat.getMember("DamageRevLow");
}

void initWpn_EnRscR(const CBdatWrapper& bdat) {
    s_memberWpn_EnRscR = bdat.getMember("RscR");
}

unsigned int getWpn_EnRscR(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWpn_EnRscR != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberWpn_EnRscR, id, 2);
    }
    return 0;
}

void initWpn_EnRscL(const CBdatWrapper& bdat) {
    s_memberWpn_EnRscL = bdat.getMember("RscL");
}

unsigned int getWpn_EnRscL(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWpn_EnRscL != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberWpn_EnRscL, id, 2);
    }
    return 0;
}

void initWpn_EnTypeRange(const CBdatWrapper& bdat) {
    s_memberWpn_EnTypeRange = bdat.getMember("TypeRange");
}

void initWpn_EnDamage(const CBdatWrapper& bdat) {
    s_memberWpn_EnDamage = bdat.getMember("Damage");
}

void initWpn_EnStability(const CBdatWrapper& bdat) {
    s_memberWpn_EnStability = bdat.getMember("Stability");
}

void initBTL_ClassName(const CBdatWrapper& bdat) {
    s_memberBTL_ClassName = bdat.getMember("Name");
}

unsigned int getBTL_ClassName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ClassName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ClassName, id, 2);
    }
    return 0;
}

void initBTL_ClassRole1(const CBdatWrapper& bdat) {
    s_memberBTL_ClassRole1 = bdat.getMember("Role1");
}

unsigned int getBTL_ClassRole1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ClassRole1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ClassRole1, id, 1);
    }
    return 0;
}

void initBTL_ClassRole2(const CBdatWrapper& bdat) {
    s_memberBTL_ClassRole2 = bdat.getMember("Role2");
}

unsigned int getBTL_ClassRole2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ClassRole2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ClassRole2, id, 1);
    }
    return 0;
}

void initBTL_ClassRole3(const CBdatWrapper& bdat) {
    s_memberBTL_ClassRole3 = bdat.getMember("Role3");
}

unsigned int getBTL_ClassRole3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ClassRole3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ClassRole3, id, 1);
    }
    return 0;
}

void initBTL_ClassDamageDown(const CBdatWrapper& bdat) {
    s_memberBTL_ClassDamageDown = bdat.getMember("DamageDown");
}

void initBTL_ClassDamageUP(const CBdatWrapper& bdat) {
    s_memberBTL_ClassDamageUP = bdat.getMember("DamageUP");
}

void initBTL_ClassHealUP(const CBdatWrapper& bdat) {
    s_memberBTL_ClassHealUP = bdat.getMember("HealUP");
}

void initBTL_ClassAutoHate(const CBdatWrapper& bdat) {
    s_memberBTL_ClassAutoHate = bdat.getMember("AutoHate");
}

void initBTL_ClassArtsHate(const CBdatWrapper& bdat) {
    s_memberBTL_ClassArtsHate = bdat.getMember("ArtsHate");
}

void initBTL_EnhanceEnhanceEffect(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEnhanceEffect = bdat.getMember("EnhanceEffect");
}

unsigned int getBTL_EnhanceEnhanceEffect(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceEnhanceEffect != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_EnhanceEnhanceEffect, id, 2);
    }
    return 0;
}

void initBTL_EnhanceParam1(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceParam1 = bdat.getMember("Param1");
}

float getBTL_EnhanceParam1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceParam1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberBTL_EnhanceParam1, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initBTL_EnhanceParam2(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceParam2 = bdat.getMember("Param2");
}

float getBTL_EnhanceParam2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceParam2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        // a float column's value is its 32 bits
        union {
            unsigned int bits;
            float value;
        } val;
        val.bits = (unsigned int)bdat.getValCheck(s_memberBTL_EnhanceParam2, id, 8);
        return val.value;
    }
    return 0.0f;
}

void initBTL_EnhanceCaption(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceCaption = bdat.getMember("Caption");
}

unsigned int getBTL_EnhanceCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_EnhanceCaption, id, 2);
    }
    return 0;
}

void initBTL_EnhanceCaption2(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceCaption2 = bdat.getMember("Caption2");
}

unsigned int getBTL_EnhanceCaption2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceCaption2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_EnhanceCaption2, id, 2);
    }
    return 0;
}

void initBTL_EnhanceEffCategory(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffCategory = bdat.getMember("Category");
}

unsigned int getBTL_EnhanceEffCategory(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceEffCategory != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_EnhanceEffCategory, id, 1);
    }
    return 0;
}

void initBTL_EnhanceEffIcon(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffIcon = bdat.getMember("Icon");
}

void initBTL_EnhanceEffFlagCondition(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffFlagConditionFlag = bdat.getMember("Flag");
    s_memberBTL_EnhanceEffFlagCondition = bdat.getMember("Condition");
}
bool isBTL_EnhanceEffFlagCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceEffFlagConditionFlag != nullptr && s_memberBTL_EnhanceEffFlagCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberBTL_EnhanceEffFlagConditionFlag, id, s_memberBTL_EnhanceEffFlagCondition) != 0;
    }
    return false;
}


void initBTL_EnhanceEffFlagUI(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffFlagUIFlag = bdat.getMember("Flag");
    s_memberBTL_EnhanceEffFlagUI = bdat.getMember("UI");
}
bool isBTL_EnhanceEffFlagUI(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceEffFlagUIFlag != nullptr && s_memberBTL_EnhanceEffFlagUI != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberBTL_EnhanceEffFlagUIFlag, id, s_memberBTL_EnhanceEffFlagUI) != 0;
    }
    return false;
}


void initBTL_EnhanceEffParam(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffParam = bdat.getMember("Param");
}

void initBTL_EnhanceEffName(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffName = bdat.getMember("Name");
}

void initBTL_EnhanceEffDirect(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffDirect = bdat.getMember("Direct");
}

void initBTL_EnhanceEffSortCat(const CBdatWrapper& bdat) {
    s_memberBTL_EnhanceEffSortCat = bdat.getMember("SortCat");
}

unsigned int getBTL_EnhanceEffSortCat(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_EnhanceEffSortCat != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_EnhanceEffSortCat, id, 1);
    }
    return 0;
}

void initBTL_Skill_BlName(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlName = bdat.getMember("Name");
}

unsigned int getBTL_Skill_BlName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_BlName, id, 2);
    }
    return 0;
}

void initBTL_Skill_BlDebugName(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlDebugName = bdat.getMember("DebugName");
}

void initBTL_Skill_BlEnhance1(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlEnhance1 = bdat.getMember("Enhance1");
}

unsigned int getBTL_Skill_BlEnhance1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlEnhance1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_BlEnhance1, id, 2);
    }
    return 0;
}

void initBTL_Skill_BlEnhance2(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlEnhance2 = bdat.getMember("Enhance2");
}

unsigned int getBTL_Skill_BlEnhance2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlEnhance2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_BlEnhance2, id, 2);
    }
    return 0;
}

void initBTL_Skill_BlEnhance3(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlEnhance3 = bdat.getMember("Enhance3");
}

unsigned int getBTL_Skill_BlEnhance3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlEnhance3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_BlEnhance3, id, 2);
    }
    return 0;
}

void initBTL_Skill_BlEnhance4(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlEnhance4 = bdat.getMember("Enhance4");
}

unsigned int getBTL_Skill_BlEnhance4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlEnhance4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_BlEnhance4, id, 2);
    }
    return 0;
}

void initBTL_Skill_BlEnhance5(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlEnhance5 = bdat.getMember("Enhance5");
}

unsigned int getBTL_Skill_BlEnhance5(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlEnhance5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_BlEnhance5, id, 2);
    }
    return 0;
}

void initBTL_Skill_BlFlagcommon(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlFlagcommonFlag = bdat.getMember("Flag");
    s_memberBTL_Skill_BlFlagcommon = bdat.getMember("common");
}
bool isBTL_Skill_BlFlagcommon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlFlagcommonFlag != nullptr && s_memberBTL_Skill_BlFlagcommon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberBTL_Skill_BlFlagcommonFlag, id, s_memberBTL_Skill_BlFlagcommon) != 0;
    }
    return false;
}


void initBTL_Skill_BlTank(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlTank = bdat.getMember("Tank");
}

unsigned int getBTL_Skill_BlTank(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlTank != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_Skill_BlTank, id, 1);
    }
    return 0;
}

void initBTL_Skill_BlAttacker(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlAttacker = bdat.getMember("Attacker");
}

unsigned int getBTL_Skill_BlAttacker(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlAttacker != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_Skill_BlAttacker, id, 1);
    }
    return 0;
}

void initBTL_Skill_BlHealer(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlHealer = bdat.getMember("Healer");
}

unsigned int getBTL_Skill_BlHealer(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_BlHealer != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_Skill_BlHealer, id, 1);
    }
    return 0;
}

void initBTL_Skill_BlUI(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_BlUI = bdat.getMember("UI");
}

void initBTL_Skill_DrName(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_DrName = bdat.getMember("Name");
}

unsigned int getBTL_Skill_DrName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_DrName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_DrName, id, 2);
    }
    return 0;
}

void initBTL_Skill_DrDebugName(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_DrDebugName = bdat.getMember("DebugName");
}

void initBTL_Skill_DrEnhance(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_DrEnhance = bdat.getMember("Enhance");
}

unsigned int getBTL_Skill_DrEnhance(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Skill_DrEnhance != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Skill_DrEnhance, id, 2);
    }
    return 0;
}

void initBTL_Skill_DrUI(const CBdatWrapper& bdat) {
    s_memberBTL_Skill_DrUI = bdat.getMember("UI");
}

void initBTL_BuffName(const CBdatWrapper& bdat) {
    s_memberBTL_BuffName = bdat.getMember("Name");
}

unsigned int getBTL_BuffName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_BuffName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_BuffName, id, 1);
    }
    return 0;
}

void initBTL_BuffDebugName(const CBdatWrapper& bdat) {
    s_memberBTL_BuffDebugName = bdat.getMember("DebugName");
}

void initBTL_BuffCaption(const CBdatWrapper& bdat) {
    s_memberBTL_BuffCaption = bdat.getMember("Caption");
}

unsigned int getBTL_BuffCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_BuffCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_BuffCaption, id, 1);
    }
    return 0;
}

void initBTL_BuffBaseNum(const CBdatWrapper& bdat) {
    s_memberBTL_BuffBaseNum = bdat.getMember("BaseNum");
}

void initBTL_BuffBaseTime(const CBdatWrapper& bdat) {
    s_memberBTL_BuffBaseTime = bdat.getMember("BaseTime");
}

void initBTL_BuffBaseRecast(const CBdatWrapper& bdat) {
    s_memberBTL_BuffBaseRecast = bdat.getMember("BaseRecast");
}

void initBTL_BuffBaseProb(const CBdatWrapper& bdat) {
    s_memberBTL_BuffBaseProb = bdat.getMember("BaseProb");
}

void initBTL_BuffInterval(const CBdatWrapper& bdat) {
    s_memberBTL_BuffInterval = bdat.getMember("Interval");
}

void initBTL_BuffEffect(const CBdatWrapper& bdat) {
    s_memberBTL_BuffEffect = bdat.getMember("Effect");
}

void initBTL_BuffIcon(const CBdatWrapper& bdat) {
    s_memberBTL_BuffIcon = bdat.getMember("Icon");
}

void initBTL_Bl_PersonalityFlagcommon(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_PersonalityFlagcommonFlag = bdat.getMember("Flag");
    s_memberBTL_Bl_PersonalityFlagcommon = bdat.getMember("common");
}
bool isBTL_Bl_PersonalityFlagcommon(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_PersonalityFlagcommonFlag != nullptr && s_memberBTL_Bl_PersonalityFlagcommon != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberBTL_Bl_PersonalityFlagcommonFlag, id, s_memberBTL_Bl_PersonalityFlagcommon) != 0;
    }
    return false;
}


void initBTL_Bl_PersonalityKizunaBase(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_PersonalityKizunaBase = bdat.getMember("KizunaBase");
}

void initBTL_Bl_PersonalityVoiceID(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_PersonalityVoiceID = bdat.getMember("VoiceID");
}

unsigned int getBTL_Bl_PersonalityVoiceID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_PersonalityVoiceID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_Bl_PersonalityVoiceID, id, 1);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkLinkNum(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkLinkNum = bdat.getMember("LinkNum");
}

unsigned int getBTL_Bl_KizunaLinkLinkNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkLinkNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkLinkNum, id, 2);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkDeadNum(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkDeadNum = bdat.getMember("DeadNum");
}

void initBTL_Bl_KizunaLinkAppStNum(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkAppStNum = bdat.getMember("AppStNum");
}

unsigned int getBTL_Bl_KizunaLinkAppStNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkAppStNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkAppStNum, id, 2);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkAppEndNum(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkAppEndNum = bdat.getMember("AppEndNum");
}

unsigned int getBTL_Bl_KizunaLinkAppEndNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkAppEndNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkAppEndNum, id, 2);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkAppCond(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkAppCond = bdat.getMember("AppCond");
}

void initBTL_Bl_KizunaLinkAppCondNum(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkAppCondNum = bdat.getMember("AppCondNum");
}

void initBTL_Bl_KizunaLinkReJudgef(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkReJudgef = bdat.getMember("ReJudgef");
}

void initBTL_Bl_KizunaLinkSpActType(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSpActType = bdat.getMember("SpActType");
}

void initBTL_Bl_KizunaLinkSpActNum(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSpActNum = bdat.getMember("SpActNum");
}

void initBTL_Bl_KizunaLinkSpActf(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSpActf = bdat.getMember("SpActf");
}

void initBTL_Bl_KizunaLinkStandDir(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkStandDir = bdat.getMember("StandDir");
}

void initBTL_Bl_KizunaLinkSetKizunaLink1(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSetKizunaLink1 = bdat.getMember("KizunaLink1");
}

unsigned int getBTL_Bl_KizunaLinkSetKizunaLink1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkSetKizunaLink1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkSetKizunaLink1, id, 2);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkSetKizunaLink2(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSetKizunaLink2 = bdat.getMember("KizunaLink2");
}

unsigned int getBTL_Bl_KizunaLinkSetKizunaLink2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkSetKizunaLink2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkSetKizunaLink2, id, 2);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkSetLinkChType(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSetLinkChType = bdat.getMember("LinkChType");
}

unsigned int getBTL_Bl_KizunaLinkSetLinkChType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkSetLinkChType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkSetLinkChType, id, 2);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkSetLinkChNum(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSetLinkChNum = bdat.getMember("LinkChNum");
}

unsigned int getBTL_Bl_KizunaLinkSetLinkChNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkSetLinkChNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkSetLinkChNum, id, 2);
    }
    return 0;
}

void initBTL_Bl_KizunaLinkSetVoiceID(const CBdatWrapper& bdat) {
    s_memberBTL_Bl_KizunaLinkSetVoiceID = bdat.getMember("VoiceID");
}

unsigned int getBTL_Bl_KizunaLinkSetVoiceID(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_Bl_KizunaLinkSetVoiceID != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_Bl_KizunaLinkSetVoiceID, id, 1);
    }
    return 0;
}

void initBTL_TestSettingDr1(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr1 = bdat.getMember("Dr1");
}

void initBTL_TestSettingDr1Lv(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr1Lv = bdat.getMember("Dr1Lv");
}

void initBTL_TestSettingDr1Bl1(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr1Bl1 = bdat.getMember("Dr1Bl1");
}

void initBTL_TestSettingDr1Bl2(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr1Bl2 = bdat.getMember("Dr1Bl2");
}

void initBTL_TestSettingDr1Bl3(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr1Bl3 = bdat.getMember("Dr1Bl3");
}

void initBTL_TestSettingDr2(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr2 = bdat.getMember("Dr2");
}

void initBTL_TestSettingDr2Lv(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr2Lv = bdat.getMember("Dr2Lv");
}

void initBTL_TestSettingDr2Bl1(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr2Bl1 = bdat.getMember("Dr2Bl1");
}

void initBTL_TestSettingDr2Bl2(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr2Bl2 = bdat.getMember("Dr2Bl2");
}

void initBTL_TestSettingDr2Bl3(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr2Bl3 = bdat.getMember("Dr2Bl3");
}

void initBTL_TestSettingDr3(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr3 = bdat.getMember("Dr3");
}

void initBTL_TestSettingDr3Lv(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr3Lv = bdat.getMember("Dr3Lv");
}

void initBTL_TestSettingDr3Bl1(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr3Bl1 = bdat.getMember("Dr3Bl1");
}

void initBTL_TestSettingDr3Bl2(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr3Bl2 = bdat.getMember("Dr3Bl2");
}

void initBTL_TestSettingDr3Bl3(const CBdatWrapper& bdat) {
    s_memberBTL_TestSettingDr3Bl3 = bdat.getMember("Dr3Bl3");
}

void initBTL_HanaBaseNCondNum(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseNCondNum = bdat.getMember("NCondNum");
}

unsigned int getBTL_HanaBaseNCondNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseNCondNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_HanaBaseNCondNum, id, 1);
    }
    return 0;
}

void initBTL_HanaBaseECondNum(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseECondNum = bdat.getMember("ECondNum");
}

unsigned int getBTL_HanaBaseECondNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseECondNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_HanaBaseECondNum, id, 1);
    }
    return 0;
}

void initBTL_HanaBaseNArtsNum(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseNArtsNum = bdat.getMember("NArtsNum");
}

unsigned int getBTL_HanaBaseNArtsNum(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseNArtsNum != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_HanaBaseNArtsNum, id, 1);
    }
    return 0;
}

void initBTL_HanaBaseCircuit1Num(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseCircuit1Num = bdat.getMember("Circuit1Num");
}

unsigned int getBTL_HanaBaseCircuit1Num(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseCircuit1Num != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaBaseCircuit1Num, id, 2);
    }
    return 0;
}

void initBTL_HanaBaseCircuit2Num(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseCircuit2Num = bdat.getMember("Circuit2Num");
}

unsigned int getBTL_HanaBaseCircuit2Num(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseCircuit2Num != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaBaseCircuit2Num, id, 2);
    }
    return 0;
}

void initBTL_HanaBaseCircuit3Num(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseCircuit3Num = bdat.getMember("Circuit3Num");
}

unsigned int getBTL_HanaBaseCircuit3Num(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseCircuit3Num != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaBaseCircuit3Num, id, 2);
    }
    return 0;
}

void initBTL_HanaBaseCircuit4Num(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseCircuit4Num = bdat.getMember("Circuit4Num");
}

unsigned int getBTL_HanaBaseCircuit4Num(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseCircuit4Num != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaBaseCircuit4Num, id, 2);
    }
    return 0;
}

void initBTL_HanaBaseCircuit5Num(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseCircuit5Num = bdat.getMember("Circuit5Num");
}

unsigned int getBTL_HanaBaseCircuit5Num(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseCircuit5Num != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaBaseCircuit5Num, id, 2);
    }
    return 0;
}

void initBTL_HanaBaseCircuit6Num(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseCircuit6Num = bdat.getMember("Circuit6Num");
}

unsigned int getBTL_HanaBaseCircuit6Num(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaBaseCircuit6Num != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaBaseCircuit6Num, id, 2);
    }
    return 0;
}

void initBTL_HanaBaseUI(const CBdatWrapper& bdat) {
    s_memberBTL_HanaBaseUI = bdat.getMember("UI");
}

void initBTL_HanaPowerPowerNum1(const CBdatWrapper& bdat) {
    s_memberBTL_HanaPowerPowerNum1 = bdat.getMember("PowerNum1");
}

unsigned int getBTL_HanaPowerPowerNum1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaPowerPowerNum1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaPowerPowerNum1, id, 2);
    }
    return 0;
}

void initBTL_HanaPowerPowerNum2(const CBdatWrapper& bdat) {
    s_memberBTL_HanaPowerPowerNum2 = bdat.getMember("PowerNum2");
}

unsigned int getBTL_HanaPowerPowerNum2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaPowerPowerNum2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaPowerPowerNum2, id, 2);
    }
    return 0;
}

void initBTL_HanaPowerPowerNum3(const CBdatWrapper& bdat) {
    s_memberBTL_HanaPowerPowerNum3 = bdat.getMember("PowerNum3");
}

unsigned int getBTL_HanaPowerPowerNum3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaPowerPowerNum3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaPowerPowerNum3, id, 2);
    }
    return 0;
}

void initBTL_HanaPowerEtherNum1(const CBdatWrapper& bdat) {
    s_memberBTL_HanaPowerEtherNum1 = bdat.getMember("EtherNum1");
}

unsigned int getBTL_HanaPowerEtherNum1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaPowerEtherNum1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberBTL_HanaPowerEtherNum1, id, 3);
    }
    return 0;
}

void initBTL_HanaPowerEtherNum2(const CBdatWrapper& bdat) {
    s_memberBTL_HanaPowerEtherNum2 = bdat.getMember("EtherNum2");
}

unsigned int getBTL_HanaPowerEtherNum2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaPowerEtherNum2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberBTL_HanaPowerEtherNum2, id, 3);
    }
    return 0;
}

void initBTL_HanaPowerEtherNum3(const CBdatWrapper& bdat) {
    s_memberBTL_HanaPowerEtherNum3 = bdat.getMember("EtherNum3");
}

unsigned int getBTL_HanaPowerEtherNum3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaPowerEtherNum3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getValCheck(s_memberBTL_HanaPowerEtherNum3, id, 3);
    }
    return 0;
}

void initBTL_HanaChipsetRoleParts(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetRoleParts = bdat.getMember("RoleParts");
}

unsigned int getBTL_HanaChipsetRoleParts(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetRoleParts != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetRoleParts, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetAtrParts(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetAtrParts = bdat.getMember("AtrParts");
}

unsigned int getBTL_HanaChipsetAtrParts(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetAtrParts != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetAtrParts, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetNArtsParts1(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetNArtsParts1 = bdat.getMember("NArtsParts1");
}

unsigned int getBTL_HanaChipsetNArtsParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetNArtsParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetNArtsParts1, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetNArtsParts2(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetNArtsParts2 = bdat.getMember("NArtsParts2");
}

unsigned int getBTL_HanaChipsetNArtsParts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetNArtsParts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetNArtsParts2, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetNArtsParts3(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetNArtsParts3 = bdat.getMember("NArtsParts3");
}

unsigned int getBTL_HanaChipsetNArtsParts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetNArtsParts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetNArtsParts3, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetNCondParts1(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetNCondParts1 = bdat.getMember("NCondParts1");
}

unsigned int getBTL_HanaChipsetNCondParts1(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetNCondParts1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetNCondParts1, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetNCondParts2(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetNCondParts2 = bdat.getMember("NCondParts2");
}

unsigned int getBTL_HanaChipsetNCondParts2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetNCondParts2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetNCondParts2, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetNCondParts3(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetNCondParts3 = bdat.getMember("NCondParts3");
}

unsigned int getBTL_HanaChipsetNCondParts3(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_HanaChipsetNCondParts3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_HanaChipsetNCondParts3, id, 2);
    }
    return 0;
}

void initBTL_HanaChipsetUI(const CBdatWrapper& bdat) {
    s_memberBTL_HanaChipsetUI = bdat.getMember("UI");
}

void initWildcardDatavalueF4(const CBdatWrapper& bdat) {
    s_memberWildcardDatavalueF4 = bdat.getMember("valueF4");
}

void initWildcardDatavalueU2(const CBdatWrapper& bdat) {
    s_memberWildcardDatavalueU2 = bdat.getMember("valueU2");
}

unsigned int getWildcardDatavalueU2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberWildcardDatavalueU2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberWildcardDatavalueU2, id, 2);
    }
    return 0;
}

void initVo_Field_FilterTargetFile(const CBdatWrapper& bdat) {
    s_memberVo_Field_FilterTargetFile = bdat.getMember("TargetFile");
}

const char* getVo_Field_FilterTargetFile(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVo_Field_FilterTargetFile != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVo_Field_FilterTargetFile, id, 7);
    }
    return nullptr;
}

void initVo_Field_FilterCondition(const CBdatWrapper& bdat) {
    s_memberVo_Field_FilterCondition = bdat.getMember("Condition");
}

unsigned int getVo_Field_FilterCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVo_Field_FilterCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberVo_Field_FilterCondition, id, 2);
    }
    return 0;
}

void initVo_Field_FilterChangeFile(const CBdatWrapper& bdat) {
    s_memberVo_Field_FilterChangeFile = bdat.getMember("ChangeFile");
}

const char* getVo_Field_FilterChangeFile(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberVo_Field_FilterChangeFile != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberVo_Field_FilterChangeFile, id, 7);
    }
    return nullptr;
}

void initBTL_DifSettingDebugName(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingDebugName = bdat.getMember("DebugName");
}

void initBTL_DifSettingParamMin(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingParamMin = bdat.getMember("ParamMin");
}

unsigned int getBTL_DifSettingParamMin(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingParamMin != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_DifSettingParamMin, id, 1);
    }
    return 0;
}

void initBTL_DifSettingParamMax(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingParamMax = bdat.getMember("ParamMax");
}

unsigned int getBTL_DifSettingParamMax(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingParamMax != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_DifSettingParamMax, id, 2);
    }
    return 0;
}

void initBTL_DifSettingInterval(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingInterval = bdat.getMember("Interval");
}

unsigned int getBTL_DifSettingInterval(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingInterval != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_DifSettingInterval, id, 1);
    }
    return 0;
}

void initBTL_DifSettingNormal(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingNormal = bdat.getMember("Normal");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_DifSetting getters holds it.
// What it does: reads the Normal column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E11BC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingNormal != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_DifSettingNormal, id, 2);
    }
    return 0;
}

void initBTL_DifSettingEasy(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingEasy = bdat.getMember("Easy");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_DifSetting getters holds it.
// What it does: reads the Easy column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1244(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingEasy != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_DifSettingEasy, id, 2);
    }
    return 0;
}

void initBTL_DifSettingHard(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingHard = bdat.getMember("Hard");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_DifSetting getters holds it.
// What it does: reads the Hard column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E12CC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingHard != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_DifSettingHard, id, 2);
    }
    return 0;
}

void initBTL_DifSettingUlt(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingUlt = bdat.getMember("Ult");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_DifSetting getters holds it.
// What it does: reads the Ult column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1354(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingUlt != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_DifSettingUlt, id, 2);
    }
    return 0;
}

void initBTL_DifSettingConditionOri(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingConditionOri = bdat.getMember("ConditionOri");
}

unsigned int getBTL_DifSettingConditionOri(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingConditionOri != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_DifSettingConditionOri, id, 2);
    }
    return 0;
}

void initBTL_DifSettingConditionIra(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingConditionIra = bdat.getMember("ConditionIra");
}

unsigned int getBTL_DifSettingConditionIra(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingConditionIra != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_DifSettingConditionIra, id, 2);
    }
    return 0;
}

void initBTL_DifSettingFlagOri(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingFlagOriFlag = bdat.getMember("Flag");
    s_memberBTL_DifSettingFlagOri = bdat.getMember("Ori");
}
bool isBTL_DifSettingFlagOri(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingFlagOriFlag != nullptr && s_memberBTL_DifSettingFlagOri != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberBTL_DifSettingFlagOriFlag, id, s_memberBTL_DifSettingFlagOri) != 0;
    }
    return false;
}


void initBTL_DifSettingFlagIra(const CBdatWrapper& bdat) {
    s_memberBTL_DifSettingFlagIraFlag = bdat.getMember("Flag");
    s_memberBTL_DifSettingFlagIra = bdat.getMember("Ira");
}
bool isBTL_DifSettingFlagIra(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_DifSettingFlagIraFlag != nullptr && s_memberBTL_DifSettingFlagIra != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberBTL_DifSettingFlagIraFlag, id, s_memberBTL_DifSettingFlagIra) != 0;
    }
    return false;
}


void initBTL_ChBtlRewardSetGoldMin(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetGoldMin = bdat.getMember("GoldMin");
}

void initBTL_ChBtlRewardSetGoldMax(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetGoldMax = bdat.getMember("GoldMax");
}

void initBTL_ChBtlRewardSetGoldPopMin(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetGoldPopMin = bdat.getMember("GoldPopMin");
}

void initBTL_ChBtlRewardSetGoldPopMax(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetGoldPopMax = bdat.getMember("GoldPopMax");
}

void initBTL_ChBtlRewardSetItemNumMin(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetItemNumMin = bdat.getMember("ItemNumMin");
}

void initBTL_ChBtlRewardSetItemNumMax(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetItemNumMax = bdat.getMember("ItemNumMax");
}

void initBTL_ChBtlRewardSetItemValueMin(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetItemValueMin = bdat.getMember("ItemValueMin");
}

void initBTL_ChBtlRewardSetItemValueMax(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetItemValueMax = bdat.getMember("ItemValueMax");
}

void initBTL_ChBtlRewardSetUpCategory1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetUpCategory1 = bdat.getMember("UpCategory1");
}

void initBTL_ChBtlRewardSetUpCategory2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetUpCategory2 = bdat.getMember("UpCategory2");
}

void initBTL_ChBtlRewardSetDownCategory1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetDownCategory1 = bdat.getMember("DownCategory1");
}

void initBTL_ChBtlRewardSetDownCategory2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetDownCategory2 = bdat.getMember("DownCategory2");
}

void initBTL_ChBtlRewardSetUpItemID1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetUpItemID1 = bdat.getMember("UpItemID1");
}

void initBTL_ChBtlRewardSetUpItemID2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetUpItemID2 = bdat.getMember("UpItemID2");
}

void initBTL_ChBtlRewardSetUpItemID3(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetUpItemID3 = bdat.getMember("UpItemID3");
}

void initBTL_ChBtlRewardSetUpItemID4(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetUpItemID4 = bdat.getMember("UpItemID4");
}

void initBTL_ChBtlRewardSetDownItemID1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetDownItemID1 = bdat.getMember("DownItemID1");
}

void initBTL_ChBtlRewardSetDownItemID2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetDownItemID2 = bdat.getMember("DownItemID2");
}

void initBTL_ChBtlRewardSetDownItemID3(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetDownItemID3 = bdat.getMember("DownItemID3");
}

void initBTL_ChBtlRewardSetDownItemID4(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardSetDownItemID4 = bdat.getMember("DownItemID4");
}

void initBTL_ChBtlRewardItemItemID(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardItemItemID = bdat.getMember("ItemID");
}

void initBTL_ChBtlRewardItemItemValue(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardItemItemValue = bdat.getMember("ItemValue");
}

void initBTL_ChBtlRewardItemParam1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlRewardItemParam1 = bdat.getMember("Param1");
}

void initBTL_ChBtlName(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlName = bdat.getMember("Name");
}

unsigned int getBTL_ChBtlName(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlName != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlName, id, 2);
    }
    return 0;
}

void initBTL_ChBtlDebugName(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlDebugName = bdat.getMember("DebugName");
}

void initBTL_ChBtlListNum(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlListNum = bdat.getMember("ListNum");
}

void initBTL_ChBtlDifficult(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlDifficult = bdat.getMember("Difficult");
}

unsigned int getBTL_ChBtlDifficult(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlDifficult != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlDifficult, id, 1);
    }
    return 0;
}

void initBTL_ChBtlWave(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWave = bdat.getMember("Wave");
}

unsigned int getBTL_ChBtlWave(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWave != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlWave, id, 1);
    }
    return 0;
}

void initBTL_ChBtlCaption(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlCaption = bdat.getMember("Caption");
}

unsigned int getBTL_ChBtlCaption(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlCaption != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlCaption, id, 2);
    }
    return 0;
}

void initBTL_ChBtlMapJump(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlMapJump = bdat.getMember("MapJump");
}

unsigned int getBTL_ChBtlMapJump(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlMapJump != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlMapJump, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWeather(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWeather = bdat.getMember("Weather");
}

unsigned int getBTL_ChBtlWeather(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWeather != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlWeather, id, 1);
    }
    return 0;
}

void initBTL_ChBtlType(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlType = bdat.getMember("Type");
}

unsigned int getBTL_ChBtlType(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlType != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlType, id, 1);
    }
    return 0;
}

void initBTL_ChBtlNeedDefeat(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlNeedDefeat = bdat.getMember("NeedDefeat");
}

unsigned int getBTL_ChBtlNeedDefeat(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlNeedDefeat != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlNeedDefeat, id, 2);
    }
    return 0;
}

void initBTL_ChBtlMaxLevel(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlMaxLevel = bdat.getMember("MaxLevel");
}

unsigned int getBTL_ChBtlMaxLevel(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlMaxLevel != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlMaxLevel, id, 1);
    }
    return 0;
}

void initBTL_ChBtlMaxWpnRank(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlMaxWpnRank = bdat.getMember("MaxWpnRank");
}

unsigned int getBTL_ChBtlMaxWpnRank(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlMaxWpnRank != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlMaxWpnRank, id, 1);
    }
    return 0;
}

void initBTL_ChBtlWpnRevTable(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevTable = bdat.getMember("WpnRevTable");
}

unsigned int getBTL_ChBtlWpnRevTable(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevTable != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevTable, id, 2);
    }
    return 0;
}

void initBTL_ChBtlTimeLimit(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTimeLimit = bdat.getMember("TimeLimit");
}

unsigned int getBTL_ChBtlTimeLimit(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlTimeLimit != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlTimeLimit, id, 2);
    }
    return 0;
}

void initBTL_ChBtlJoinNumber(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlJoinNumber = bdat.getMember("JoinNumber");
}

unsigned int getBTL_ChBtlJoinNumber(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlJoinNumber != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlJoinNumber, id, 1);
    }
    return 0;
}

void initBTL_ChBtlDriver1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlDriver1 = bdat.getMember("Driver1");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtl getters holds it.
// What it does: reads the Driver1 column (unsigned char) of a row, as the init function above found it.
unsigned int fn_71001E13DC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlDriver1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlDriver1, id, 1);
    }
    return 0;
}

void initBTL_ChBtlDriver2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlDriver2 = bdat.getMember("Driver2");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtl getters holds it.
// What it does: reads the Driver2 column (unsigned char) of a row, as the init function above found it.
unsigned int fn_71001E1464(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlDriver2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlDriver2, id, 1);
    }
    return 0;
}

void initBTL_ChBtlDriver3(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlDriver3 = bdat.getMember("Driver3");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtl getters holds it.
// What it does: reads the Driver3 column (unsigned char) of a row, as the init function above found it.
unsigned int fn_71001E14EC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlDriver3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_ChBtlDriver3, id, 1);
    }
    return 0;
}

void initBTL_ChBtlNeedItem(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlNeedItem = bdat.getMember("NeedItem");
}

unsigned int getBTL_ChBtlNeedItem(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlNeedItem != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlNeedItem, id, 2);
    }
    return 0;
}

void initBTL_ChBtlCondition(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlCondition = bdat.getMember("Condition");
}

unsigned int getBTL_ChBtlCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlCondition, id, 2);
    }
    return 0;
}

void initBTL_ChBtlConditionCap(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlConditionCap = bdat.getMember("ConditionCap");
}

unsigned int getBTL_ChBtlConditionCap(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlConditionCap != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlConditionCap, id, 2);
    }
    return 0;
}

void initBTL_ChBtlCondition2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlCondition2 = bdat.getMember("Condition2");
}

unsigned int getBTL_ChBtlCondition2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlCondition2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlCondition2, id, 2);
    }
    return 0;
}

void initBTL_ChBtlConditionCap2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlConditionCap2 = bdat.getMember("ConditionCap2");
}

unsigned int getBTL_ChBtlConditionCap2(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlConditionCap2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlConditionCap2, id, 2);
    }
    return 0;
}

void initBTL_ChBtlHideCondition(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlHideCondition = bdat.getMember("HideCondition");
}

unsigned int getBTL_ChBtlHideCondition(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlHideCondition != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlHideCondition, id, 2);
    }
    return 0;
}

void initBTL_ChBtlFlagHide(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlFlagHideFlag = bdat.getMember("Flag");
    s_memberBTL_ChBtlFlagHide = bdat.getMember("Hide");
}
bool isBTL_ChBtlFlagHide(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlFlagHideFlag != nullptr && s_memberBTL_ChBtlFlagHide != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return bdat.getFlagVal(s_memberBTL_ChBtlFlagHideFlag, id, s_memberBTL_ChBtlFlagHide) != 0;
    }
    return false;
}


void initBTL_ChBtlTresureSet1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureSet1 = bdat.getMember("TresureSet1");
}

void initBTL_ChBtlTresureSet2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureSet2 = bdat.getMember("TresureSet2");
}

void initBTL_ChBtlTresureSet3(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureSet3 = bdat.getMember("TresureSet3");
}

void initBTL_ChBtlTresureNeed1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureNeed1 = bdat.getMember("TresureNeed1");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtl getters holds it.
// What it does: reads the TresureNeed1 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1574(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlTresureNeed1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlTresureNeed1, id, 2);
    }
    return 0;
}

void initBTL_ChBtlTresureNeed2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureNeed2 = bdat.getMember("TresureNeed2");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtl getters holds it.
// What it does: reads the TresureNeed2 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E15FC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlTresureNeed2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlTresureNeed2, id, 2);
    }
    return 0;
}

void initBTL_ChBtlTresureNeed3(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureNeed3 = bdat.getMember("TresureNeed3");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtl getters holds it.
// What it does: reads the TresureNeed3 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1684(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlTresureNeed3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlTresureNeed3, id, 2);
    }
    return 0;
}

void initBTL_ChBtlTresureResource1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureResource1 = bdat.getMember("TresureResource1");
}

void initBTL_ChBtlTresureResource2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureResource2 = bdat.getMember("TresureResource2");
}

void initBTL_ChBtlTresureResource3(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlTresureResource3 = bdat.getMember("TresureResource3");
}

void initBTL_ChBtlClearReward(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlClearReward = bdat.getMember("ClearReward");
}

unsigned int getBTL_ChBtlClearReward(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlClearReward != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlClearReward, id, 2);
    }
    return 0;
}

void initBTL_ChBtlEvent(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlEvent = bdat.getMember("Event");
}

unsigned int getBTL_ChBtlEvent(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlEvent != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlEvent, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg1(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg1 = bdat.getMember("WpnDmg1");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg1 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E170C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg1, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg2(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg2 = bdat.getMember("WpnDmg2");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg2 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1794(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg2, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg3(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg3 = bdat.getMember("WpnDmg3");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg3 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E181C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg3, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg4(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg4 = bdat.getMember("WpnDmg4");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg4 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E18A4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg4 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg4, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg5(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg5 = bdat.getMember("WpnDmg5");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg5 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E192C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg5 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg5, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg6(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg6 = bdat.getMember("WpnDmg6");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg6 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E19B4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg6 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg6, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg7(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg7 = bdat.getMember("WpnDmg7");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg7 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1A3C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg7 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg7, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg8(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg8 = bdat.getMember("WpnDmg8");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg8 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1AC4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg8 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg8, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg9(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg9 = bdat.getMember("WpnDmg9");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg9 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1B4C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg9 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg9, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg10(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg10 = bdat.getMember("WpnDmg10");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg10 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1BD4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg10 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg10, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg11(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg11 = bdat.getMember("WpnDmg11");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg11 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1C5C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg11 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg11, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg12(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg12 = bdat.getMember("WpnDmg12");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg12 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1CE4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg12 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg12, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg13(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg13 = bdat.getMember("WpnDmg13");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg13 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1D6C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg13 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg13, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg14(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg14 = bdat.getMember("WpnDmg14");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg14 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1DF4(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg14 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg14, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg15(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg15 = bdat.getMember("WpnDmg15");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg15 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1E7C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg15 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg15, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg16(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg16 = bdat.getMember("WpnDmg16");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg16 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1F04(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg16 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg16, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg17(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg17 = bdat.getMember("WpnDmg17");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg17 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E1F8C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg17 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg17, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg18(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg18 = bdat.getMember("WpnDmg18");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg18 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E2014(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg18 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg18, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg19(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg19 = bdat.getMember("WpnDmg19");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg19 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E209C(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg19 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg19, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg20(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg20 = bdat.getMember("WpnDmg20");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg20 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E2124(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg20 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg20, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg21(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg21 = bdat.getMember("WpnDmg21");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg21 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E21AC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg21 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg21, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg22(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg22 = bdat.getMember("WpnDmg22");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg22 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E2234(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg22 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg22, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg23(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg23 = bdat.getMember("WpnDmg23");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg23 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E22BC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg23 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg23, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg24(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg24 = bdat.getMember("WpnDmg24");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg24 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E2344(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg24 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg24, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg25(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg25 = bdat.getMember("WpnDmg25");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg25 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E23CC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg25 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg25, id, 2);
    }
    return 0;
}

void initBTL_ChBtlWpnRevWpnDmg26(const CBdatWrapper& bdat) {
    s_memberBTL_ChBtlWpnRevWpnDmg26 = bdat.getMember("WpnDmg26");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_ChBtlWpnRev getters holds it.
// What it does: reads the WpnDmg26 column (unsigned short) of a row, as the init function above found it.
unsigned int fn_71001E2454(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_ChBtlWpnRevWpnDmg26 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBTL_ChBtlWpnRevWpnDmg26, id, 2);
    }
    return 0;
}

void initBTL_IrGroupRevGroupRev1(const CBdatWrapper& bdat) {
    s_memberBTL_IrGroupRevGroupRev1 = bdat.getMember("GroupRev1");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_IrGroupRev getters holds it.
// What it does: reads the GroupRev1 column (unsigned char) of a row, as the init function above found it.
unsigned int fn_71001E24DC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_IrGroupRevGroupRev1 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_IrGroupRevGroupRev1, id, 1);
    }
    return 0;
}

void initBTL_IrGroupRevGroupRev2(const CBdatWrapper& bdat) {
    s_memberBTL_IrGroupRevGroupRev2 = bdat.getMember("GroupRev2");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_IrGroupRev getters holds it.
// What it does: reads the GroupRev2 column (unsigned char) of a row, as the init function above found it.
unsigned int fn_71001E2564(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_IrGroupRevGroupRev2 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_IrGroupRevGroupRev2, id, 1);
    }
    return 0;
}

void initBTL_IrGroupRevGroupRev3(const CBdatWrapper& bdat) {
    s_memberBTL_IrGroupRevGroupRev3 = bdat.getMember("GroupRev3");
}

// Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it; a slot table of BTL_IrGroupRev getters holds it.
// What it does: reads the GroupRev3 column (unsigned char) of a row, as the init function above found it.
unsigned int fn_71001E25EC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBTL_IrGroupRevGroupRev3 != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBTL_IrGroupRevGroupRev3, id, 1);
    }
    return 0;
}

// a slot table's getter for a slot (the name is not the original's). The original's slot tables are writable data
// (.data): clang 3.9 makes a static table constant unless its address is passed on before inlining, so its slot
// getters handed the table to an inline helper like this one.
template <class Getter, unsigned long N>
inline Getter getSlot(Getter (&table)[N], unsigned int slot) {
    return table[slot];
}

}  // namespace _gfbbt

GfBdatBtl::GfBdatBtl() {
    m_fpArtsDr = nullptr;
    m_fpArtsBl = nullptr;
    m_fpArtsBlSp = nullptr;
    m_fpGrow = nullptr;
    m_fpLv_Rev = nullptr;
    m_fpWpn_En = nullptr;
    m_fpBTL_Class = nullptr;
    m_fpBTL_Enhance = nullptr;
    m_fpBTL_EnhanceEff = nullptr;
    m_fpBTL_Skill_Bl = nullptr;
    m_fpBTL_Skill_Dr = nullptr;
    m_fpBTL_Buff = nullptr;
    m_fpBTL_Bl_Personality = nullptr;
    m_fpBTL_Bl_KizunaLink = nullptr;
    m_fpBTL_Bl_KizunaLinkSet = nullptr;
    m_fpBTL_TestSetting = nullptr;
    m_fpBTL_HanaBase = nullptr;
    m_fpBTL_HanaPower = nullptr;
    m_fpBTL_HanaChipset = nullptr;
    m_fpWildcardData = nullptr;
    m_fpVo_Field_Filter = nullptr;
    m_fpBTL_DifSetting = nullptr;
    m_fpBTL_ChBtlRewardSet = nullptr;
    m_fpBTL_ChBtlRewardItem = nullptr;
    m_fpBTL_ChBtl = nullptr;
    m_fpBTL_ChBtlWpnRev = nullptr;
    m_fpBTL_IrGroupRev = nullptr;
    bdatRefresh();
}

GfBdatBtl::~GfBdatBtl() {
    destroyFP();
}

void GfBdatBtl::destroyFP() {
    if (m_fpArtsDr != nullptr) {
        delete m_fpArtsDr;
        m_fpArtsDr = nullptr;
    }
    if (m_fpArtsBl != nullptr) {
        delete m_fpArtsBl;
        m_fpArtsBl = nullptr;
    }
    if (m_fpArtsBlSp != nullptr) {
        delete m_fpArtsBlSp;
        m_fpArtsBlSp = nullptr;
    }
    if (m_fpGrow != nullptr) {
        delete m_fpGrow;
        m_fpGrow = nullptr;
    }
    if (m_fpLv_Rev != nullptr) {
        delete m_fpLv_Rev;
        m_fpLv_Rev = nullptr;
    }
    if (m_fpWpn_En != nullptr) {
        delete m_fpWpn_En;
        m_fpWpn_En = nullptr;
    }
    if (m_fpBTL_Class != nullptr) {
        delete m_fpBTL_Class;
        m_fpBTL_Class = nullptr;
    }
    if (m_fpBTL_Enhance != nullptr) {
        delete m_fpBTL_Enhance;
        m_fpBTL_Enhance = nullptr;
    }
    if (m_fpBTL_EnhanceEff != nullptr) {
        delete m_fpBTL_EnhanceEff;
        m_fpBTL_EnhanceEff = nullptr;
    }
    if (m_fpBTL_Skill_Bl != nullptr) {
        delete m_fpBTL_Skill_Bl;
        m_fpBTL_Skill_Bl = nullptr;
    }
    if (m_fpBTL_Skill_Dr != nullptr) {
        delete m_fpBTL_Skill_Dr;
        m_fpBTL_Skill_Dr = nullptr;
    }
    if (m_fpBTL_Buff != nullptr) {
        delete m_fpBTL_Buff;
        m_fpBTL_Buff = nullptr;
    }
    if (m_fpBTL_Bl_Personality != nullptr) {
        delete m_fpBTL_Bl_Personality;
        m_fpBTL_Bl_Personality = nullptr;
    }
    if (m_fpBTL_Bl_KizunaLink != nullptr) {
        delete m_fpBTL_Bl_KizunaLink;
        m_fpBTL_Bl_KizunaLink = nullptr;
    }
    if (m_fpBTL_Bl_KizunaLinkSet != nullptr) {
        delete m_fpBTL_Bl_KizunaLinkSet;
        m_fpBTL_Bl_KizunaLinkSet = nullptr;
    }
    if (m_fpBTL_TestSetting != nullptr) {
        delete m_fpBTL_TestSetting;
        m_fpBTL_TestSetting = nullptr;
    }
    if (m_fpBTL_HanaBase != nullptr) {
        delete m_fpBTL_HanaBase;
        m_fpBTL_HanaBase = nullptr;
    }
    if (m_fpBTL_HanaPower != nullptr) {
        delete m_fpBTL_HanaPower;
        m_fpBTL_HanaPower = nullptr;
    }
    if (m_fpBTL_HanaChipset != nullptr) {
        delete m_fpBTL_HanaChipset;
        m_fpBTL_HanaChipset = nullptr;
    }
    if (m_fpWildcardData != nullptr) {
        delete m_fpWildcardData;
        m_fpWildcardData = nullptr;
    }
    if (m_fpVo_Field_Filter != nullptr) {
        delete m_fpVo_Field_Filter;
        m_fpVo_Field_Filter = nullptr;
    }
    if (m_fpBTL_DifSetting != nullptr) {
        delete m_fpBTL_DifSetting;
        m_fpBTL_DifSetting = nullptr;
    }
    if (m_fpBTL_ChBtlRewardSet != nullptr) {
        delete m_fpBTL_ChBtlRewardSet;
        m_fpBTL_ChBtlRewardSet = nullptr;
    }
    if (m_fpBTL_ChBtlRewardItem != nullptr) {
        delete m_fpBTL_ChBtlRewardItem;
        m_fpBTL_ChBtlRewardItem = nullptr;
    }
    if (m_fpBTL_ChBtl != nullptr) {
        delete m_fpBTL_ChBtl;
        m_fpBTL_ChBtl = nullptr;
    }
    if (m_fpBTL_ChBtlWpnRev != nullptr) {
        delete m_fpBTL_ChBtlWpnRev;
        m_fpBTL_ChBtlWpnRev = nullptr;
    }
    if (m_fpBTL_IrGroupRev != nullptr) {
        delete m_fpBTL_IrGroupRev;
        m_fpBTL_IrGroupRev = nullptr;
    }
}

void GfBdatBtl::createFP() {
#line 831
    m_fpArtsDr = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x1));
#line 832
    m_fpArtsBl = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x2));
#line 833
    m_fpArtsBlSp = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x4));
#line 834
    m_fpGrow = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x2F));
#line 835
    m_fpLv_Rev = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x34));
#line 836
    m_fpWpn_En = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x45));
#line 837
    m_fpBTL_Class = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x18));
#line 838
    m_fpBTL_Enhance = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x2C));
#line 839
    m_fpBTL_EnhanceEff = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x2D));
#line 840
    m_fpBTL_Skill_Bl = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x3F));
#line 841
    m_fpBTL_Skill_Dr = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x3E));
#line 842
    m_fpBTL_Buff = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x11));
#line 843
    m_fpBTL_Bl_Personality = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xE));
#line 844
    m_fpBTL_Bl_KizunaLink = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xD));
#line 845
    m_fpBTL_Bl_KizunaLinkSet = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xC));
#line 846
    m_fpBTL_TestSetting = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x46));
#line 848
    m_fpBTL_HanaBase = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x47));
#line 849
    m_fpBTL_HanaPower = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x48));
#line 850
    m_fpBTL_HanaChipset = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x49));
#line 851
    m_fpWildcardData = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x7B));
#line 852
    m_fpVo_Field_Filter = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x5C));
#line 853
    m_fpBTL_DifSetting = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x1F));
#line 855
    m_fpBTL_ChBtlRewardSet = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x4A));
#line 856
    m_fpBTL_ChBtlRewardItem = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x4B));
#line 857
    m_fpBTL_ChBtl = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x4D));
#line 858
    m_fpBTL_ChBtlWpnRev = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x4C));
#line 859
    m_fpBTL_IrGroupRev = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0x4F));
}

void GfBdatBtl::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbbt::initArtsDrName(*m_fpArtsDr);
    _gfbbt::initArtsDrDebugName(*m_fpArtsDr);
    _gfbbt::initArtsDrCaption(*m_fpArtsDr);
    _gfbbt::initArtsDrCondCap(*m_fpArtsDr);
    _gfbbt::initArtsDrTalentCap(*m_fpArtsDr);
    _gfbbt::initArtsDrDriver(*m_fpArtsDr);
    _gfbbt::initArtsDrWpnType(*m_fpArtsDr);
    _gfbbt::initArtsDrIrType(*m_fpArtsDr);
    _gfbbt::initArtsDrCondition(*m_fpArtsDr);
    _gfbbt::initArtsDrActNo(*m_fpArtsDr);
    _gfbbt::initArtsDrArtsType(*m_fpArtsDr);
    _gfbbt::initArtsDrArtsBuff(*m_fpArtsDr);
    _gfbbt::initArtsDrAtrType(*m_fpArtsDr);
    _gfbbt::initArtsDrFlagNormal(*m_fpArtsDr);
    _gfbbt::initArtsDrFlagPierce(*m_fpArtsDr);
    _gfbbt::initArtsDrFlagNoRepelled(*m_fpArtsDr);
    _gfbbt::initArtsDrNextArts(*m_fpArtsDr);
    _gfbbt::initArtsDrTarget(*m_fpArtsDr);
    _gfbbt::initArtsDrDistance(*m_fpArtsDr);
    _gfbbt::initArtsDrRangeType(*m_fpArtsDr);
    _gfbbt::initArtsDrRadius(*m_fpArtsDr);
    _gfbbt::initArtsDrLength(*m_fpArtsDr);
    _gfbbt::initArtsDrHate(*m_fpArtsDr);
    _gfbbt::initArtsDrHitRevise(*m_fpArtsDr);
    _gfbbt::initArtsDrCriRevise(*m_fpArtsDr);
    _gfbbt::initArtsDrBulletID(*m_fpArtsDr);
    _gfbbt::initArtsDrBulletNum(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm1(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm2(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm3(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm4(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm5(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm6(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm7(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm8(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm9(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm10(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm11(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm12(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm13(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm14(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm15(*m_fpArtsDr);
    _gfbbt::initArtsDrHitFrm16(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp1(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp2(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp3(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp4(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp5(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp6(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp7(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp8(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp9(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp10(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp11(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp12(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp13(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp14(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp15(*m_fpArtsDr);
    _gfbbt::initArtsDrEfp16(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID1(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID2(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID3(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID4(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID5(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID6(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID7(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID8(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID9(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID10(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID11(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID12(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID13(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID14(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID15(*m_fpArtsDr);
    _gfbbt::initArtsDrHitDirID16(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt1(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt2(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt3(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt4(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt5(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt6(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt7(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt8(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt9(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt10(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt11(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt12(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt13(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt14(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt15(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgRt16(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct1(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct2(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct3(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct4(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct5(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct6(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct7(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct8(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct9(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct10(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct11(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct12(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct13(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct14(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct15(*m_fpArtsDr);
    _gfbbt::initArtsDrReAct16(*m_fpArtsDr);
    _gfbbt::initArtsDrMoveCancelFrm(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgMgn1(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgMgn2(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgMgn3(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgMgn4(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgMgn5(*m_fpArtsDr);
    _gfbbt::initArtsDrDmgMgn6(*m_fpArtsDr);
    _gfbbt::initArtsDrRecast1(*m_fpArtsDr);
    _gfbbt::initArtsDrRecast2(*m_fpArtsDr);
    _gfbbt::initArtsDrRecast3(*m_fpArtsDr);
    _gfbbt::initArtsDrRecast4(*m_fpArtsDr);
    _gfbbt::initArtsDrRecast5(*m_fpArtsDr);
    _gfbbt::initArtsDrRecast6(*m_fpArtsDr);
    _gfbbt::initArtsDrAtrNum(*m_fpArtsDr);
    _gfbbt::initArtsDrEnhance1(*m_fpArtsDr);
    _gfbbt::initArtsDrEnhance2(*m_fpArtsDr);
    _gfbbt::initArtsDrEnhance3(*m_fpArtsDr);
    _gfbbt::initArtsDrEnhance4(*m_fpArtsDr);
    _gfbbt::initArtsDrEnhance5(*m_fpArtsDr);
    _gfbbt::initArtsDrEnhance6(*m_fpArtsDr);
    _gfbbt::initArtsDrReleaseLv1(*m_fpArtsDr);
    _gfbbt::initArtsDrReleaseLv2(*m_fpArtsDr);
    _gfbbt::initArtsDrReleaseLv3(*m_fpArtsDr);
    _gfbbt::initArtsDrReleaseLv4(*m_fpArtsDr);
    _gfbbt::initArtsDrReleaseLv5(*m_fpArtsDr);
    _gfbbt::initArtsDrNeedWP2(*m_fpArtsDr);
    _gfbbt::initArtsDrNeedWP3(*m_fpArtsDr);
    _gfbbt::initArtsDrNeedWP4(*m_fpArtsDr);
    _gfbbt::initArtsDrNeedWP5(*m_fpArtsDr);
    _gfbbt::initArtsDrUI(*m_fpArtsDr);
    _gfbbt::initArtsDrPriority(*m_fpArtsDr);
    _gfbbt::initArtsBlName(*m_fpArtsBl);
    _gfbbt::initArtsBlDebugName(*m_fpArtsBl);
    _gfbbt::initArtsBlCaption(*m_fpArtsBl);
    _gfbbt::initArtsBlWpnType(*m_fpArtsBl);
    _gfbbt::initArtsBlCmnBlType(*m_fpArtsBl);
    _gfbbt::initArtsBlSpLv(*m_fpArtsBl);
    _gfbbt::initArtsBlActNo(*m_fpArtsBl);
    _gfbbt::initArtsBlArtsType(*m_fpArtsBl);
    _gfbbt::initArtsBlArtsBuff(*m_fpArtsBl);
    _gfbbt::initArtsBlFlagcommon(*m_fpArtsBl);
    _gfbbt::initArtsBlFlagPierce(*m_fpArtsBl);
    _gfbbt::initArtsBlTarget(*m_fpArtsBl);
    _gfbbt::initArtsBlDistance(*m_fpArtsBl);
    _gfbbt::initArtsBlRangeType(*m_fpArtsBl);
    _gfbbt::initArtsBlRadius(*m_fpArtsBl);
    _gfbbt::initArtsBlLength(*m_fpArtsBl);
    _gfbbt::initArtsBlAtr(*m_fpArtsBl);
    _gfbbt::initArtsBlHate(*m_fpArtsBl);
    _gfbbt::initArtsBlHitRevise(*m_fpArtsBl);
    _gfbbt::initArtsBlCriRevise(*m_fpArtsBl);
    _gfbbt::initArtsBlBulletID(*m_fpArtsBl);
    _gfbbt::initArtsBlBulletNum(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm1(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm2(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm3(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm4(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm5(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm6(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm7(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm8(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm9(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm10(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm11(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm12(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm13(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm14(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm15(*m_fpArtsBl);
    _gfbbt::initArtsBlHitFrm16(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp1(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp2(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp3(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp4(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp5(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp6(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp7(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp8(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp9(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp10(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp11(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp12(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp13(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp14(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp15(*m_fpArtsBl);
    _gfbbt::initArtsBlEfp16(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID1(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID2(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID3(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID4(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID5(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID6(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID7(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID8(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID9(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID10(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID11(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID12(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID13(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID14(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID15(*m_fpArtsBl);
    _gfbbt::initArtsBlHitDirID16(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt1(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt2(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt3(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt4(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt5(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt6(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt7(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt8(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt9(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt10(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt11(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt12(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt13(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt14(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt15(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgRt16(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct1(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct2(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct3(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct4(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct5(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct6(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct7(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct8(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct9(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct10(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct11(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct12(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct13(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct14(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct15(*m_fpArtsBl);
    _gfbbt::initArtsBlReAct16(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgMgn1(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgMgn2(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgMgn3(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgMgn4(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgMgn5(*m_fpArtsBl);
    _gfbbt::initArtsBlDmgMgn6(*m_fpArtsBl);
    _gfbbt::initArtsBlAtrNum(*m_fpArtsBl);
    _gfbbt::initArtsBlEnhance1(*m_fpArtsBl);
    _gfbbt::initArtsBlEnhance2(*m_fpArtsBl);
    _gfbbt::initArtsBlEnhance3(*m_fpArtsBl);
    _gfbbt::initArtsBlEnhance4(*m_fpArtsBl);
    _gfbbt::initArtsBlEnhance5(*m_fpArtsBl);
    _gfbbt::initArtsBlEnhance6(*m_fpArtsBl);
    _gfbbt::initArtsBlBtnType(*m_fpArtsBl);
    _gfbbt::initArtsBlBtnChal1(*m_fpArtsBl);
    _gfbbt::initArtsBlUI(*m_fpArtsBl);
    _gfbbt::initArtsBlSpName(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDebugName(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCaption(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpWpnType(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCondition(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCmnBlType(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpActNoDr(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpActNoBl(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpActNoBl2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpBuddyDr(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpAddBl(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpActType(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpPC01(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpPC02(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpPC03(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpPC06(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpArtsType(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpArtsBuff(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpFlagPierce(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpFlagNoMove(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpTarget(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDistance(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpRangeType(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpRadius(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpLength(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpAtr(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHate(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitRevise(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCriRevise(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpBulletID(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpBulletEffID(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpBulletNum(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm3(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm4(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm5(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm6(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm7(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm8(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm9(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm10(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm11(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm12(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm13(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm14(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm15(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitFrm16(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp3(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp4(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp5(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp6(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp7(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp8(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp9(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp10(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp11(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp12(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp13(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp14(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp15(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEfp16(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID3(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID4(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID5(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID6(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID7(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID8(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID9(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID10(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID11(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID12(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID13(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID14(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID15(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitDirID16(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt3(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt4(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt5(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt6(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt7(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt8(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt9(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt10(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt11(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt12(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt13(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt14(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt15(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgRt16(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct3(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct4(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct5(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct6(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct7(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct8(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct9(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct10(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct11(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct12(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct13(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct14(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct15(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpReAct16(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpDmgMgn(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpRecast(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpAtrNum(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpEnhance(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpBtnType(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpBtnChal1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCamera1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCamera2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCamera3(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCameraCT1(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCameraCT2(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpCameraEndf(*m_fpArtsBlSp);
    _gfbbt::initArtsBlSpHitEff(*m_fpArtsBlSp);
    _gfbbt::initGrowLevelExp(*m_fpGrow);
    _gfbbt::initGrowLevelExp2(*m_fpGrow);
    _gfbbt::initGrowEnemyExp(*m_fpGrow);
    _gfbbt::initGrowEnemyWP(*m_fpGrow);
    _gfbbt::initGrowEnemySP(*m_fpGrow);
    _gfbbt::initGrowEnemyGold(*m_fpGrow);
    _gfbbt::initGrowGoldDivide(*m_fpGrow);
    _gfbbt::initLv_RevExpRevHigh(*m_fpLv_Rev);
    _gfbbt::initLv_RevExpRevLow(*m_fpLv_Rev);
    _gfbbt::initLv_RevDamageRevHigh(*m_fpLv_Rev);
    _gfbbt::initLv_RevDamageRevLow(*m_fpLv_Rev);
    _gfbbt::initWpn_EnRscR(*m_fpWpn_En);
    _gfbbt::initWpn_EnRscL(*m_fpWpn_En);
    _gfbbt::initWpn_EnTypeRange(*m_fpWpn_En);
    _gfbbt::initWpn_EnDamage(*m_fpWpn_En);
    _gfbbt::initWpn_EnStability(*m_fpWpn_En);
    _gfbbt::initBTL_ClassName(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassRole1(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassRole2(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassRole3(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassDamageDown(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassDamageUP(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassHealUP(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassAutoHate(*m_fpBTL_Class);
    _gfbbt::initBTL_ClassArtsHate(*m_fpBTL_Class);
    _gfbbt::initBTL_EnhanceEnhanceEffect(*m_fpBTL_Enhance);
    _gfbbt::initBTL_EnhanceParam1(*m_fpBTL_Enhance);
    _gfbbt::initBTL_EnhanceParam2(*m_fpBTL_Enhance);
    _gfbbt::initBTL_EnhanceCaption(*m_fpBTL_Enhance);
    _gfbbt::initBTL_EnhanceCaption2(*m_fpBTL_Enhance);
    _gfbbt::initBTL_EnhanceEffCategory(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_EnhanceEffIcon(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_EnhanceEffFlagCondition(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_EnhanceEffFlagUI(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_EnhanceEffParam(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_EnhanceEffName(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_EnhanceEffDirect(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_EnhanceEffSortCat(*m_fpBTL_EnhanceEff);
    _gfbbt::initBTL_Skill_BlName(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlDebugName(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlEnhance1(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlEnhance2(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlEnhance3(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlEnhance4(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlEnhance5(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlFlagcommon(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlTank(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlAttacker(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlHealer(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_BlUI(*m_fpBTL_Skill_Bl);
    _gfbbt::initBTL_Skill_DrName(*m_fpBTL_Skill_Dr);
    _gfbbt::initBTL_Skill_DrDebugName(*m_fpBTL_Skill_Dr);
    _gfbbt::initBTL_Skill_DrEnhance(*m_fpBTL_Skill_Dr);
    _gfbbt::initBTL_Skill_DrUI(*m_fpBTL_Skill_Dr);
    _gfbbt::initBTL_BuffName(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffDebugName(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffCaption(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffBaseNum(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffBaseTime(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffBaseRecast(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffBaseProb(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffInterval(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffEffect(*m_fpBTL_Buff);
    _gfbbt::initBTL_BuffIcon(*m_fpBTL_Buff);
    _gfbbt::initBTL_Bl_PersonalityFlagcommon(*m_fpBTL_Bl_Personality);
    _gfbbt::initBTL_Bl_PersonalityKizunaBase(*m_fpBTL_Bl_Personality);
    _gfbbt::initBTL_Bl_PersonalityVoiceID(*m_fpBTL_Bl_Personality);
    _gfbbt::initBTL_Bl_KizunaLinkLinkNum(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkDeadNum(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkAppStNum(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkAppEndNum(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkAppCond(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkAppCondNum(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkReJudgef(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkSpActType(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkSpActNum(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkSpActf(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkStandDir(*m_fpBTL_Bl_KizunaLink);
    _gfbbt::initBTL_Bl_KizunaLinkSetKizunaLink1(*m_fpBTL_Bl_KizunaLinkSet);
    _gfbbt::initBTL_Bl_KizunaLinkSetKizunaLink2(*m_fpBTL_Bl_KizunaLinkSet);
    _gfbbt::initBTL_Bl_KizunaLinkSetLinkChType(*m_fpBTL_Bl_KizunaLinkSet);
    _gfbbt::initBTL_Bl_KizunaLinkSetLinkChNum(*m_fpBTL_Bl_KizunaLinkSet);
    _gfbbt::initBTL_Bl_KizunaLinkSetVoiceID(*m_fpBTL_Bl_KizunaLinkSet);
    _gfbbt::initBTL_TestSettingDr1(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr1Lv(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr1Bl1(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr1Bl2(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr1Bl3(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr2(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr2Lv(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr2Bl1(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr2Bl2(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr2Bl3(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr3(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr3Lv(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr3Bl1(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr3Bl2(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_TestSettingDr3Bl3(*m_fpBTL_TestSetting);
    _gfbbt::initBTL_HanaBaseNCondNum(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseECondNum(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseNArtsNum(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseCircuit1Num(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseCircuit2Num(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseCircuit3Num(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseCircuit4Num(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseCircuit5Num(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseCircuit6Num(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaBaseUI(*m_fpBTL_HanaBase);
    _gfbbt::initBTL_HanaPowerPowerNum1(*m_fpBTL_HanaPower);
    _gfbbt::initBTL_HanaPowerPowerNum2(*m_fpBTL_HanaPower);
    _gfbbt::initBTL_HanaPowerPowerNum3(*m_fpBTL_HanaPower);
    _gfbbt::initBTL_HanaPowerEtherNum1(*m_fpBTL_HanaPower);
    _gfbbt::initBTL_HanaPowerEtherNum2(*m_fpBTL_HanaPower);
    _gfbbt::initBTL_HanaPowerEtherNum3(*m_fpBTL_HanaPower);
    _gfbbt::initBTL_HanaChipsetRoleParts(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetAtrParts(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetNArtsParts1(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetNArtsParts2(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetNArtsParts3(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetNCondParts1(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetNCondParts2(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetNCondParts3(*m_fpBTL_HanaChipset);
    _gfbbt::initBTL_HanaChipsetUI(*m_fpBTL_HanaChipset);
    _gfbbt::initWildcardDatavalueF4(*m_fpWildcardData);
    _gfbbt::initWildcardDatavalueU2(*m_fpWildcardData);
    _gfbbt::initVo_Field_FilterTargetFile(*m_fpVo_Field_Filter);
    _gfbbt::initVo_Field_FilterCondition(*m_fpVo_Field_Filter);
    _gfbbt::initVo_Field_FilterChangeFile(*m_fpVo_Field_Filter);
    _gfbbt::initBTL_DifSettingDebugName(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingParamMin(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingParamMax(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingInterval(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingNormal(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingEasy(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingHard(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingUlt(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingConditionOri(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingConditionIra(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingFlagOri(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_DifSettingFlagIra(*m_fpBTL_DifSetting);
    _gfbbt::initBTL_ChBtlRewardSetGoldMin(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetGoldMax(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetGoldPopMin(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetGoldPopMax(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetItemNumMin(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetItemNumMax(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetItemValueMin(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetItemValueMax(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetUpCategory1(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetUpCategory2(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetDownCategory1(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetDownCategory2(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetUpItemID1(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetUpItemID2(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetUpItemID3(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetUpItemID4(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetDownItemID1(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetDownItemID2(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetDownItemID3(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardSetDownItemID4(*m_fpBTL_ChBtlRewardSet);
    _gfbbt::initBTL_ChBtlRewardItemItemID(*m_fpBTL_ChBtlRewardItem);
    _gfbbt::initBTL_ChBtlRewardItemItemValue(*m_fpBTL_ChBtlRewardItem);
    _gfbbt::initBTL_ChBtlRewardItemParam1(*m_fpBTL_ChBtlRewardItem);
    _gfbbt::initBTL_ChBtlName(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlDebugName(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlListNum(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlDifficult(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlWave(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlCaption(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlMapJump(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlWeather(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlType(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlNeedDefeat(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlMaxLevel(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlMaxWpnRank(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlWpnRevTable(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTimeLimit(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlJoinNumber(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlDriver1(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlDriver2(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlDriver3(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlNeedItem(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlCondition(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlConditionCap(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlCondition2(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlConditionCap2(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlHideCondition(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlFlagHide(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureSet1(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureSet2(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureSet3(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureNeed1(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureNeed2(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureNeed3(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureResource1(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureResource2(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlTresureResource3(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlClearReward(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlEvent(*m_fpBTL_ChBtl);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg1(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg2(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg3(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg4(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg5(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg6(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg7(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg8(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg9(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg10(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg11(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg12(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg13(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg14(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg15(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg16(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg17(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg18(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg19(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg20(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg21(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg22(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg23(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg24(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg25(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_ChBtlWpnRevWpnDmg26(*m_fpBTL_ChBtlWpnRev);
    _gfbbt::initBTL_IrGroupRevGroupRev1(*m_fpBTL_IrGroupRev);
    _gfbbt::initBTL_IrGroupRevGroupRev2(*m_fpBTL_IrGroupRev);
    _gfbbt::initBTL_IrGroupRevGroupRev3(*m_fpBTL_IrGroupRev);
}

unsigned int GfBdatBtl::getArtsDrStart() const {
    return Bdat::getIdTop(m_fpArtsDr->m_fp);
}

unsigned int GfBdatBtl::getArtsDrEnd() const {
    return Bdat::getIdTop(m_fpArtsDr->m_fp) + Bdat::getIdCount(m_fpArtsDr->m_fp);
}

unsigned int GfBdatBtl::getArtsDrName(unsigned int id) const {
    return _gfbbt::getArtsDrName(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrCaption(unsigned int id) const {
    return _gfbbt::getArtsDrCaption(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrDebugName(unsigned int id) const {
    return _gfbbt::getArtsDrCondCap(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrUI(unsigned int id) const {
    return _gfbbt::getArtsDrTalentCap(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrDriver(unsigned int id) const {
    return _gfbbt::getArtsDrDriver(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrWpnType(unsigned int id) const {
    return _gfbbt::getArtsDrWpnType(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrIrType(unsigned int id) const {
    return _gfbbt::getArtsDrIrType(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrArtsType(unsigned int id) const {
    return _gfbbt::getArtsDrArtsType(*m_fpArtsDr, id);
}

bool GfBdatBtl::isArtsDrFlagNormal(unsigned int id) const {
    return _gfbbt::isArtsDrFlagNormal(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrReleaseLv1(unsigned int id) const {
    return _gfbbt::getArtsDrReleaseLv1(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrPriority(unsigned int id) const {
    return _gfbbt::getArtsDrPriority(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrDmgMgn(unsigned int arts, unsigned int level) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getArtsDrDmgMgn1,
        _gfbbt::getArtsDrDmgMgn2,
        _gfbbt::getArtsDrDmgMgn3,
        _gfbbt::getArtsDrDmgMgn4,
        _gfbbt::getArtsDrDmgMgn5,
        _gfbbt::getArtsDrDmgMgn6,
    };
    return _gfbbt::getSlot(s_getters, level)(*m_fpArtsDr, arts);
}

unsigned int GfBdatBtl::getArtsDrRecast(unsigned int arts, unsigned int level) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getArtsDrRecast1,
        _gfbbt::getArtsDrRecast2,
        _gfbbt::getArtsDrRecast3,
        _gfbbt::getArtsDrRecast4,
        _gfbbt::getArtsDrRecast5,
        _gfbbt::getArtsDrRecast6,
    };
    return _gfbbt::getSlot(s_getters, level)(*m_fpArtsDr, arts);
}

unsigned int GfBdatBtl::getArtsDrEnhance(unsigned int arts, unsigned int level) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getArtsDrEnhance1,
        _gfbbt::getArtsDrEnhance2,
        _gfbbt::getArtsDrEnhance3,
        _gfbbt::getArtsDrEnhance4,
        _gfbbt::getArtsDrEnhance5,
        _gfbbt::getArtsDrEnhance6,
    };
    return _gfbbt::getSlot(s_getters, level)(*m_fpArtsDr, arts);
}

unsigned int GfBdatBtl::getArtsDrReleaseLv(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getArtsDrReleaseLv1,
        _gfbbt::getArtsDrReleaseLv1,
        _gfbbt::getArtsDrReleaseLv2,
        _gfbbt::getArtsDrReleaseLv3,
        _gfbbt::getArtsDrReleaseLv4,
        _gfbbt::getArtsDrReleaseLv5,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsDrNeedWP(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getArtsDrNeedWP2,
        _gfbbt::getArtsDrNeedWP2,
        _gfbbt::getArtsDrNeedWP2,
        _gfbbt::getArtsDrNeedWP3,
        _gfbbt::getArtsDrNeedWP4,
        _gfbbt::getArtsDrNeedWP5,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpArtsDr, id);
}

unsigned int GfBdatBtl::getArtsBlStart() const {
    return Bdat::getIdTop(m_fpArtsBl->m_fp);
}

unsigned int GfBdatBtl::getArtsBlEnd() const {
    return Bdat::getIdTop(m_fpArtsBl->m_fp) + Bdat::getIdCount(m_fpArtsBl->m_fp);
}

unsigned int GfBdatBtl::getArtsBlName(unsigned int id) const {
    return _gfbbt::getArtsBlName(*m_fpArtsBl, id);
}

const char* GfBdatBtl::getArtsBlDebugName(unsigned int id) const {
    return _gfbbt::getArtsBlDebugName(*m_fpArtsBl, id);
}

unsigned int GfBdatBtl::getArtsBlCaption(unsigned int id) const {
    return _gfbbt::getArtsBlCaption(*m_fpArtsBl, id);
}

unsigned int GfBdatBtl::getArtsBlWpnType(unsigned int id) const {
    return _gfbbt::getArtsBlWpnType(*m_fpArtsBl, id);
}

unsigned int GfBdatBtl::getArtsBlCmnBlType(unsigned int id) const {
    return _gfbbt::getArtsBlCmnBlType(*m_fpArtsBl, id);
}

unsigned int GfBdatBtl::getArtsBlSpLv(unsigned int id) const {
    return _gfbbt::getArtsBlSpLv(*m_fpArtsBl, id);
}

bool GfBdatBtl::isArtsBlFlagcommon(unsigned int id) const {
    return _gfbbt::isArtsBlFlagcommon(*m_fpArtsBl, id);
}

unsigned int GfBdatBtl::getArtsBlEnhance(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getArtsBlEnhance1,
        _gfbbt::getArtsBlEnhance2,
        _gfbbt::getArtsBlEnhance3,
        _gfbbt::getArtsBlEnhance4,
        _gfbbt::getArtsBlEnhance5,
        _gfbbt::getArtsBlEnhance6,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpArtsBl, id);
}

unsigned int GfBdatBtl::getArtsBlSpStart() const {
    return Bdat::getIdTop(m_fpArtsBlSp->m_fp);
}

unsigned int GfBdatBtl::getArtsBlSpEnd() const {
    return Bdat::getIdTop(m_fpArtsBlSp->m_fp) + Bdat::getIdCount(m_fpArtsBlSp->m_fp);
}

unsigned int GfBdatBtl::getArtsBlSpName(unsigned int id) const {
    return _gfbbt::getArtsBlSpName(*m_fpArtsBlSp, id);
}

unsigned int GfBdatBtl::getArtsBlSpCaption(unsigned int id) const {
    return _gfbbt::getArtsBlSpCaption(*m_fpArtsBlSp, id);
}

unsigned int GfBdatBtl::getArtsBlSpWpnType(unsigned int id) const {
    return _gfbbt::getArtsBlSpWpnType(*m_fpArtsBlSp, id);
}

unsigned int GfBdatBtl::getArtsBlSpCmnBlType(unsigned int id) const {
    return _gfbbt::getArtsBlSpCmnBlType(*m_fpArtsBlSp, id);
}

unsigned int GfBdatBtl::getGrowStart() const {
    return Bdat::getIdTop(m_fpGrow->m_fp);
}

unsigned int GfBdatBtl::getGrowEnd() const {
    return Bdat::getIdTop(m_fpGrow->m_fp) + Bdat::getIdCount(m_fpGrow->m_fp);
}

unsigned int GfBdatBtl::getGrowLevelExp(unsigned int id) const {
    return _gfbbt::getGrowLevelExp(*m_fpGrow, id);
}

unsigned int GfBdatBtl::getGrowLevelExp2(unsigned int id) const {
    return _gfbbt::getGrowLevelExp2(*m_fpGrow, id);
}

unsigned int GfBdatBtl::getGrowEnemyExp(unsigned int id) const {
    return _gfbbt::getGrowEnemyExp(*m_fpGrow, id);
}

unsigned int GfBdatBtl::getGrowEnemyWP(unsigned int id) const {
    return _gfbbt::getGrowEnemyWP(*m_fpGrow, id);
}

unsigned int GfBdatBtl::getGrowEnemySP(unsigned int id) const {
    return _gfbbt::getGrowEnemySP(*m_fpGrow, id);
}

unsigned int GfBdatBtl::getGrowEnemyGold(unsigned int id) const {
    return _gfbbt::getGrowEnemyGold(*m_fpGrow, id);
}

unsigned int GfBdatBtl::getGrowGoldDivide(unsigned int level) const {
    return _gfbbt::getGrowGoldDivide(*m_fpGrow, level);
}

unsigned int GfBdatBtl::getWpn_EnRscR(unsigned int id) const {
    return _gfbbt::getWpn_EnRscR(*m_fpWpn_En, id);
}

unsigned int GfBdatBtl::getWpn_EnRscL(unsigned int id) const {
    return _gfbbt::getWpn_EnRscL(*m_fpWpn_En, id);
}

unsigned int GfBdatBtl::getBTL_ClassStart() const {
    return Bdat::getIdTop(m_fpBTL_Class->m_fp);
}

unsigned int GfBdatBtl::getBTL_ClassEnd() const {
    return Bdat::getIdTop(m_fpBTL_Class->m_fp) + Bdat::getIdCount(m_fpBTL_Class->m_fp);
}

unsigned int GfBdatBtl::getBTL_ClassName(unsigned int id) const {
    return _gfbbt::getBTL_ClassName(*m_fpBTL_Class, id);
}

unsigned int GfBdatBtl::getBTL_ClassRole(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getBTL_ClassRole1,
        _gfbbt::getBTL_ClassRole2,
        _gfbbt::getBTL_ClassRole3,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_Class, id);
}

unsigned int GfBdatBtl::getBTL_EnhanceEnhanceEffect(unsigned int id) const {
    return _gfbbt::getBTL_EnhanceEnhanceEffect(*m_fpBTL_Enhance, id);
}

float GfBdatBtl::getBTL_EnhanceParam1(unsigned int id) const {
    return _gfbbt::getBTL_EnhanceParam1(*m_fpBTL_Enhance, id);
}

float GfBdatBtl::getBTL_EnhanceParam2(unsigned int id) const {
    return _gfbbt::getBTL_EnhanceParam2(*m_fpBTL_Enhance, id);
}

unsigned int GfBdatBtl::getBTL_EnhanceCaption(unsigned int id) const {
    return _gfbbt::getBTL_EnhanceCaption(*m_fpBTL_Enhance, id);
}

unsigned int GfBdatBtl::getBTL_EnhanceCaption2(unsigned int id) const {
    return _gfbbt::getBTL_EnhanceCaption2(*m_fpBTL_Enhance, id);
}

unsigned int GfBdatBtl::getBTL_EnhanceEffCategory(unsigned int id) const {
    return _gfbbt::getBTL_EnhanceEffCategory(*m_fpBTL_EnhanceEff, id);
}

bool GfBdatBtl::isBTL_EnhanceEffFlagCondition(unsigned int id) const {
    return _gfbbt::isBTL_EnhanceEffFlagCondition(*m_fpBTL_EnhanceEff, id);
}

unsigned int GfBdatBtl::getBTL_EnhanceEffSortCat(unsigned int id) const {
    return _gfbbt::getBTL_EnhanceEffSortCat(*m_fpBTL_EnhanceEff, id);
}

unsigned int GfBdatBtl::getBTL_Skill_BlStart() const {
    return Bdat::getIdTop(m_fpBTL_Skill_Bl->m_fp);
}

unsigned int GfBdatBtl::getBTL_Skill_BlEnd() const {
    return Bdat::getIdTop(m_fpBTL_Skill_Bl->m_fp) + Bdat::getIdCount(m_fpBTL_Skill_Bl->m_fp);
}

unsigned int GfBdatBtl::getBTL_Skill_BlName(unsigned int id) const {
    return _gfbbt::getBTL_Skill_BlName(*m_fpBTL_Skill_Bl, id);
}

bool GfBdatBtl::isBTL_Skill_BlFlagcommon(unsigned int id) const {
    return _gfbbt::isBTL_Skill_BlFlagcommon(*m_fpBTL_Skill_Bl, id);
}

unsigned int GfBdatBtl::getBTL_Skill_BlTank(unsigned int id) const {
    return _gfbbt::getBTL_Skill_BlTank(*m_fpBTL_Skill_Bl, id);
}

unsigned int GfBdatBtl::getBTL_Skill_BlAttacker(unsigned int id) const {
    return _gfbbt::getBTL_Skill_BlAttacker(*m_fpBTL_Skill_Bl, id);
}

unsigned int GfBdatBtl::getBTL_Skill_BlHealer(unsigned int id) const {
    return _gfbbt::getBTL_Skill_BlHealer(*m_fpBTL_Skill_Bl, id);
}

unsigned int GfBdatBtl::getBTL_Skill_BlEnhance(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getBTL_Skill_BlEnhance1,
        _gfbbt::getBTL_Skill_BlEnhance2,
        _gfbbt::getBTL_Skill_BlEnhance3,
        _gfbbt::getBTL_Skill_BlEnhance4,
        _gfbbt::getBTL_Skill_BlEnhance5,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_Skill_Bl, id);
}

unsigned int GfBdatBtl::getBTL_Skill_DrName(unsigned int id) const {
    return _gfbbt::getBTL_Skill_DrName(*m_fpBTL_Skill_Dr, id);
}

unsigned int GfBdatBtl::getBTL_Skill_DrEnhance(unsigned int id) const {
    return _gfbbt::getBTL_Skill_DrEnhance(*m_fpBTL_Skill_Dr, id);
}

unsigned int GfBdatBtl::getBTL_BuffName(unsigned int id) const {
    return _gfbbt::getBTL_BuffName(*m_fpBTL_Buff, id);
}

unsigned int GfBdatBtl::getBTL_BuffCaption(unsigned int id) const {
    return _gfbbt::getBTL_BuffCaption(*m_fpBTL_Buff, id);
}

unsigned int GfBdatBtl::getBTL_Bl_PersonalityStart() const {
    return Bdat::getIdTop(m_fpBTL_Bl_Personality->m_fp);
}

unsigned int GfBdatBtl::getBTL_Bl_PersonalityEnd() const {
    return Bdat::getIdTop(m_fpBTL_Bl_Personality->m_fp) + Bdat::getIdCount(m_fpBTL_Bl_Personality->m_fp);
}

bool GfBdatBtl::isBTL_Bl_PersonalityFlagcommon(unsigned int id) const {
    return _gfbbt::isBTL_Bl_PersonalityFlagcommon(*m_fpBTL_Bl_Personality, id);
}

unsigned int GfBdatBtl::getBTL_Bl_PersonalityVoiceID(unsigned int id) const {
    return _gfbbt::getBTL_Bl_PersonalityVoiceID(*m_fpBTL_Bl_Personality, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkLinkNum(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkLinkNum(*m_fpBTL_Bl_KizunaLink, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkAppStNum(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkAppStNum(*m_fpBTL_Bl_KizunaLink, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkAppEndNum(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkAppEndNum(*m_fpBTL_Bl_KizunaLink, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkSetStart() const {
    return Bdat::getIdTop(m_fpBTL_Bl_KizunaLinkSet->m_fp);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkSetEnd() const {
    return Bdat::getIdTop(m_fpBTL_Bl_KizunaLinkSet->m_fp) + Bdat::getIdCount(m_fpBTL_Bl_KizunaLinkSet->m_fp);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkSetKizunaLink1(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkSetKizunaLink1(*m_fpBTL_Bl_KizunaLinkSet, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkSetKizunaLink2(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkSetKizunaLink2(*m_fpBTL_Bl_KizunaLinkSet, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkSetLinkChType(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkSetLinkChType(*m_fpBTL_Bl_KizunaLinkSet, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkSetLinkChNum(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkSetLinkChNum(*m_fpBTL_Bl_KizunaLinkSet, id);
}

unsigned int GfBdatBtl::getBTL_Bl_KizunaLinkSetVoiceID(unsigned int id) const {
    return _gfbbt::getBTL_Bl_KizunaLinkSetVoiceID(*m_fpBTL_Bl_KizunaLinkSet, id);
}

unsigned int GfBdatBtl::getBTL_HanaBaseNCondNum(unsigned int id) const {
    return _gfbbt::getBTL_HanaBaseNCondNum(*m_fpBTL_HanaBase, id);
}

unsigned int GfBdatBtl::getBTL_HanaBaseECondNum(unsigned int id) const {
    return _gfbbt::getBTL_HanaBaseECondNum(*m_fpBTL_HanaBase, id);
}

unsigned int GfBdatBtl::getBTL_HanaBaseNArtsNum(unsigned int id) const {
    return _gfbbt::getBTL_HanaBaseNArtsNum(*m_fpBTL_HanaBase, id);
}

unsigned int GfBdatBtl::getBTL_HanaBaseCircuitNum(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getBTL_HanaBaseCircuit1Num,
        _gfbbt::getBTL_HanaBaseCircuit2Num,
        _gfbbt::getBTL_HanaBaseCircuit3Num,
        _gfbbt::getBTL_HanaBaseCircuit4Num,
        _gfbbt::getBTL_HanaBaseCircuit5Num,
        _gfbbt::getBTL_HanaBaseCircuit6Num,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_HanaBase, id);
}

int GfBdatBtl::getBTL_HanaPowerPowerNum(unsigned int rank, unsigned int hana) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getBTL_HanaPowerPowerNum1,
        _gfbbt::getBTL_HanaPowerPowerNum2,
        _gfbbt::getBTL_HanaPowerPowerNum3,
    };
    return _gfbbt::getSlot(s_getters, hana)(*m_fpBTL_HanaPower, rank);
}

int GfBdatBtl::getBTL_HanaPowerEtherNum(unsigned int rank, unsigned int hana) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getBTL_HanaPowerEtherNum1,
        _gfbbt::getBTL_HanaPowerEtherNum2,
        _gfbbt::getBTL_HanaPowerEtherNum3,
    };
    return _gfbbt::getSlot(s_getters, hana)(*m_fpBTL_HanaPower, rank);
}

unsigned int GfBdatBtl::getBTL_HanaChipsetRoleParts(unsigned int id) const {
    return _gfbbt::getBTL_HanaChipsetRoleParts(*m_fpBTL_HanaChipset, id);
}

unsigned int GfBdatBtl::getBTL_HanaChipsetAtrParts(unsigned int id) const {
    return _gfbbt::getBTL_HanaChipsetAtrParts(*m_fpBTL_HanaChipset, id);
}

unsigned int GfBdatBtl::getBTL_HanaChipsetNArtsParts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getBTL_HanaChipsetNArtsParts1,
        _gfbbt::getBTL_HanaChipsetNArtsParts2,
        _gfbbt::getBTL_HanaChipsetNArtsParts3,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_HanaChipset, id);
}

unsigned int GfBdatBtl::getBTL_HanaChipsetNCondParts(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::getBTL_HanaChipsetNCondParts1,
        _gfbbt::getBTL_HanaChipsetNCondParts2,
        _gfbbt::getBTL_HanaChipsetNCondParts3,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_HanaChipset, id);
}

unsigned int GfBdatBtl::getWildcardDatavalueU2(unsigned int id) const {
    return _gfbbt::getWildcardDatavalueU2(*m_fpWildcardData, id);
}

unsigned int GfBdatBtl::getVo_Field_FilterStart() const {
    return Bdat::getIdTop(m_fpVo_Field_Filter->m_fp);
}

unsigned int GfBdatBtl::getVo_Field_FilterEnd() const {
    return Bdat::getIdTop(m_fpVo_Field_Filter->m_fp) + Bdat::getIdCount(m_fpVo_Field_Filter->m_fp);
}

const char* GfBdatBtl::getVo_Field_FilterTargetFile(unsigned int id) const {
    return _gfbbt::getVo_Field_FilterTargetFile(*m_fpVo_Field_Filter, id);
}

unsigned int GfBdatBtl::getVo_Field_FilterCondition(unsigned int id) const {
    return _gfbbt::getVo_Field_FilterCondition(*m_fpVo_Field_Filter, id);
}

const char* GfBdatBtl::getVo_Field_FilterChangeFile(unsigned int id) const {
    return _gfbbt::getVo_Field_FilterChangeFile(*m_fpVo_Field_Filter, id);
}

unsigned int GfBdatBtl::getBTL_DifSettingParamMin(unsigned int id) const {
    return _gfbbt::getBTL_DifSettingParamMin(*m_fpBTL_DifSetting, id);
}

unsigned int GfBdatBtl::getBTL_DifSettingParamMax(unsigned int id) const {
    return _gfbbt::getBTL_DifSettingParamMax(*m_fpBTL_DifSetting, id);
}

unsigned int GfBdatBtl::getBTL_DifSettingInterval(unsigned int id) const {
    return _gfbbt::getBTL_DifSettingInterval(*m_fpBTL_DifSetting, id);
}

unsigned int GfBdatBtl::getBTL_DifSettingConditionOri(unsigned int id) const {
    return _gfbbt::getBTL_DifSettingConditionOri(*m_fpBTL_DifSetting, id);
}

unsigned int GfBdatBtl::getBTL_DifSettingConditionIra(unsigned int id) const {
    return _gfbbt::getBTL_DifSettingConditionIra(*m_fpBTL_DifSetting, id);
}

bool GfBdatBtl::isBTL_DifSettingFlagIra(unsigned int id) const {
    return _gfbbt::isBTL_DifSettingFlagIra(*m_fpBTL_DifSetting, id);
}

unsigned int GfBdatBtl::getBTL_DifSettingDiff(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::fn_71001E11BC,
        _gfbbt::fn_71001E1244,
        _gfbbt::fn_71001E12CC,
        _gfbbt::fn_71001E1354,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_DifSetting, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlStart() const {
    return Bdat::getIdTop(m_fpBTL_ChBtl->m_fp);
}

unsigned int GfBdatBtl::getBTL_ChBtlEnd() const {
    return Bdat::getIdTop(m_fpBTL_ChBtl->m_fp) + Bdat::getIdCount(m_fpBTL_ChBtl->m_fp);
}

unsigned int GfBdatBtl::getBTL_ChBtlName(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlName(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlDifficult(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlDifficult(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlWave(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlWave(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlCaption(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlCaption(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlMapJump(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlMapJump(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlWeather(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlWeather(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlType(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlType(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlNeedDefeat(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlNeedDefeat(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlMaxLevel(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlMaxLevel(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlMaxWpnRank(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlMaxWpnRank(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlWpnRevTable(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlWpnRevTable(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlTimeLimit(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlTimeLimit(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlJoinNumber(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlJoinNumber(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlNeedItem(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlNeedItem(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlCondition(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlCondition(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlConditionCap(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlConditionCap(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlCondition2(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlCondition2(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlConditionCap2(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlConditionCap2(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlHideCondition(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlHideCondition(*m_fpBTL_ChBtl, id);
}

bool GfBdatBtl::isBTL_ChBtlFlagHide(unsigned int id) const {
    return _gfbbt::isBTL_ChBtlFlagHide(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlTresureNeed1(unsigned int id) const {
    return _gfbbt::fn_71001E1574(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlTresureNeed2(unsigned int id) const {
    return _gfbbt::fn_71001E15FC(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlTresureNeed3(unsigned int id) const {
    return _gfbbt::fn_71001E1684(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlClearReward(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlClearReward(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlEvent(unsigned int id) const {
    return _gfbbt::getBTL_ChBtlEvent(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlDriver(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::fn_71001E13DC,
        _gfbbt::fn_71001E1464,
        _gfbbt::fn_71001E14EC,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlTresureNeed(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::fn_71001E1574,
        _gfbbt::fn_71001E15FC,
        _gfbbt::fn_71001E1684,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_ChBtl, id);
}

unsigned int GfBdatBtl::getBTL_ChBtlWpnRevWpnDmg(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        nullptr,
        _gfbbt::fn_71001E170C,
        _gfbbt::fn_71001E1794,
        _gfbbt::fn_71001E181C,
        _gfbbt::fn_71001E18A4,
        _gfbbt::fn_71001E192C,
        _gfbbt::fn_71001E19B4,
        _gfbbt::fn_71001E1A3C,
        _gfbbt::fn_71001E1AC4,
        _gfbbt::fn_71001E1B4C,
        _gfbbt::fn_71001E1BD4,
        _gfbbt::fn_71001E1C5C,
        _gfbbt::fn_71001E1CE4,
        _gfbbt::fn_71001E1D6C,
        _gfbbt::fn_71001E1DF4,
        _gfbbt::fn_71001E1E7C,
        _gfbbt::fn_71001E1F04,
        _gfbbt::fn_71001E1F8C,
        _gfbbt::fn_71001E2014,
        _gfbbt::fn_71001E209C,
        _gfbbt::fn_71001E2124,
        _gfbbt::fn_71001E21AC,
        _gfbbt::fn_71001E2234,
        _gfbbt::fn_71001E22BC,
        _gfbbt::fn_71001E2344,
        _gfbbt::fn_71001E23CC,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
        _gfbbt::fn_71001E2454,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_ChBtlWpnRev, id);
}

unsigned int GfBdatBtl::getBTL_IrGroupRevGroupRev(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbt::fn_71001E24DC,
        _gfbbt::fn_71001E2564,
        _gfbbt::fn_71001E25EC,
    };
    return _gfbbt::getSlot(s_getters, slot)(*m_fpBTL_IrGroupRev, id);
}

}  // namespace gf
