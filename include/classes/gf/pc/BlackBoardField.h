#ifndef CLASSES_GF_PC_BLACKBOARDFIELD_H
#define CLASSES_GF_PC_BLACKBOARDFIELD_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/BlackBoard.h"

namespace gf { namespace pc {
// table 0x7100B67908
class BlackBoardField : public ::ai::BlackBoard {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~BlackBoardField();  // slot 1
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
