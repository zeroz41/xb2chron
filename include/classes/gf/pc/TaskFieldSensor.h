#ifndef CLASSES_GF_PC_TASKFIELDSENSOR_H
#define CLASSES_GF_PC_TASKFIELDSENSOR_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }
namespace ai { class Event; }

namespace gf { namespace pc {
// table 0x7100B67C00
class TaskFieldSensor : public ::ai::BehaviorNode {
public:
    virtual ~TaskFieldSensor();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&);  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
    virtual void onEvent(ai::BlackBoard&, ai::Event const&);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
