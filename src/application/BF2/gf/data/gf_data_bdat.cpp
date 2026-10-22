#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfDataBdat.h"
#include "classes/gf/GfBdatQuest.h"
#include "classes/gf/GfBdatBlade.h"
#include "classes/gf/GfBdatItem.h"
#include "classes/gf/GfBdatCond.h"
#include "classes/gf/GfBdatMaplist.h"
#include "classes/gf/GfBdatChrDr.h"
#include "classes/gf/GfBdatChrBl.h"
#include "classes/gf/GfBdatBgm.h"
#include "classes/gf/GfBdatChrEnArrange.h"
#include "classes/gf/GfBdatChrEnParam.h"
#include "classes/gf/GfBdatRsc.h"
#include "classes/gf/GfBdatBtl.h"
#include "classes/gf/GfBdatMsg.h"
#include "classes/gf/GfBdatLookAt.h"
#include "classes/gf/GfBdatShop.h"
#include "classes/gf/GfBdatUniqueMotion.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfInfo.h"
#include "classes/fw/BdatManager.h"
#include "mm/mtl/FixStr.h"

namespace gf {
namespace _gfbdat {
const char* s_aszGfBdatName[481] = {
    "BTL_Ai",
    "BTL_Arts_Dr",
    "BTL_Arts_Bl",
    "BTL_Arts_Bl_Cam",
    "BTL_Arts_BlSp",
    "BTL_Arts_BlSpVo",
    "BTL_Arts_En",
    "BTL_ArtsDirection",
    "BTL_Aura",
    "BTL_BallBreak",
    "BTL_Bl_KizunaBase",
    "BTL_Bl_KizunaUpDown",
    "BTL_Bl_KizunaLinkSet",
    "BTL_Bl_KizunaLink",
    "BTL_Bl_Personality",
    "BTL_Bl_TrustUp",
    "BTL_BtnChallenge",
    "BTL_Buff",
    "BTL_Bullet",
    "BTL_BulletEffect",
    "BTL_ChainAttackCam",
    "BTL_ChainAttackFull",
    "BTL_ChainAttackStart",
    "BTL_Circle",
    "BTL_Class",
    "BTL_CmnBl_Capacity",
    "BTL_CmnBl_Power",
    "BTL_CmnBl_NewBlArts",
    "BTL_CmnBl_StatusType",
    "BTL_CmnBl_Armor",
    "BTL_Condition",
    "BTL_DifSetting",
    "BTL_Dr_IdeaUp",
    "BTL_Dr_IdeaUpType",
    "BTL_Drop_Heal",
    "BTL_ElementalCombo",
    "BTL_ElementalEffect",
    "BTL_EnAwake",
    "BTL_EnDropItem",
    "BTL_EnDropQuest",
    "BTL_EnBook",
    "BTL_EndEvent",
    "BTL_NamedList",
    "BTL_NamedListIra",
    "BTL_Enhance",
    "BTL_EnhanceEff",
    "BTL_FightCombo",
    "BTL_Grow",
    "BTL_HitCameraParam",
    "BTL_HitDirection",
    "BTL_HitEffect",
    "BTL_Kizuna",
    "BTL_Lv_Rev",
    "BTL_MapRev",
    "BTL_SpSkill",
    "BTL_PartyGauge",
    "BTL_PouchBuff",
    "BTL_PouchBuffSet",
    "BTL_Reaction",
    "BTL_SE",
    "BTL_SpBtl",
    "BTL_SpBtlPos",
    "BTL_Skill_Dr",
    "BTL_Skill_Bl",
    "BTL_SpArtsRecast",
    "BTL_Summon",
    "BTL_SystemBalance",
    "BTL_UniteCombo",
    "BTL_UCDirect",
    "BTL_Wpn_En",
    "BTL_TestSetting",
    "BTL_HanaBase",
    "BTL_HanaPower",
    "BTL_HanaChipset",
    "BTL_ChBtlRewardSet",
    "BTL_ChBtlRewardItem",
    "BTL_ChBtlWpnRev",
    "BTL_ChBtl",
    "BTL_ChBtlScore",
    "BTL_IrGroupRev",
    "ITM_HanaRole",
    "ITM_HanaAtr",
    "ITM_HanaArtsEnh",
    "ITM_HanaNArtsSet",
    "ITM_HanaAssist",
    "Vo_Battle_Driver",
    "Vo_Battle_Blade",
    "Vo_Battle_Enemy",
    "Vo_WinSp",
    "Vo_WinSpIra",
    "Vo_Filter",
    "Vo_Group",
    "Vo_Field_Filter",
    "FLD_maplist",
    "FLD_TimeInfo",
    "FLD_WeatherInfo",
    "FLD_ConditionScenario",
    "FLD_ConditionFlag",
    "FLD_ConditionList",
    "FLD_ConditionQuest",
    "FLD_ConditionEnv",
    "FLD_ConditionLevel",
    "FLD_ConditionPT",
    "FLD_ConditionItem",
    "FLD_ConditionIdea",
    "FLD_ConditionAchievement",
    "FLD_ConditionFieldSkiiLevel",
    "FLD_ConditionMapGimmick",
    "FLD_ConditionNamed",
    "FLD_DMGFloor",
    "FLD_ENActMove",
    "FLD_FieldSkillList",
    "FLD_FieldSkillRandom",
    "FLD_FieldSkillSetting",
    "FLD_LODList",
    "FLD_BtnChallenge",
    "FLD_SalvageClimbLotTable",
    "FLD_SalvageConfig",
    "FLD_SalvageEvent",
    "FLD_SalvageItemSet",
    "FLD_SalvageEnemySet",
    "FLD_SalvageTable",
    "FLD_SalvageWeatherTable",
    "FLD_wildcardData",
    "FLD_MercenariesConfig",
    "FLD_MercenariesNPC",
    "FLD_MercenariesMission",
    "FLD_DevelopmentLevel",
    "FLD_OwnerBonus",
    "FLD_OwnerBonusParam",
    "FLD_IdeaTable",
    "FLD_VoiceTable",
    "FLD_VoiceTableBlade",
    "FLD_VoiceTableRare",
    "FLD_VoiceTableCommon",
    "FLD_actorSE",
    "CHR_Dr",
    "CHR_Ir",
    "CHR_Bl",
    "CHR_EnArrange",
    "CHR_EnParam",
    "CHR_EnParamTable",
    "CHR_EnParam_Rev",
    "CHR_EnRstDebuff_Rev",
    "CHR_DriverParam",
    "IRA_Party",
    "ITM_PcWpn",
    "ITM_CollectionList",
    "ITM_TresureList",
    "ITM_PcWpnChip",
    "ITM_PcWpnType",
    "ITM_PcEquip",
    "ITM_Orb",
    "ITM_OrbRecipe",
    "ITM_OrbEquip",
    "BTL_HealPot",
    "ITM_PreciousList",
    "ITM_PreciousListIra",
    "ITM_InfoList",
    "ITM_EventList",
    "ITM_CrystalList",
    "ITM_SalvageList",
    "ITM_BoosterList",
    "ITM_FavoriteList",
    "ITM_PcWpnIr",
    "RSC_En",
    "RSC_EnGenus",
    "RSC_EnUnd",
    "RSC_NpcList",
    "RSC_NpcWpn",
    "RSC_MobList",
    "RSC_MapObjList",
    "RSC_TboxList",
    "RSC_PcWpn",
    "RSC_PcWpnMount",
    "RSC_EnWpn",
    "RSC_BgmList",
    "RSC_BgmCondition",
    "RSC_TypeWpn",
    "COL_CharList",
    "SYS_PcFldKeyList",
    "SYS_PcBtlKeyList",
    "SYS_MapJumpList",
    "SYS_MapJumpEvList",
    "SYS_BasicFormation",
    "SYS_BladeOffset",
    "FLD_QuestList",
    "FLD_QuestListNormal",
    "FLD_QuestListMini",
    "FLD_QuestListMercenaries",
    "FLD_QuestListAchievement",
    "FLD_QuestListBlade",
    "FLD_QuestListNormalIra",
    "FLD_QuestListIra",
    "FLD_QuestTask",
    "FLD_QuestTaskNormal",
    "FLD_QuestTaskMini",
    "FLD_QuestTaskMercenaries",
    "FLD_QuestTaskAchievement",
    "FLD_QuestTaskBlade",
    "FLD_QuestTaskNormalIra",
    "FLD_QuestTaskIra",
    "FLD_QuestBattle",
    "FLD_RequestItemSet",
    "FLD_QuestCollect",
    "FLD_QuestUse",
    "FLD_QuestReach",
    "FLD_QuestTalk",
    "FLD_QuestTalkDummyGroup",
    "FLD_QuestGimmick",
    "FLD_QuestFieldSkillCount",
    "FLD_RequestBlade",
    "FLD_QuestCondition",
    "FLD_QuestHints",
    "FLD_QuestReward",
    "FLD_QuestRewardRandom",
    "FLD_QuestEvent",
    "FLD_EnemyGroup",
    "FLD_Achievement",
    "FLD_AchievementSet",
    "FLD_AchievementList",
    "FLD_AddItem",
    "BLD_Idea",
    "BLD_IdeaTable",
    "BLD_BladeTable",
    "BLD_BladeList",
    "BLD_CommonList",
    "BLD_NameList",
    "BLD_BladeModelList",
    "BLD_CreateConfig",
    "BLD_RareList",
    "BLD_ReleaceReward",
    "EVT_listBf",
    "EVT_listQst01",
    "EVT_listFev01",
    "EVT_listTlk01",
    "EVT_listBl",
    "MNU_ShopList",
    "MNU_ShopNormal",
    "MNU_ShopInn",
    "MNU_ShopChange",
    "MNU_ShopChangeNopon",
    "MNU_ShopChangeTask",
    "MNU_ShopCategoryName",
    "MNU_SpecialShop",
    "menu_ms",
    "MNU_CmnWindow",
    "MNU_CmnJog",
    "MNU_BtnChallenge2",
    "MNU_BtnChallengeSeq",
    "MNU_ChallengeParam",
    "MNU_ChallengeResult",
    "MNU_ModelView",
    "MNU_EventTheater",
    "MNU_EventTheater_ira",
    "MNU_Tutorial",
    "MNU_Tutorial_Ira",
    "MNU_Tutorial_Chbtl",
    "MNU_Tutorial_Tips",
    "MNU_OptionCamera",
    "MNU_OptionSound",
    "MNU_OptionDisp",
    "MNU_OptionGame",
    "MNU_OptionGameDlc",
    "MNU_OptionGameIra",
    "MNU_OptionGameDif",
    "MNU_DlcGift",
    "MNU_AnnouncePage",
    "MNU_AnnouncePageIra",
    "MNU_AnnounceSchedule",
    "MNU_DriverInfo",
    "MNU_NpcChange",
    "MNU_NpcFace",
    "menu_cmnwindow",
    "menu_operation_info_ms",
    "menu_jog_ms",
    "menu_attr_ms",
    "menu_role_name_ms",
    "menu_tag_ms",
    "menu_main_contents_ms",
    "menu_operation_guide",
    "menu_sub_contents_ms",
    "menu_rarity",
    "menu_collectionitemtype",
    "menu_shop_category",
    "menu_filter_category",
    "menu_sort_category",
    "menu_error_info_ms",
    "menu_enemy_reaction",
    "menu_arts_type",
    "menu_range_type",
    "menu_chapter_end_ms",
    "menu_assistcore_slot_ms",
    "menu_st_correctionvalue",
    "menu_ideacollar_ms",
    "menu_class",
    "menu_st_congeniality",
    "menu_quest_cate_ms",
    "menu_tutorial",
    "menu_tutorial_chbtl",
    "menu_ev_theater_ms",
    "menu_zone_telop_ms",
    "mnu_map_level_name_ms",
    "menu_favorite_category",
    "menu_enemy_category",
    "menu_popup_title_ms",
    "menu_popup_ms",
    "menu_popup_system_ms",
    "menu_trust_rank_ms",
    "menu_option_name_ms",
    "menu_option_cap_ms",
    "menu_cast_name",
    "menu_ilust_name",
    "menu_dlc_gift",
    "menu_ang_info",
    "menu_announce",
    "menu_camp_ms",
    "MNU_Msg_Mercenaries",
    "MNU_Msg_Attr",
    "MNU_Msg_Reaction",
    "MNU_Msg_ReactionAll",
    "MNU_Msg_Weapon_Type",
    "MNU_Msg_Gender",
    "MNU_Msg_Race",
    "MNU_Msg_ItemType",
    "MNU_Msg_CollectionItem",
    "MNU_Msg_OperationGuide",
    "MNU_Msg_Rarelity",
    "MNU_Msg_SubContents",
    "MNU_Msg_ErrorInfo",
    "MNU_Msg_ItemFilter",
    "MNU_Msg_ItemListFilter",
    "MNU_Msg_PouchFilter",
    "MNU_Msg_PouchFilter_Ira",
    "MNU_Msg_ItemSort",
    "MNU_Msg_ArtsType",
    "MNU_Msg_ArtsTypeIndex",
    "MNU_Msg_ArtsRange",
    "MNU_MsgChapterEnd",
    "MNU_MsgFavoriteType",
    "MNU_MsgQListTab",
    "MNU_MsgEvthCast",
    "MNU_MsgEvthChapter",
    "MNU_MsgEnbFamily",
    "MNU_MsgDrStatusIndex",
    "MNU_MsgBlStatusIndex",
    "MNU_MsgPouch",
    "MNU_MsgPopupTitle",
    "MNU_MsgPopup",
    "MNU_MsgPopupSystem",
    "MNU_MsgTrustRank",
    "MNU_MsgMapFilter",
    "MNU_MsgMapFilterIra",
    "MNU_MsgDamageBuff",
    "MNU_MsgKeyAchieve",
    "MNU_MsgUniteBonus",
    "MNU_Msg_MenuDescription",
    "MNU_MsgSelect",
    "MNU_MsgSelectTitle",
    "MNU_MsgGiftItem",
    "MNU_MsgGiftFilter",
    "MNU_Msg_OptList",
    "MNU_Msg_ANGInfo",
    "MNU_Msg_ANGInfo2",
    "MNU_MsgEvthEx",
    "MNU_SortTable",
    "MNU_SortEnhance",
    "MNU_SortBuff",
    "MNU_SortRole",
    "MNU_SortFieldSkill",
    "MNU_BlCoolTimeLv",
    "MNU_FSMenu",
    "MNU_IconList",
    "MNU_DrImageID",
    "MNU_BlImageID",
    "MNU_DamageValue",
    "MNU_WorldMap",
    "MNU_WorldMapCond",
    "MNU_MapInfo",
    "MNU_MapGroup",
    "MNU_HanaSet",
    "MNU_HanaMode",
    "MNU_Condition",
    "MNU_MainOrder",
    "MNU_MainOrder_ira",
    "MNU_CharDriverOrder",
    "MNU_CharDriverOrder_ira",
    "MNU_CharBladeOrder",
    "MNU_CharBladeOrder_ira",
    "MNU_CharHanaOrder",
    "MNU_KeyOrder",
    "MNU_SoundSe",
    "MNU_SoundBgm",
    "MNU_BladeCreate",
    "CAM_Params",
    "CAM_MaxLevel",
    "bld_bladename",
    "bld_mercename",
    "btl_arts_bl_ms",
    "btl_arts_blsp_ms",
    "btl_arts_dr_ms",
    "btl_arts_dr_cap",
    "btl_arts_en_ms",
    "btl_aura_cap",
    "btl_aura_ms",
    "btl_buff_cap",
    "btl_buff_ms",
    "btl_class_ms",
    "btl_elementalcombo_ms",
    "btl_elementaleffect_ms",
    "btl_engenus_ms",
    "btl_enhance_cap",
    "btl_fightcombo_ms",
    "btl_skill_dr_name",
    "btl_skill_bl_name",
    "btl_unitecombo_ms",
    "btl_pouchbuff_ms",
    "btl_chbtl_ms",
    "itm_hana_role_ms",
    "itm_hana_narts_set_ms",
    "itm_hana_atr_ms",
    "itm_hana_assist_ms",
    "itm_hana_arts_enh_ms",
    "chr_bl_ms",
    "chr_dr_ms",
    "cmm_homuri_name_ms",
    "fld_achievementtxt",
    "fld_actionwindow",
    "fld_developmentname",
    "fld_enemyname",
    "fld_fieldskillplace",
    "fld_fieldskilltxt",
    "fld_gmkname",
    "fld_helpms",
    "fld_kizunatalktitle",
    "fld_landmark",
    "fld_mapinfo",
    "fld_npcname",
    "fld_quest",
    "fld_quest_normal",
    "fld_quest_mini",
    "fld_quest_blade",
    "fld_quest_achievement",
    "fld_quest_mercenaries",
    "fld_randomtalk",
    "fld_salvagepoint",
    "fld_shopname",
    "fld_shopchange",
    "fld_unitname",
    "fld_wavename",
    "fld_camppoint",
    "fld_npcjobname",
    "fld_npcresult",
    "itm_booster",
    "itm_collection",
    "itm_crystal",
    "itm_evt",
    "itm_favorite",
    "itm_info",
    "itm_orb",
    "itm_pcequip",
    "itm_pcwpn_ms",
    "itm_pcwpnchip_ms",
    "itm_pcwpntype_ms",
    "itm_precious",
    "itm_salvage",
    "itm_tresure",
    "FLD_LookSetDr",
    "FLD_LookSetBl",
    "FLD_LookSetEn",
    "FLD_LookSetNpc",
    "FLD_LookSetMob",
    "FLD_LookType000",
    "FLD_LookType001",
    "FLD_LookType002",
    "FLD_UniquePreset",
    "FLD_UniqueTable",
    "Fx_Act_Surface_Table",
    "Fx_FileName",
    "Fx_Surface_Chara_Table",
    "FLD_CollectionTable",
};
}  // namespace _gfbdat

GfDataBdat::GfDataBdat(const GfSetupParam& param) : m_reloadCount(0), m_initialized(false) {
    initialize(param);
}

GfDataBdat::~GfDataBdat() {}

void GfDataBdat::build(const GfSetupParam& param) {
#line 573
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfDataBdat(param);
}

void GfDataBdat::initialize(const GfSetupParam& param) {
    GfEvent::addEventCallback(this);
    loadBdat("lookat", 15);
    while (isBdatLoading(15)) {
        GfSleep(1);
    }
    setupBdatInfo();
#line 617
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatQuest(param));
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatBlade());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatItem());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatCond());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatMaplist());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatChrDr());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatChrBl());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatBgm());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatChrEnArrange());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatChrEnParam());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatRsc());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatBtl());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatMsg());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatLookAt());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatShop());
    m_bdats.push_back(new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfBdatUniqueMotion());
    m_initialized = true;
}

