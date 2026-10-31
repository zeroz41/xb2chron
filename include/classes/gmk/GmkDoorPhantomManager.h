#ifndef CLASSES_GMK_GMKDOORPHANTOMMANAGER_H
#define CLASSES_GMK_GMKDOORPHANTOMMANAGER_H

#include "mm/mtl/Vector.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// an element of GmkDoorPhantomManager's vector (Vector<gmk::GmkDoorPhantomTargetInfo>::erase); 8 bytes
class GmkDoorPhantomTargetInfo {
public:
    GmkDoorPhantomTargetInfo(gf::GF_OBJ_HANDLE* gob) : m_gob(gob) {}
    // the object listenerGfObj adds when it is created, removes when it is destroyed (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;
};

// table 0x7100B6CDE8; a listener gf::GfObjManager::addListener registers (its constructor)
class GmkDoorPhantomManager : public ::gf::IGfObjListener {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    GmkDoorPhantomManager();
    virtual ~GmkDoorPhantomManager();  // slot 1
    void create();
    void update(float dt);
    // 0x8: the objects it watches (the name is not the original's); size 0x30 from GfFieldGimmick, where
    // GmkDmgPhantomManager follows it at +0x30
    mm::mtl::Vector<GmkDoorPhantomTargetInfo> m_targets;
};
}  // namespace gmk

#endif
