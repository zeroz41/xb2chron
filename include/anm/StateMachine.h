#ifndef ANM_STATEMACHINE_H
#define ANM_STATEMACHINE_H

#include <string.h>
#include "anm/AsmBlender.h"
#include "anm/StringPtr.h"
#include "mm/mtl/Map.h"

namespace anm { class ResASM; }

namespace anm {

// where setState starts the new state (no value has a name yet; gf::GfComAsm passes 0 and its setup info's byte)
enum StartFrameType : int {};

// one layer of an animation state machine: anm::ASMControl keeps seven, 0x70 apart (the field names are not the
// original's)
class StateMachine {
public:
    StateMachine();
    bool executeCmd(const char* cmd);
    const char* getStateName() const;
    bool setState(const char* state, StartFrameType type);
    bool doEaseInAdditive(const char* state, float time, float weight, InterpolateType type, InterpolateCurve curve);
    bool doEaseOutAdditive(const char* state, float time, InterpolateType type, InterpolateCurve curve);
    bool setAdditiveStateWeight(const char* state, float weight);
    bool setAdditiveStateSpeed(const char* state, float speed);
    bool isEnd() const;
    bool isLoop() const;
    void setLocalTime(float time);
    float getLocalTime() const;
    void setSpeed(float speed);
    float getSpeed() const;
    unsigned long getAttribute(unsigned int category) const;
    // whether an additive state of the name plays (inline: gf::GfComAsm::isActiveAdditiveState; the name is not the
    // original's)
    bool isActiveAdditiveState(const char* state) const { return m_additives.find(state) != nullptr; }
    // whether a state is being blended in (inline: gf::GfComAsm::isInterpolate; the name is not the original's)
    bool isInterpolate() const { return m_interpolate != nullptr; }

    unsigned char pad_0[0x10];
    mm::mtl::Map<StringPtr, AdditiveInfo> m_additives;  // by state name
    const void* m_interpolate;  // the state blended in, none when there is none
    unsigned char pad_30[0x40];
};
}  // namespace anm

#endif
