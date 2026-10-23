#ifndef GF_GFREQCOMMAND_H
#define GF_GFREQCOMMAND_H

namespace gf {
// the requests GfReqManager queues (GfReqManager's table comment names them gf::GfReqCommand's): only the ones
// called so far are declared
class GfReqCommand {
public:
    static void reqChangeBladeWithSetId(unsigned int slot, int setId, bool flag);
    static void reqDestroyGf();  // GfManager::finalize's: the game framework's teardown
};
}  // namespace gf

#endif
