#ifndef CLASSES_GF_PC_TASKFIELDCHECKWARPFALLDEAD_H
#define CLASSES_GF_PC_TASKFIELDCHECKWARPFALLDEAD_H

#include "mm/mtl/RTTI.h"

namespace gf { namespace pc {
// 1.0.0's third warp task (its table, functions and BehaviorTree::createTask instance are 1.0.0's): 3.0.1's
// linker dropped all of its code, and only its m_rtti, which its unit's static initializer builds, is left
class TaskFieldCheckWarpFallDead {
public:
    static mm::mtl::RTTI m_rtti;
};
}}  // namespace gf::pc

#endif
