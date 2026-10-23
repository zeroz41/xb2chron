#ifndef CLASSES_GMK_GMKGOBEVENTLISTENER_H
#define CLASSES_GMK_GMKGOBEVENTLISTENER_H

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6BE80
class GmkGobEventListener {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    virtual ~GmkGobEventListener();  // slot 1
    // how many gimmick lists share it: each list's constructor adds one, TGmkList's destructor releases one and
    // deletes it at none (the name is not the original's)
    int m_refCount;
};
}  // namespace gmk

#endif
