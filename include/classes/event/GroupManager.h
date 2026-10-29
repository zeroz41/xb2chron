#ifndef CLASSES_EVENT_GROUPMANAGER_H
#define CLASSES_EVENT_GROUPMANAGER_H

#include "mm/Mat44.h"
#include "classes/event/IManager.h"
#include "classes/event/Group.h"
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
        m_group.clear();
    }

    unsigned char pad_10[0x10];
    // its own table at 0x20 (the destructor stores Group's); clear() clears its list; the name is not the original's
    Group m_group;  // 0x20
    unsigned char pad_448[0x8];
    // reset to the identity by clear(); the name is not the original's
    mm::Mat44 m_mtx;  // 0x450
    // zeroed by clear(); the name is not the original's
    int m_count;  // 0x490
};
}  // namespace event

#endif
