#ifndef CLASSES_GF_GFPLAYCOMRESETBLADE_H
#define CLASSES_GF_GFPLAYCOMRESETBLADE_H

#include "classes/gf/GfPlayCom.h"
#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/FixedQueue.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B581D8
class GfPlayComResetBlade : public GfPlayCom {
public:
    // the field names are not the original's
    GfPlayComResetBlade(unsigned int blade, int mode)
        : GfPlayCom(42, true), m_req(-1), m_blade(blade), m_mode(mode), m_wait(0), m_state(0) {
        if (blade <= 2) {
            s_execFlag.push_back(blade);
        }
    }
    static GfPlayComResetBlade* create(unsigned int blade, int mode);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComResetBlade();  // slot 1 (symbols: fn_710031D164, D0 fn_710031D21C)
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComResetBlade";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    unsigned int m_req;    // the change request's handle (GfReqManager::isValid), -1 for none
    unsigned int m_blade;  // addResetBlade's first argument (the name is not the original's)
    int m_mode;            // addResetBlade's second argument: the set id, or which of three resets
    int m_wait;            // start() sets 3; update counts it down before requesting
    int m_state;           // 0 waiting, 1 waiting on the request
    // whether the reset of a party slot's blade (0-2) is running
    static bool isPlaying(unsigned int slot);
    // the party slots whose reset is running (unsigned bytes: isPlaying and the destructor compare them with
    // ldrb against the slot's low byte)
    static mm::mtl::FixedVector<signed char, 3> s_execFlag;
};
}  // namespace gf

#endif
