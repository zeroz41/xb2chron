#ifndef CLASSES_GF_PC_TASKFIELDRETREAT_H
#define CLASSES_GF_PC_TASKFIELDRETREAT_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }
namespace gf { namespace pc { class BlackBoardField; }}

namespace gf { namespace pc {
// table 0x7100B67AE0
class TaskFieldRetreat : public ::ai::BehaviorNode {
public:
    virtual ~TaskFieldRetreat();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&);  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
