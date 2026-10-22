#ifndef CLASSES_GF_PC_TASKFIELDWALLESCAPE_H
#define CLASSES_GF_PC_TASKFIELDWALLESCAPE_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/TaskNode.h"
#include "classes/gf/pc/BlackBoardField.h"

namespace ai { class BlackBoard; }

namespace gf { namespace pc {
// table 0x7100B67A08
class TaskFieldWallEscape : public ::ai::TaskNode {
public:
    virtual ~TaskFieldWallEscape();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&);  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
    // (its checkCondition and execute, which call these, are emitted where its table is)
    bool testCondition(gf::pc::BlackBoardField const& bb);
    void update(gf::pc::BlackBoardField& bb);
    static mm::mtl::RTTI m_rtti;

    // testCondition's: how far the other players push the PC (AgentUtilField::calcParentPlayerPush's; the name is
    // not the original's)
    mm::Vec3 m_push;
};
}}  // namespace gf::pc

#endif
