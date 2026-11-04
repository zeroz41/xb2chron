#ifndef GF_GFDATANPC_H
#define GF_GFDATANPC_H

namespace gf {
// the NPCs' data, by their row id (functions, by its symbols)
class GfDataNpc {
public:
    static const char* getName(unsigned int npc);
    // the message table and row of the NPC's name
    static bool getName(unsigned char*& bdat, unsigned int& id, unsigned int npc);
    static const char* getModelName(unsigned int npc);
    // the BDAT file of the NPC's resources (GfObjFactory::createGmkNpc passes its row's "NpcID")
    static unsigned char* getRscBdatFp(int npc);
    static const char* getMotionName(unsigned int npc);
    static const char* getEffectName(unsigned int npc);
    static bool isNeedResourceEvent(unsigned int npc);
    static int getOffsetID(unsigned int npc);  // its menu offset id
    static bool getExtraParts(unsigned int npc, unsigned int part);
    static unsigned int getFootStep(unsigned int npc);
    static unsigned int getFootStepEffect(unsigned int npc);
    static unsigned int getEyeRotControl(unsigned int npc);
    static unsigned int getRace(unsigned int npc);
    static unsigned int getGender(unsigned int npc);
    static float getScale(unsigned int npc);
    static unsigned int getCollisionId(unsigned int npc);
    static const char* getAddMotionName(unsigned int npc);
    // 2.0.0's symbols name it. What it does: false for an id up to 2000, else whether
    // GfBdatRsc::getRscNpcListEvtRetarget(id) is nonzero.
    static bool isEventRetarget(unsigned int id);
    // 2.0.0's symbols name it. What it does: sets local flag (type 1) id, moved as in GfDataNpc::isTalkBonusFlag, to
    // value (GfGameFlag::setLocal(1, id, value)). Caller: GfComBehaviorNpc::BdatInfo:: setTalkBonusFlag, with
    // GfDataNpc::isTalkBonusFlag's id and 1.
    static void setTalkBonusFlag(unsigned int id, unsigned int value);
    // 2.0.0's symbols name it. What it does: whether local flag (type 1) id is set, an id above 43877 moved up by 11651
    // first (GfGameFlag::getLocal(1, id)). Caller: GfComBehaviorNpc::BdatInfo:: isIconTalkBonus, with its talk event's
    // row in BDAT sheet 0xeb + 41878.
    static bool isTalkBonusFlag(unsigned int id);
    // 2.0.0's symbols name it. What it does: false for ids below 2001; else sets bdat to GfDataBdat::getFP(0x1C3) and
    // id to GfBdatRsc::getRscNpcListJob(blade) (the PtrSingleton<GfBdatRsc> instance) and returns whether that id is
    // nonzero. GfMenuObjTargetInfo::openOther passes a type-6 object's BDAT id (GfObjAcc::getNpcRscId) and shows the
    // text at bdat/id as the other's shop name.
    static bool getJobMsg(unsigned char*& bdat, unsigned int& id, unsigned int blade);
    // 2.0.0's symbols name it. What it does: 0 for an id up to 2000; else RSC_NpcList's message id for the row
    // (GfBdatRsc): getRscNpcListMSGID2 when condition getRscNpcListCondition1 holds (GfGameCond::isGameCond), else
    // getRscNpcListMSGID3 when condition getRscNpcListCondition2 holds, else getRscNpcListMSGID. GfDataNpc::getPlaceMsg
    // calls it.
    static unsigned int getPlaceMsgId(unsigned int id);
    // 2.0.0's symbols name it. What it does: false for ids below 2001; else bdat = GfDataBdat::getFP(435) and id =
    // GfDataNpc::getPlaceMsgId(rsc), true when that id is nonzero. Caller: GfMenuObjHitonowa::dispStatus.
    static bool getPlaceMsg(unsigned char*& bdat, unsigned int& id, unsigned int rsc);
    // a GfBdatRsc caption: bdat = GfDataBdat::getFP(452), id = GfBdatRsc::getRscNpcListresult(rsc); false for rows up to
    // 2000 or no caption (GfMenuObjHitonowa::dispResult)
    static bool getResultMsg(unsigned char*& bdat, unsigned int& id, unsigned int rsc);
    // 2.0.0's symbols name it. What it does: 0 for an id up to 2000, else GfBdatRsc::getRscNpcListHitonowaFlag(id)
    // (GfDataNpc::setHitonowaMeetsFlag records that value - 0xED02). Callers:
    // GfMenuCharDataAdapter::update_IRA_NpcFaceIcon (an NPC object's id; shows the value - 0xED03),
    // gf_menu_obj_hitonowa.
    static unsigned int getHitonowaFlag2Index(unsigned int id);
    // 2.0.0's symbols name it. What it does: 0 for an id up to 2000, else GfBdatRsc::getRscNpcListNpcMeetFlag(id).
    // Caller: GfMenuManager::requestNpcEntry (before GfDataNpc::isHitonowaMeetsFlag on the same id).
    static unsigned int getHitonowaMeetsFlag1Index(unsigned int id);
    // 2.0.0's symbols name it. What they do: GfDataNpc::setHitonowaFlag, for an id above 2000 with a
    // GfBdatRsc::getRscNpcListHitonowaFlag value v, sets local flag v (type 2) to value, calls
    // GfDataHitonowa::setHitonowaEntry, raises local flag 652 (type 4) to GfDataHitonowa::getFlagLevel's result and,
    // when the value changed, calls GfEvent::callHitonowaChanged (caller: event::UIManager::openHitonowaUI).
    // GfDataHitonowa::setHitonowaEntry, for such an id and mode 0..3, records v - 0xED02 in the first free one of the
    // 256 type-8 local flags from 0x10C4 (mode 0) / 0x11C5 (1, 3) / 0x12C6 (2) unless already there (modes 0 and 1 only
    // when GfDataNpc::isHitonowaMeetsFlag answers true; GfDataNpc::setHitonowaMeetsFlag passes 0).
    // GfDataHitonowa::getFlagLevel: 0..6 by how many hitonowa entries GfDataHitonowa::getCompleteNum counts set,
    // against GfBdatBtl's wildcard values 76..80 and 95.
    static void setHitonowaFlag(unsigned int id, unsigned int value);
    // 2.0.0's symbols name it. What it does: 0 for ids below 2001; else the game flag number
    // GfBdatRsc::getRscNpcListHitonowaFlag(id) gives (the PtrSingleton<GfBdatRsc> instance) and, when that is nonzero,
    // the local game flag GfGameFlag::getLocal(2, flag). GfMenuGfObjAdapter::update_IRA_NpcHitonowaIcon passes a type-6
    // object's BDAT id (GfObjAcc::getNpcRscId) and switches on 0..3.
    static unsigned int getHitonowaFlag(unsigned int id);
    // 2.0.0's symbols name it. What it does: for an id above 2000 with a GfBdatRsc::getRscNpcListNpcMeetFlag flag, sets
    // that local flag (type 1) to the bool; when the flag changed and getRscNpcListHitonowaFlag answers nonzero,
    // records that value - 0xED02 in the first free one of the 256 type-8 local flags from 0x10C4 (unless already
    // there). Caller: setNpcMeet (id, true).
    static void setHitonowaMeetsFlag(unsigned int id, bool set);
    // 2.0.0's symbols name it. What it does: for an id above 2000, looks the id up with
    // GfBdatRsc::getRscNpcListNpcMeetFlag and answers whether that local flag (type 1) is set; false otherwise.
    // Callers: the fld plugin's setNpcMeet (before and after GfDataNpc::setHitonowaMeetsFlag),
    // GfMenuManager::requestNpcEntry.
    static bool isHitonowaMeetsFlag(unsigned int id);
    // 2.0.0's symbols name it. What it does: for an id above 2000 reads local flag (type 2)
    // GfBdatRsc::getRscNpcListHitonowaFlag(id) and answers whether it is 1 or 3; false otherwise.
    static bool isDispHitonowa(unsigned int id);
    // 2.0.0's symbols name it. What it does: sets local flag (type 1) 2160 + GfBdatRsc::getRscNpcListNpcMeetFlag(id)
    // (2160 alone for an id up to 2000) to value.
    static void setHitonowaNewFlag(unsigned int id, bool value);
    // 2.0.0's symbols name it. What it does: whether local flag (type 1) 2160 + GfBdatRsc::getRscNpcListNpcMeetFlag(id)
    // is set (2160 alone for an id up to 2000); GfDataNpc::setHitonowaNewFlag sets it.
    static bool isHitonowaNewFlag(unsigned int id);
};
}  // namespace gf

#endif
