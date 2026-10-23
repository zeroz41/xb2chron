#ifndef CLASSES_GMK_GMKGOBEVENTLISTENER_H
#define CLASSES_GMK_GMKGOBEVENTLISTENER_H

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfObjManager.h"

namespace gmk {
// table 0x7100B6BE80
class GmkGobEventListener : public ::gf::IGfObjListener {
public:
    GmkGobEventListener() : m_refCount(0) {}
    // one more gimmick list shares the listener: the first one creates and registers it (every TGmkList
    // constructor inlines it; the name is not the original's)
    static void addRef();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 0
    virtual ~GmkGobEventListener();  // slot 1
    // how many gimmick lists share it: each list's constructor adds one, TGmkList's destructor releases one and
    // deletes it at none (the name is not the original's)
    int m_refCount;
};
// the listener every gimmick list shares, none before the first list (internal: the lists reach it without the
// GOT; the name is not the original's)
static GmkGobEventListener* s_gobEventListener;
inline void GmkGobEventListener::addRef() {
    if (s_gobEventListener == nullptr) {
#line 51 "D:/Monolithsoft/BF2/prog/application/BF2\\gmk/gmk_gob_event_listener_impl.h"
        GmkGobEventListener* listener = new (gf::getAllocator(gf::ALLOCATOR(0)), __FILE__, __LINE__, 8) GmkGobEventListener();
        gf::GfObjManager::addListener(listener, gf::IGfObjListener::OBJEVT(0));
        s_gobEventListener = listener;
    }
    s_gobEventListener->m_refCount++;
}
}  // namespace gmk

#endif
