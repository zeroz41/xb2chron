#ifndef CLASSES_GMK_GMKSQUAD_H
#define CLASSES_GMK_GMKSQUAD_H

#include "classes/gmk/GmkAcc.h"
#include "mm/Vec3.h"
#include "mm/mtl/Vector.h"

namespace gmk {
// table 0x7100B6CD10
class GmkSquad {
public:
    virtual ~GmkSquad();  // slot 0
    void dispose();
    unsigned char pad_8[0x28];
    // 0x30: the destructor ends this access after dispose (GmkAcc's table and GmkAccManager::removeGmkAcc); the name
    // is not the original's
    GmkAcc m_acc;
    unsigned int pad_70;  // how many members it has (GmkSquadNavi::getMemberDefType, GfComBehaviorMob::isSquadMember)
    unsigned char pad_74[0x2c];
    // seqInit fills these three (Vector<Vec3>::expand/push_back, Vector<float>::expand, Vector<bool>::expand); the
    // names are not the original's
    ::mm::mtl::Vector< ::mm::Vec3> m_vec3s;  // 0xa0
    ::mm::mtl::Vector<float> m_floats;  // 0xc8
    ::mm::mtl::Vector<bool> m_bools;  // 0xf0
};
}  // namespace gmk

#endif
