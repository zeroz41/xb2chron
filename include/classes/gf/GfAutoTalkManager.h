#ifndef CLASSES_GF_GFAUTOTALKMANAGER_H
#define CLASSES_GF_GFAUTOTALKMANAGER_H

#include "classes/gf/IGfEvent.h"
#include "classes/gf/GfEvent.h"
#include "classes/gf/GfAutoTalkList.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusiveList.h"
#include "plugin/Bdat.h"

namespace gf { class GfAutoTalkManager; }
namespace gf { class GfSetupParam; }
namespace gf { class GfAutoTalk; }
namespace gf { enum RELOAD_BDAT : int; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B53838: the current map's auto talks, a list per gimmick set. The members are 1.0.0's.
class GfAutoTalkManager : public ::mm::mtl::PtrSingleton< ::gf::GfAutoTalkManager>, public ::gf::IGfEvent {
public:
    GfAutoTalkManager(const GfSetupParam& param) : m_seq(nullptr) {
        GfEvent::addEventCallback(this);
    }
    virtual ~GfAutoTalkManager() {  // slot 0
        dispose();
        GfEvent::removeEventCallback(this);
    }
    virtual void gevReloadBdat(gf::RELOAD_BDAT type, unsigned int) {  // slot 2
        if (type == 1) {
            create();
        }
    }
    static void build(const GfSetupParam& param);
    void create();
    static void destroy();
    static bool isInitialized() { return get() != nullptr; }
    static void update(const fw::UpdateInfo& info);
    void update(float dt) {
        if (m_seq) {
            (this->*m_seq)(dt);
        }
    }
    void dispose() {
        clearAutoTalkLists();
        m_seq = nullptr;
    }
    void seqInit(float dt);
    void clearAutoTalkLists() {
        while (!m_lists.empty()) {
            GfAutoTalkList* list = static_cast<GfAutoTalkList*>(m_lists.m_root.m_next);
            m_lists.remove(list);
            delete list;
        }
    }
    bool createAutoTalkList(int id);
    void disposeAutoTalkList(int id) {
        for (mm::mtl::IntrusiveList<GfAutoTalkList>::iterator it = m_lists.begin(); it != m_lists.end(); ++it) {
            if (it->m_info.m_id == id) {
                GfAutoTalkList* list = it.m_node;
                m_lists.remove(list);
                delete list;
                break;
            }
        }
    }
    void seqUpdate(float dt);
    // the talk of that row in the list of that table, none when no list has the table (inline: canDispText's
    // chain test; the name is 1.0.0's)
    const GfAutoTalk* findGfAutoTalkByBdatId(unsigned char* fp, int id) const {
        for (mm::mtl::IntrusiveList<GfAutoTalkList>::iterator it = m_lists.begin(); it != m_lists.end(); ++it) {
            if (it->m_info.m_fp == fp) {
                const mm::mtl::Vector<GfAutoTalk>& talks = it->m_talks;
                unsigned int index = id - Bdat::getIdTop(fp);
                return &talks[index];
            }
        }
        return nullptr;
    }

    mm::mtl::IntrusiveList<GfAutoTalkList> m_lists;  // 0x10 (the names are not the original's)
    void (GfAutoTalkManager::*m_seq)(float);         // 0x28: seqInit, then seqUpdate
};
}  // namespace gf

#endif
