#ifndef CLASSES_AI_BLACKBOARD_H
#define CLASSES_AI_BLACKBOARD_H

#include "mm/mtl/RTTI.h"
namespace ai {
// table 0x7100B80DF8
class BlackBoard {
public:
    BlackBoard();  // out of line (0x7100862B84): BlackBoardField's ctor calls it
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~BlackBoard();  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}  // namespace ai

#endif
