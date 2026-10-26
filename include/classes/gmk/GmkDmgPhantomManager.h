#ifndef CLASSES_GMK_GMKDMGPHANTOMMANAGER_H
#define CLASSES_GMK_GMKDMGPHANTOMMANAGER_H

#include "classes/gf/IGfEvent.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// a base of gmk::GmkDmgPhantomManager no evidence names yet
class TUnk_B6CF98 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
    virtual ~TUnk_B6CF98();
    virtual void gevPartyMover(gf::GF_OBJ_HANDLE*, bool) = 0;
};
// table 0x7100B6CF98; base at 0x0 unknown (TUnk_B6CF98)
class GmkDmgPhantomManager : public TUnk_B6CF98, public ::gf::IGfEvent {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    GmkDmgPhantomManager();
    virtual ~GmkDmgPhantomManager();  // slot 1
    void update(float dt);
    virtual void gevPartyMover(gf::GF_OBJ_HANDLE*, bool);  // slot 3
};
}  // namespace gmk

#endif
