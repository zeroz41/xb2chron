#ifndef CLASSES_FW_EFFECTCASTERSEND_H
#define CLASSES_FW_EFFECTCASTERSEND_H

#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Vector.h"
#include "mm/Mat44.h"

namespace mm { class Mat44; }
namespace fw { class EffectCasterBase; }
namespace fw { class EffectPoint; }

namespace fw {
// table 0x7100B413D0
// linked into one of EffectManager's caster groups (EffectManager::CasterGroup) through its node base
class EffectCasterSend : public ::mm::mtl::IntrusiveListNodeBase {
public:
    virtual ~EffectCasterSend();  // slot 0
    virtual void* getMdl();  // slot 2
    // the state name of the half of the double buffer effect::SystemManager reads (the one m_secondBuffer does not pick)
    virtual const char* getStateName();  // slot 3
    // the caster's bind data and its size
    virtual void* getBindData(unsigned int& size);  // slot 4
    virtual float getMdlFrame();  // slot 5
    virtual float getMdlScl();  // slot 6
    virtual void getMdlMat(mm::Mat44&);  // slot 7
    virtual void getEfpMat(mm::Mat44&, char const*);  // slot 8
    // EffectManager::sendCaster and sendCasterStateName hand a caster's values on to these
    // a send for caster with count matrices per half, from allocator (EffectManager::addCaster passes the caster's own;
    // the names of the parameters are not the original's)
    static EffectCasterSend* create(EffectCasterBase* caster, mm::mtl::IAllocator* allocator, unsigned int count);
    void sendData(mm::Mat44& mtx, const char* name, int index);
    void sendDataStateName(const char* name);
    // EffectManager::tail calls it on every send of every caster group
    void tailCopy();

    // a matrix sent for a point name: the name's hash, the name ("root" for none) and the matrix (sendData fills one;
    // the names are not the original's)
    struct MtxAndName {
        unsigned int m_hash;
        char m_name[0x1C];
        mm::Mat44 m_mtx;
    };
    // per half of effect::SystemManager's double buffer, one per point (create reserves and fills both with the
    // caster's count; the name is not the original's)
    mm::mtl::Vector<MtxAndName> m_mtxAndNames[2];
    EffectCasterBase* m_caster;  // the caster it sends for (EffectManager finds a caster's by it)
    // the caster's point (EffectManager::updateLayer updates it before the caster and marks its points dirty; the
    // name is not the original's)
    EffectPoint* m_point;
    unsigned char pad_78[0x8];
    void* m_mdl;  // getMdl's last model (the name is not the original's)
    // per half of effect::SystemManager's double buffer (m_secondBuffer picks one): EffectCasterBase::setScl's and
    // setMotionFrame's values (the names are not the original's)
    float m_scl[2];
    float m_frame[2];
    mm::mtl::FixStr<32> m_stateName[2];  // per half, sendDataStateName's (the name is not the original's)
};
}  // namespace fw

#endif
