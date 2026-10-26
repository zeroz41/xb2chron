#ifndef GF_GFREQCOMMAND_H
#define GF_GFREQCOMMAND_H

namespace gf { class GF_OBJ_HANDLE; class GfMapjumpInfo; class GfReqParam; enum SAVESLOT : int; }
namespace gf {
// the requests GfReqManager queues (GfReqManager's table comment names them gf::GfReqCommand's): only the ones
// called so far are declared
class GfReqCommand {
public:
    // after a blade's weapon changes: returns the request's handle, -1 when no party driver engages the blade
    static unsigned int reqRebuildPartyWeapon(unsigned int blade);
    // both return the request's handle (GfPlayComResetBlade::update keeps it for GfReqManager::isValid)
    static unsigned int reqChangeBladeWithSetId(unsigned int slot, int setId, bool flag);
    static unsigned int reqChangeBladeWithBladeId(unsigned int slot, unsigned int blade);
    // a wait-event request (GfPlayComWaitEvent::start keeps the handle and waits on GfReqManager::isValid)
    static unsigned int reqWaitEvent(float time, GF_OBJ_HANDLE* handle);
    // a map jump request: returns its handle (GfPlayComMapjump::start keeps it for GfReqManager::isValid)
    static unsigned int reqMapjump(const GfMapjumpInfo& info);
    // returns its handle (GfPlayComIraCampSave::start passes 22 and waits on GfReqManager::isValid)
    static unsigned int reqSoloParty(unsigned int party);
    // the fld script plugin's startScript passes (0, name, true) and ignores the returned handle
    static unsigned int reqStartScript(unsigned int id, const char* name, bool start);
    // a save request: returns its handle (GfMenuObjBladeCreate::seqSave passes slot 22 and waits on
    // GfReqManager::isValid)
    static unsigned int reqSave(SAVESLOT slot);
    // GfManager::finalize's: the game framework's teardown; returns the request's handle (then stops the queue)
    static unsigned int reqDestroyGf();
    static unsigned int reqSaveOption();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits between reqSave
    // and reqSaveOption in the unit and queues the same request as reqSave. What it does: queues the save request
    // for the slot with the request's second flag set (reqSave leaves both clear); GfMenuObjBalloon::seqSave calls it.
    static unsigned int fn_7100554234(SAVESLOT slot);
    // Placeholder name: new in 3.0.1. A member because it sits between reqChangeParty and reqChangeBladeWithSetId
    // and queues execChangeParty. What it does: queues a party change built from GfGameParty::getCurrentPartyInfo,
    // passed through fn_710055509C first.
    static unsigned int fn_710055570C();

    // Placeholder name: 1.0.0 has the same function after execMapjump, unnamed too (fn_71005BE790). A member
    // because execChangeBladeWithSetId tail-calls it with its request's slot and set id. What it does: changes the
    // slot's blade to the set's.
    static void fn_71005573CC(unsigned int slot, int setId);

    static void execSave(const GfReqParam* param);
    static void execSaveOption(const GfReqParam* param);
    static void execWaitEvent(const GfReqParam* param);
    static void execRebuildPartyWeapon(const GfReqParam* param);
    static void execChangeParty(const GfReqParam* param);
    static void execChangeBladeWithSetId(const GfReqParam* param);
    static void execChangeBladeWithBladeId(const GfReqParam* param);
    static void execMapjump(const GfReqParam* param);
    static void execDestroyGf(const GfReqParam* param);
    static void execStartScript(const GfReqParam* param);
};
}  // namespace gf

#endif
