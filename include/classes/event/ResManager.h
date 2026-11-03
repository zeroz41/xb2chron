#ifndef CLASSES_EVENT_RESMANAGER_H
#define CLASSES_EVENT_RESMANAGER_H

#include "classes/event/ResPackManager.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"
#include <string.h>
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; class IResEvent; }
#include "classes/event/IResPackEvent.h"

namespace event {
// table 0x7100B3C098; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::ResManager>, base at 0x10 event::IResPackEvent (ResPackManager::load gets it)
class ResManager : public IManager, public mm::mtl::Singleton<ResManager>, public IResPackEvent {
public:
    virtual ~ResManager() {}  // slot 0
    ResManager();  // out of line (Singleton<ResManager>::getPtr calls it)
    void loadPack(const char* name);
    // named by the symbols (CamManager/CharaManager/EffectManager::loadResource tail-call it)
    void load(const char* name, IResEvent* event, bool);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    virtual void OnPackEvent(event::IResPackEvent::PARAM const&);  // slot 3
    void clear();
    void update();
    void render();

    // the 0x438-byte entry load() news (1.0.0's symbols: ResManager::Item::Item(char const*, IResEvent*, bool,
    // RES_RESULT_TYPE, void*, unsigned long, bool)): a FixStr name first, a reference-counted holder @0x418, the
    // asset @0x420 clear() releases through GfAssetManager::releaseRefResource
    struct Item {
        mm::mtl::FixStr<256> m_name;  // 0x0: search() strstr's it (the name is not the original's)
        unsigned char pad_104[0x31c];
        void* m_data;  // 0x420: the ctor's void* (the name is not the original's)
        unsigned long m_size;  // 0x428: the ctor's unsigned long (the name is not the original's)
        unsigned char pad_430[0x8];
    };
    // 1.0.0's ResManager::search (0x710009929C, out of line there; 3.0.1 inlines it): the first item whose name
    // contains the text
    Item* search(const char* name) {
        for (Item** it = m_entries.begin(); it != m_entries.end(); ++it) {
            if (strstr((*it)->m_name.m_str, name) != nullptr) {
                return *it;
            }
        }
        return nullptr;
    }

    unsigned int pad_0x18;  // the constructor and clear() zero an int here
    mm::mtl::FixedVector<Item*, 512> m_entries;  // @0x20, size @0x1020; the name is not the original's
    ResPackManager m_packManager;  // @0x1028; the name is not the original's
    long pad_0x10b8;  // the constructor and clear() zero 8 bytes here
};
}  // namespace event

#endif
