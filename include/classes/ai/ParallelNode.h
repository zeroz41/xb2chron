#ifndef CLASSES_AI_PARALLELNODE_H
#define CLASSES_AI_PARALLELNODE_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/CompositeNode.h"

namespace ai { class BlackBoard; }

namespace ai {
// table 0x7100B80EF8
class ParallelNode : public ::ai::CompositeNode {
public:
    virtual ~ParallelNode();  // slot 0
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 2
    virtual bool checkCondition(ai::BlackBoard const&) { return true; }  // slot 3
    virtual bool execute(ai::BlackBoard&);  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ai

#endif
