#ifndef GF_GFREQCOMMAND_H
#define GF_GFREQCOMMAND_H

namespace gf { class GF_OBJ_HANDLE; class GfMapjumpInfo; }
namespace gf {
// the requests GfReqManager queues (GfReqManager's table comment names them gf::GfReqCommand's): only the ones
// called so far are declared
class GfReqCommand {
public:
    static void reqRebuildPartyWeapon(unsigned int blade);  // after a blade's weapon changes
    // both return the request's handle (GfPlayComResetBlade::update keeps it for GfReqManager::isValid)
    static unsigned int reqChangeBladeWithSetId(unsigned int slot, int setId, bool flag);
    static unsigned int reqChangeBladeWithBladeId(unsigned int slot, unsigned int blade);
    // a wait-event request (GfPlayComWaitEvent::start keeps the handle and waits on GfReqManager::isValid)
    static unsigned int reqWaitEvent(float time, GF_OBJ_HANDLE* handle);
    // a map jump request: returns its handle (GfPlayComMapjump::start keeps it for GfReqManager::isValid)
    static unsigned int reqMapjump(const GfMapjumpInfo& info);
    // returns its handle (GfPlayComIraCampSave::start passes 22 and waits on GfReqManager::isValid)
    static unsigned int reqSoloParty(unsigned int party);
    // the fld script plugin's startScript passes (0, name, true); the name is the symbol's, the result (if any) is
    // ignored by its caller
    static void reqStartScript(unsigned int, const char* name, bool);
    static void reqDestroyGf();  // GfManager::finalize's: the game framework's teardown
};
}  // namespace gf

#endif
