#ifndef CLASSES_FW_COLIUSERDATA_H
#define CLASSES_FW_COLIUSERDATA_H

#include "mm/mtl/RTTI.h"

namespace fw {
// what a collision carries for its owner. 1.0.0 names its type fw::ColiUserData::m_rtti ("ColiUserData", no
// bases; here lbl_7100C23468, constructed by unit_710016A378's initializer), the base the gmk collision and
// gimmick types' m_rtti name. Its table and members are not identified yet.
class ColiUserData {
public:
    static mm::mtl::RTTI m_rtti;
};
}  // namespace fw

#endif
