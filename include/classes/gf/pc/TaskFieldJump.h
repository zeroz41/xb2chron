#ifndef CLASSES_GF_PC_TASKFIELDJUMP_H
#define CLASSES_GF_PC_TASKFIELDJUMP_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/BehaviorNode.h"

namespace ai { class BlackBoard; }
namespace gf { namespace pc { class BlackBoardField; }}

namespace gf { namespace pc {
// table 0x7100B67930
class TaskFieldJump : public ::ai::BehaviorNode {
public:
    // its field AI parameter entry (AgentUtilField::getAIParamAdapter's 4); the name is not the original's
    struct Param {
        float m_minSpeed;  // update launches the PC at least this fast
    };

    virtual ~TaskFieldJump();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&);  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
