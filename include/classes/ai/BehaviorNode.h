#ifndef CLASSES_AI_BEHAVIORNODE_H
#define CLASSES_AI_BEHAVIORNODE_H

namespace ai { class BlackBoard; }
namespace ai { class Event; }

namespace ai {
// table 0x7100B80E20
class BehaviorNode {
public:
    virtual ~BehaviorNode();  // slot 0
    virtual void getRTTI() const;  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&) { return true; }  // slot 3
    virtual bool execute(ai::BlackBoard&) { return true; }  // slot 4
    virtual void setActiveNotiryChildren(ai::BlackBoard&, bool);  // slot 5
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
};
}  // namespace ai

#endif
