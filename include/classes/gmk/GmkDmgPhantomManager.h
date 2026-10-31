#ifndef CLASSES_GMK_GMKDMGPHANTOMMANAGER_H
#define CLASSES_GMK_GMKDMGPHANTOMMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "mm/mtl/Vector.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// an element of GmkDmgPhantomManager's vector (Vector<gmk::GmkDmgPhantomTargetInfo>::erase); 0x10 bytes
class GmkDmgPhantomTargetInfo {
public:
    GmkDmgPhantomTargetInfo(gf::GF_OBJ_HANDLE* gob) : m_gob(gob), m_insideCount(0), pad_c(0) {}
    // the object listenerGfObj/gevPartyMover add and remove (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;
    // isGobInstInsideDmgPhantom: the object is inside while it is above 0 (the name is not the original's)
    int m_insideCount;
    int pad_c;
};

// table 0x7100B6CF98; a listener gf::GfObjManager::addListener registers and an event callback
// gf::GfEvent::addEventCallback registers at 0x8 (its constructor)
class GmkDmgPhantomManager : public ::gf::IGfObjListener, public ::gf::IGfEvent {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    GmkDmgPhantomManager();
    virtual ~GmkDmgPhantomManager();  // slot 1
    void create();
    void update(float dt);
    bool isGobInstInsideDmgPhantom(gf::GF_OBJ_HANDLE* handle) const;
    void addTargetInfo(gf::GF_OBJ_HANDLE* handle);
    virtual void gevPartyMover(gf::GF_OBJ_HANDLE*, bool);  // slot 3
    // 0x10: the objects it watches (the name is not the original's)
    mm::mtl::Vector<GmkDmgPhantomTargetInfo> m_targets;
    bool pad_38;  // the constructor clears it; size 0x40 from GfFieldGimmick (GmkAntiBladeAreaManager follows at +0x40)
};
}  // namespace gmk

#endif
