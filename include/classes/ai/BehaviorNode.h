#ifndef CLASSES_AI_BEHAVIORNODE_H
#define CLASSES_AI_BEHAVIORNODE_H

#include "ai/Event.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/RTTI.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80E20; its trees hold their nodes through mm::mtl::IntrusivePtr
class BehaviorNode : public ::mm::mtl::ReferenceObject {
public:
    BehaviorNode(const char* name, unsigned int flags);
    virtual ~BehaviorNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&) { return true; }  // slot 3
    virtual bool execute(ai::BlackBoard&) { return true; }  // slot 4
    virtual void setActiveNotiryChildren(ai::BlackBoard& blackBoard, bool active) {  // slot 5
        if (m_active != active) {
            m_active = active;
            if (m_flags & 1) {
                Event event;
                event.m_type = 1;
                event.m_active = active;
                onEvent(blackBoard, event);
            }
        }
    }
    virtual void onEvent(ai::BlackBoard&, ai::Event const&) {}  // slot 6

    static mm::mtl::RTTI m_rtti;
    mm::mtl::FixStr<32> m_name;
    bool m_active;         // set by setActiveNotiryChildren
    // bit 0: setActiveNotiryChildren tells onEvent of a change; bit 2: BehaviorTree::cleanup sends it event 4
    unsigned int m_flags;
};
}  // namespace ai

#endif
