#ifndef CLASSES_EVENT_CMDQUEUE_H
#define CLASSES_EVENT_CMDQUEUE_H

#include "classes/event/CmdItem.h"
#include "classes/event/ICmd.h"
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
    // queues cmd with its parameters, dropping the oldest while the queue is full (one instance per queue size)
    void push_back(ICmd* cmd, const CmdParam& param);
    mm::mtl::FixedVector<CmdItem, T0> m_items;  // 0x8 (the name is not the original's)
};
template <unsigned long T0, int T1>
void CmdQueue<T0, T1>::erase(const ICmd* cmd) {
    for (CmdItem* it = m_items.begin(); it != m_items.end(); ++it) {
        if (it->m_cmd == cmd) {
            it->m_cmd->term();
            m_items.erase(it);
            return;
        }
    }
}

template <unsigned long T0, int T1>
void CmdQueue<T0, T1>::push_back(ICmd* cmd, const CmdParam& param) {
    while (m_items.size() >= m_items.capacity()) {
        m_items.erase(m_items.begin());
    }
    cmd->init();
    m_items.push_back(CmdItem(cmd, param));
}
}  // namespace event

#endif
