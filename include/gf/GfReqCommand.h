#ifndef GF_GFREQCOMMAND_H
#define GF_GFREQCOMMAND_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf {
// the requests GfReqManager queues (GfReqManager's table comment names them gf::GfReqCommand's): only the ones
// called so far are declared
class GfReqCommand {
public:
    static void reqRebuildPartyWeapon(unsigned int blade);  // after a blade's weapon changes
    static void reqChangeBladeWithSetId(unsigned int slot, int setId, bool flag);
    // a wait-event request (GfPlayComWaitEvent::start keeps the handle and waits on GfReqManager::isValid)
    static unsigned int reqWaitEvent(float time, GF_OBJ_HANDLE* handle);
    static void reqDestroyGf();  // GfManager::finalize's: the game framework's teardown
};
}  // namespace gf

#endif
