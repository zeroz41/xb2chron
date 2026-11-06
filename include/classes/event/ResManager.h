#ifndef CLASSES_EVENT_RESMANAGER_H
#define CLASSES_EVENT_RESMANAGER_H

#include "classes/event/ResPackManager.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixStr.h"
#include <string.h>
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; class IResEvent; }
// 1.0.0's ResManager::Item constructor mangles it; the values are not named
namespace event { enum RES_RESULT_TYPE : int {}; }
#include "classes/event/IResPackEvent.h"
#include "classes/event/IResEvent.h"
#include "classes/fw/RenderResource.h"

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
    // 1.0.0's symbol; update calls it out of line while no pack loads
    void updateNormal();
    void render();

    // the 0x438-byte entry load() news (1.0.0's symbols: ResManager::Item::Item(char const*, IResEvent*, bool,
    // RES_RESULT_TYPE, void*, unsigned long, bool) and Item::addRef(IResEvent*)); 3.0.1 inlines them. The field
    // names are not the original's
    struct Item {
        Item(const char* name, IResEvent* event, bool packOnly, RES_RESULT_TYPE type, void* data, unsigned long size,
             bool packed)
            : m_name(name), m_packOnly(packOnly), m_eventIndex(0), m_eventCount(1), m_res(nullptr), m_data(data),
              m_size(size), m_type(type), m_packed(packed) {
            m_events[0] = event;
            for (int i = 1; i < 96; i++) {
                m_events[i] = nullptr;
            }
        }
        ~Item() {
            if (m_res != nullptr) {
                m_res->release();
            }
        }
        void addRef(IResEvent* event) { m_events[m_eventCount++] = event; }

        mm::mtl::FixStr<256> m_name;  // 0x0: search() strstr's it
        IResEvent* m_events[96];  // 0x108: the listeners, called once it has loaded (execCallback)
        // 0x408: the ctor's first bool; updateNormal skips the request when it is set; render's "packonly" column
        bool m_packOnly;
        unsigned int m_eventIndex;  // 0x40c: the next listener execCallback calls
        unsigned int m_eventCount;  // 0x410
        fw::RenderResource* m_res;  // 0x418: the requested resource (updateNormal)
        void* m_data;  // 0x420: the ctor's void*; the asset clear() releases through GfAssetManager::releaseRefResource
        unsigned long m_size;  // 0x428: the ctor's unsigned long
        RES_RESULT_TYPE m_type;  // 0x430: 0 to request, 1 requested, 2 loaded, 3 done, 4 failed
        bool m_packed;  // 0x434: the ctor's last bool; OnPackEvent sets it
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
    // 1.0.0's ResManager::filename (0x7100098F64; 3.0.1 inlines it: render): the name after the path's last
    // separator
    static const char* filename(const char* path) {
        const char* name = strrchr(path, '\\');
        if (name != nullptr) {
            return name + 1;
        }
        name = strrchr(path, '/');
        return name != nullptr ? name + 1 : path;
    }
    // 1.0.0's ResManager::execCallback (0x7100098B04; 3.0.1 inlines it: updateNormal): reports the item to each
    // listener not called yet
    void execCallback(Item* item) {
        IResEvent::PARAM param = {item->m_type, item->m_name.m_str, item->m_data, item->m_size};
        for (; item->m_eventIndex < item->m_eventCount; item->m_eventIndex++) {
            if (IResEvent* event = item->m_events[item->m_eventIndex]) {
                event->OnResEvent(param);
            }
        }
    }

    unsigned int pad_0x18;  // the constructor and clear() zero an int here
    mm::mtl::FixedVector<Item*, 512> m_entries;  // @0x20, size @0x1020; the name is not the original's
    ResPackManager m_packManager;  // @0x1028; the name is not the original's
    // the constructor and clear() zero 8 bytes here; Manager::update waits while the int is above 0
    int pad_0x10b8;
    unsigned int pad_0x10bc;
};
}  // namespace event

#endif
