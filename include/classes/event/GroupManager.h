#ifndef CLASSES_EVENT_GROUPMANAGER_H
#define CLASSES_EVENT_GROUPMANAGER_H

#include "mm/Mat44.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D010; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::GroupManager>
class GroupManager : public IManager, public mm::mtl::Singleton<GroupManager> {
public:
    virtual ~GroupManager();  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void update();
    void render();
    // 1.0.0's GroupManager::clear (0x71000E1998); 3.0.1 inlines it into OnEventProc
    void clear() {
        m_mtx = mm::Mat44::identity;
        m_count = 0;
        if (m_current != 0) {
            m_current = 0;
        }
    }

    unsigned char pad_10[0x418];
    // cleared by clear() when set; what it points to is not known yet; the name is not the original's
    void* m_current;  // 0x428
    unsigned char pad_430[0x20];
    // reset to the identity by clear(); the name is not the original's
    mm::Mat44 m_mtx;  // 0x450
    // zeroed by clear(); the name is not the original's
    int m_count;  // 0x490
};
}  // namespace event

#endif
