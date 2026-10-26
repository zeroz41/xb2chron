#ifndef CLASSES_GMK_GMKDOORPHANTOMMANAGER_H
#define CLASSES_GMK_GMKDOORPHANTOMMANAGER_H

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6CDE8
class GmkDoorPhantomManager {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    virtual ~GmkDoorPhantomManager();  // slot 1
    void update(float dt);
    unsigned char pad_8[0x28];  // fields: size from GfFieldGimmick, where GmkDmgPhantomManager follows it at +0x30
};
}  // namespace gmk

#endif
