#ifndef CLASSES_GMK_GMKSQUAD_H
#define CLASSES_GMK_GMKSQUAD_H

#include "classes/gmk/GmkAcc.h"
#include "classes/gmk/GmkSquadLeader.h"
#include "classes/gmk/IGmkList.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/Vector.h"

namespace gmk {
class GmkSquadLeader;
class GmkSquadNavi;
// table 0x7100B6CD10
// counted (GmkEnemyInsts::createSquad takes a reference, `m_RefCount > 0` as it releases one) and linked into
// GmkSquadManager's list through its node at 0x10 (create links it, dispose unlinks it)
class GmkSquad : public ::mm::mtl::ReferenceObject, public ::mm::mtl::IntrusiveListNodeBase {
public:
    // what GmkEnemyInsts::createSquad builds (the gimmick set's row, its squad id less one, a count); the names are
    // not the original's
    class CreateInfo {
    public:
        CreateInfo() : m_gmkSetId(-1), pad_4(-1), pad_8(1) {}
        int m_gmkSetId;  // create finds the gimmick set (GmkManager::findGmkSet) and reaches its squad leader in it
        int pad_4;       // the leader's row (GmkAcc::CreateInfo's pad_8)
        unsigned int pad_8;
    };
    virtual ~GmkSquad();  // slot 0
    void create(const CreateInfo& info);
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
    // member index placed at random within the leader's circle around member 0, facing as member 0 does (1.0.0 name)
    void updateMemberPosRotY_MemberDef_Circle(unsigned int index);
    void removeGmkSquadNavi(GmkSquadNavi* navi);
    CreateInfo m_info;  // 0x20: the name is not the original's
    float pad_2c = 1.0f;  // 1.0 at construction (GmkMobInsts::createSquad); GmkEnemyInsts::createSquad stores its float argument
    // 0x30: the destructor ends this access after dispose (GmkAcc's table and GmkAccManager::removeGmkAcc); the name
    // is not the original's
    GmkAcc m_acc;
    unsigned int pad_70 = 0;  // how many members it has (GmkSquadNavi::getMemberDefType, GfComBehaviorMob::isSquadMember)
    unsigned char pad_74[0x4];
    void (GmkSquad::*m_seq)(float) = nullptr;  // 0x78: the step to run (seqUpdate sets seqInit; the name is not the
    // original's)
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
