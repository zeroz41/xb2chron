#ifndef CLASSES_FW_EFFECTCASTERSEND_H
#define CLASSES_FW_EFFECTCASTERSEND_H

#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/FixStr.h"

namespace mm { class Mat44; }
namespace fw { class EffectCasterBase; }

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
    void sendData(mm::Mat44& mtx, const char* name, int index);
    void sendDataStateName(const char* name);

    unsigned char pad_18[0x50];
    EffectCasterBase* m_caster;  // the caster it sends for (EffectManager finds a caster's by it)
    unsigned char pad_70[0x10];
    void* m_mdl;  // getMdl's last model (the name is not the original's)
    // per half of effect::SystemManager's double buffer (m_secondBuffer picks one): EffectCasterBase::setScl's and
    // setMotionFrame's values (the names are not the original's)
    float m_scl[2];
    float m_frame[2];
    mm::mtl::FixStr<32> m_stateName[2];  // per half, sendDataStateName's (the name is not the original's)
};
}  // namespace fw

#endif
