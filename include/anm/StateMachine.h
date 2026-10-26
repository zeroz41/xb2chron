#ifndef ANM_STATEMACHINE_H
#define ANM_STATEMACHINE_H

#include <string.h>
#include "anm/AsmBlender.h"
#include "anm/StringPtr.h"
#include "mm/mtl/Map.h"
#include "mm/mtl/Vector.h"

namespace anm { class ResASM; struct ResStateData; struct TransInfo; struct InterpolateInfo; class AsmListener; class Variable; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {

// where setState starts the new state (no value has a name yet; gf::GfComAsm passes 0 and its setup info's byte)
enum StartFrameType : int {};

// one layer of an animation state machine: anm::ASMControl keeps seven, 0x70 apart (the field names are not the
// original's)
class StateMachine {
public:
    typedef mm::mtl::Map<StringPtr, AdditiveInfo> AdditiveMap;
    typedef mm::mtl::Map<StringPtr, mm::mtl::IntrusivePtr<AsmState> > StateMap;

    StateMachine();
    ~StateMachine();
    void setup(const ResASM& res, unsigned int count, mm::mtl::IAllocator& allocator);
    AsmState* createState(const ResStateData& res);
    void cleanup();
    void update(float dt);
    void updateFrame(float dt);
    bool doTrans(const char* state, const TransInfo& trans, const InterpolateInfo& interpolate, float time, float frame);
    void clearState();
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

    mm::mtl::IntrusivePtr<AsmState> m_pState;  // the state playing (the names of the fields are not the original's)
    mm::mtl::IntrusivePtr<AsmState> m_pPrevState;  // the state blended out
    AdditiveMap m_additives;  // by state name
    const InterpolateInfo* m_interpolate;  // doTrans's while m_pPrevState blends out, none when there is none
    float m_elapsed;  // doTrans resets it
    StateMap m_states;  // by name
    AsmListener* m_pListener;
    AsmBlender* m_pBlender;
    mm::mtl::Vector<Variable>* m_pVariables;  // the blend trees read them
    mm::mtl::IAllocator* m_pAllocator;  // setup's: the states come from it
};
// a random number in [0, 1) from the state machines' own Mersenne Twister, seeded by the system tick
float rand();
}  // namespace anm

#endif
