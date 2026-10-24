#ifndef CLASSES_FW_EFFECTCASTERSEND_H
#define CLASSES_FW_EFFECTCASTERSEND_H

#include "mm/mtl/IntrusiveList.h"

namespace mm { class Mat44; }
namespace fw { class EffectCasterBase; }

namespace fw {
// table 0x7100B413D0
// linked into one of EffectManager's caster groups (EffectManager::CasterGroup) through its node base
class EffectCasterSend : public ::mm::mtl::IntrusiveListNodeBase {
public:
    virtual ~EffectCasterSend();  // slot 0
    virtual void getMdl();  // slot 2
    virtual void getStateName();  // slot 3
    virtual void getBindData(unsigned int&);  // slot 4
    virtual void getMdlFrame();  // slot 5
    virtual void getMdlScl();  // slot 6
    virtual void getMdlMat(mm::Mat44&);  // slot 7
    virtual void getEfpMat(mm::Mat44&, char const*);  // slot 8
    // EffectManager::sendCaster and sendCasterStateName hand a caster's values on to these
    void sendData(mm::Mat44& mtx, const char* name, int index);
    void sendDataStateName(const char* name);

    unsigned char pad_18[0x50];
    EffectCasterBase* m_caster;  // the caster it sends for (EffectManager finds a caster's by it)
    unsigned char pad_70[0x18];
    // per half of effect::SystemManager's double buffer (m_secondBuffer picks one): EffectCasterBase::setScl's and
    // setMotionFrame's values (the names are not the original's)
    float m_scl[2];
    float m_frame[2];
};
}  // namespace fw

#endif
