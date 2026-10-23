#ifndef CLASSES_GF_GFMENUOBJCHAINICON_H
#define CLASSES_GF_GFMENUOBJCHAINICON_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B60D18
class GfMenuObjChainIcon : public ::gf::GfMenuObject {
public:
    class ChainIconInfo;
    class ListListener;
    // what open shows the icon over
    struct OpenParam {
        GF_OBJ_HANDLE* m_obj;  // a driver (open shows nothing for other objects); the name is not the original's
    };
    GfMenuObjChainIcon(unsigned int handle);
    virtual ~GfMenuObjChainIcon();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // a LAY_chain_icon_root copy over the object, its handle (0 for none); the oldest one closes past 32
    static unsigned int open(const OpenParam& param);
    static void close(unsigned int handle);  // fades that copy out (event 0x22)
};
}  // namespace gf

#endif
