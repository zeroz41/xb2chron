#ifndef CLASSES_GMK_GMKSQUAD_H
#define CLASSES_GMK_GMKSQUAD_H

#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkSquadLeader.h"
#include "classes/gmk/IGmkList.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/Vector.h"

namespace gmk {
class GmkSquadLeader;
class GmkSquadNavi;
// table 0x7100B6CD10
class GmkSquad {
public:
    virtual ~GmkSquad();  // slot 0
    void dispose();
    void seqInit(float);
    // runs while the squad is valid: updatePosRotY(false); else back to seqInit
    void seqUpdate(float);
    void updatePosRotY(bool);
    // its leader, when the access reaches a valid one with members and the squad has members; none otherwise
    GmkSquadLeader* getBindedGmkSquadLeader() const;
    // whether the access reaches a valid leader with members and the squad has members: getBindedGmkSquadLeader's test
    // as a bool (inline in GmkSquadNavi::getPosRotY, which goes on without reading the leader again; the name is not
    // the original's)
    bool isValid() const {
        if (m_acc.isValid()) {
            IGmkList* members = static_cast<GmkSquadLeader*>(m_acc.m_gmk)->getBindedSquadMemberList();
            if (members != nullptr && members->getInstNum() != 0 && pad_70 != 0) {
                return true;
            }
        }
        return false;
    }
    // the position and y rotation of member index (out of line, 0x7100580618; the mob pop finders call it)
    void getPosRotY(::mm::Vec3& pos, float& rotY, unsigned int index) const;
    // 1.0.0's names: GmkSquadNavi::create joins its squad through addGmkSquadNavi, dispose leaves through
    // removeGmkSquadNavi
    void addGmkSquadNavi(GmkSquadNavi* navi);
    void removeGmkSquadNavi(GmkSquadNavi* navi);
    unsigned char pad_8[0x28];
    // 0x30: the destructor ends this access after dispose (GmkAcc's table and GmkAccManager::removeGmkAcc); the name
    // is not the original's
    GmkAcc m_acc;
    unsigned int pad_70;  // how many members it has (GmkSquadNavi::getMemberDefType, GfComBehaviorMob::isSquadMember)
    unsigned char pad_74[0x4];
    void (GmkSquad::*m_seq)(float);  // 0x78: the step to run (seqUpdate sets seqInit; the name is not the original's)
    // 0x88: the navis that joined it (addGmkSquadNavi links one, removeGmkSquadNavi unlinks it; the name is not the
    // original's)
    ::mm::mtl::IntrusiveList<GmkSquadNavi> m_navis;
    // seqInit fills these three (Vector<Vec3>::expand/push_back, Vector<float>::expand, Vector<bool>::expand); the
    // names are not the original's
    ::mm::mtl::Vector< ::mm::Vec3> m_vec3s;  // 0xa0
    ::mm::mtl::Vector<float> m_floats;  // 0xc8
    ::mm::mtl::Vector<bool> m_bools;  // 0xf0
};
}  // namespace gmk

#endif