void GfDataBdat::destroy() {
    GfDataBdat* data = get();
    data->finalize();
    delete data;
}

void GfDataBdat::finalize() {
    for (IDataBdat** it = m_bdats.begin(); it != m_bdats.end(); ++it) {
        if (*it != nullptr) {
            delete *it;
            *it = nullptr;
        }
    }
    releaseBdatInfo();
    destroyBdat(15);
    GfEvent::removeEventCallback(this);
    m_initialized = false;
}

bool GfDataBdat::isInitialized() {
    GfDataBdat* data = get();
    if (data == nullptr) {
        return false;
    }
    return data->m_initialized;
}

bool GfDataBdat::loadBdat(const char* name, unsigned int slot) {
    mm::mtl::FixStr<64> path;
    path.format("%s.bdat", name);
    return fw::BdatManager::loadBdat(slot, getAllocator(ALLOCATOR(4))->getMemHandle(), path.m_str);
}

bool GfDataBdat::isBdatLoading(unsigned int slot) const {
    return !fw::BdatManager::isEnableBdat(slot);
}

void GfDataBdat::setupBdatInfo() {
    GfDataBdat* data = get();
    for (int i = 0; i < 481; i++) {
        data->m_fp[i] = nullptr;
    }
    for (int i = 0; i < 481; i++) {
        data->m_fp[i] = fw::BdatManager::getFp(_gfbdat::s_aszGfBdatName[i]);
    }
    data->m_reloadCount++;
    for (IDataBdat** it = data->m_bdats.begin(); it != data->m_bdats.end(); ++it) {
        (*it)->bdatRefresh();
    }
}

void GfDataBdat::releaseBdatInfo() {
    GfDataBdat* data = get();
    for (int i = 0; i < 481; i++) {
        data->m_fp[i] = nullptr;
    }
}

void GfDataBdat::destroyBdat(unsigned int slot) {
    fw::BdatManager::unregistBdat(slot);
}

unsigned char* GfDataBdat::getFP(unsigned int id) {
    if (id < 481) {
        return get()->m_fp[id];
    }
    return nullptr;
}

// 1.0.0 calls every table class's bdatRefresh here when the tables are reloaded (type 1); 3.0.1's does nothing
void GfDataBdat::gevReloadBdat(gf::RELOAD_BDAT type, unsigned int id) {}

unsigned int GfDataBdat::getReloadCount() {
    return get()->m_reloadCount;
}

}  // namespace gf
