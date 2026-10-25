#ifndef CLASSES_EVENT_RESMANAGER_H
#define CLASSES_EVENT_RESMANAGER_H

#include "classes/event/ResPackManager.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }
namespace event { namespace IResPackEvent { class PARAM; }}

namespace event {
// a base of event::ResManager no evidence names yet
class TUnk_B3C098 {
public:
    virtual ~TUnk_B3C098() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
    virtual void OnPackEvent(event::IResPackEvent::PARAM const&) = 0;
};
// a base of event::ResManager no evidence names yet
class TUnk_B3C0C8 {
public:
    virtual ~TUnk_B3C0C8() {}
};
// a base of event::ResManager no evidence names yet
class TUnk_B3C0E8 {
public:
    virtual void OnPackEvent(event::IResPackEvent::PARAM const&) = 0;
};
// table 0x7100B3C098; base at 0x0 unknown (TUnk_B3C098), base at 0x8 unknown (TUnk_B3C0C8), base at 0x10 unknown (TUnk_B3C0E8)
class ResManager : public TUnk_B3C098, public TUnk_B3C0C8, public TUnk_B3C0E8 {
public:
    virtual ~ResManager() {}  // slot 0
    ResManager();  // out of line (Singleton<ResManager>::getPtr calls it)
    void loadPack(const char* name);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual void OnPackEvent(event::IResPackEvent::PARAM const&);  // slot 3
    void clear();
    void update();
    void render();

    // the name is not the original's: the 0x438-byte entry load() news (a FixStr name first, a reference-counted
    // holder @0x418, the asset @0x420 clear() releases through GfAssetManager::releaseRefResource)
    struct Entry;

    unsigned int pad_0x18;  // the constructor and clear() zero an int here
    mm::mtl::FixedVector<Entry*, 512> m_entries;  // @0x20, size @0x1020; the name is not the original's
    ResPackManager m_packManager;  // @0x1028; the name is not the original's
    long pad_0x10b8;  // the constructor and clear() zero 8 bytes here
};
}  // namespace event

#endif
