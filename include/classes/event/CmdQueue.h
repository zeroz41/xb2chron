#ifndef CLASSES_EVENT_CMDQUEUE_H
#define CLASSES_EVENT_CMDQUEUE_H

#include "classes/event/CmdItem.h"
#include "mm/mtl/FixedVector.h"

namespace event {
// a template: 4 instances in the module
template <unsigned long T0, int T1>
class CmdQueue {
public:
    virtual ~CmdQueue() {}  // slot T1
    void update();
    // the commands destroyed from the last (RandManager::clear inlines it)
    void clear() { m_items.clear(); }
    bool empty() const { return m_items.empty(); }
    // removes the item running cmd (out of line in CharaObj.cpp, one instance per queue size)
    void erase(const ICmd* cmd);
    // erases every command, first to last (CharaObj::clear inlines it); the name is not the original's
    void eraseAll() {
        while (!empty()) {
            erase(m_items.begin()->m_cmd);
        }
    }
    mm::mtl::FixedVector<CmdItem, T0> m_items;  // 0x8 (the name is not the original's)
};
}  // namespace event

#endif
