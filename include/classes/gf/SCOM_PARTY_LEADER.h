#ifndef CLASSES_GF_SCOM_PARTY_LEADER_H
#define CLASSES_GF_SCOM_PARTY_LEADER_H

#include "mm/Vec3.h"

namespace gf {
// 1.0.0's party-leader request; 3.0.1 keeps only its static (gf_req_scom's static initializer sets it to
// mm::Vec3::zero), like SCOM_ADD_ETHER.h
class SCOM_PARTY_LEADER {
public:
    static mm::Vec3 s_pos;
};
}  // namespace gf

#endif
