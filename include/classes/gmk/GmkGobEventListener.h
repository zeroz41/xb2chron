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
};
}  // namespace gmk

#endif
