#ifndef ANM_ASMBLENDER_H
#define ANM_ASMBLENDER_H

#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/anm/ReferenceObject.h"

namespace anm { class AsmListener; class Blender; class Control; class QsTransform; class ResASM; }
namespace anm { struct ResClipData; struct ResStateData; }
namespace mm { namespace mtl { class IAllocator; } }

namespace anm {

// how an additive state eases in and out (no value has a name yet; AdditiveInfo::updateFrame skips the state's update
// while easing with 0, and update takes 1 for an ease curve)
enum InterpolateType : int {};
enum InterpolateCurve : int {};

class AsmBlender;
struct AsmClip;

// a state of an animation state machine (SimplexState, FrozenState and the blend trees derive from it); counted
class AsmState : public ReferenceObject {
public:
    // (inline: the blend trees' constructors inline it; the names of the fields are not the original's)
    AsmState(const ResStateData* pRes, mm::mtl::IAllocator& allocator)
        : ReferenceObject(&allocator), m_pRes(pRes), m_speed(1.0f), m_weight(1.0f), m_loopCount(0),
          m_loop(0) {}

    virtual void attach(AsmBlender* blender) = 0;     // slot 2
    virtual void dettach(AsmBlender* blender) = 0;    // slot 3
    virtual void onEnter(AsmListener* listener) = 0;  // slot 4
    virtual void onLeave(AsmListener* listener) = 0;  // slot 5
    virtual void update(float dt, AsmListener* listener) = 0;  // slot 6
    virtual void setLocalTime(float time) = 0;  // slot 7
    virtual float getLocalTime() const = 0;     // slot 8
    virtual void onSetSpeed() = 0;              // slot 9
    virtual void onSetWeight() = 0;             // slot 10: m_weight changed
    virtual AsmClip* getBaseClip() const = 0;   // slot 11: the first clip (the type is not proven)

    // m_weight, told to the state (inline: the name is not the original's)
    void setWeight(float weight) {
        m_weight = weight;
        onSetWeight();
    }

    // the loop counting the listener sees (emitted with AddBlendTree)
    void initLoopCount();
    // the state's enter and leave callbacks told to the listener (emitted with AddBlendTree)
    void notifyEnter(AsmListener* listener);
    void notifyLeave(AsmListener* listener);
    // one more loop when the base clip looped: always with a loop count, once without (the name is not the original's)
    void countLoop(bool looped) {
        if (m_loopCount <= 0 ? (m_loopCount == 0 && m_loop == 0 && looped) : looped) {
            m_loop++;
        }
    }

    const ResStateData* m_pRes;
    float m_speed;   // onEnter resets it to 1, then calls onSetSpeed (the name is not the original's)
    float m_weight;  // AdditiveInfo sets it, then calls onSetWeight (the name is not the original's)
    int m_loopCount;  // initLoopCount's (the name is not the original's)
    int m_loop;       // the loops counted (the name is not the original's)
};

// one clip AsmBlender blends: its control and its resource (the names are not the original's)
struct AsmClip : public mm::mtl::IntrusiveListNodeBase {
    AsmClip();
    ~AsmClip();
    void destroyControl();
    void createControl(const ResClipData& res, mm::mtl::IAllocator& allocator);
    // true when the clip looped
    bool update(float dt, AsmListener* listener);
    void setLocalTime(float time);
    float getLocalTime() const;
    void setSpeed(float speed);
    void setWeight(float weight);

    Control* m_pControl;
    const ResClipData* m_pRes;
};

// an additive state over the state machine's, eased in and out (the names are not the original's)
class AdditiveInfo {
public:
    // easing modes
    enum {
        MODE_NONE = 0,
        MODE_IN = 1,
        MODE_OUT = 2,
    };

    AdditiveInfo();
    // state replaces the current state, its weight eased from 0 to weight over time (at once for no time)
    void easeIn(AsmBlender* blender, AsmListener* listener, mm::mtl::IntrusivePtr<AsmState> state, float time,
                float weight, InterpolateType type, InterpolateCurve curve);
    // the state eased out over time, left at once for no time
    void easeOut(AsmBlender* blender, AsmListener* listener, float time, InterpolateType type, InterpolateCurve curve);
    void updateFrame(float dt, AsmListener* listener);
    void update(float dt, AsmBlender* blender, AsmListener* listener);

    mm::mtl::IntrusivePtr<AsmState> m_state;
    float m_time;             // how long the ease takes
    InterpolateCurve m_curve;
    InterpolateType m_type;
    float m_elapsed;
    int m_mode;               // MODE_*
    float m_weight;           // easeIn's: the weight eased to
    float m_scale;            // 1 from the constructor: scales the eased weight
};

// blends an animation state machine's clips (anm_asm_blender.cpp)
class AsmBlender {
public:
    AsmBlender();
    ~AsmBlender();
    void setup(const ResASM& res, mm::mtl::IAllocator& allocator);
    void cleanup();
    void sampleTrucks(unsigned int count, QsTransform* pOut);
    void sampleTrucksMS(unsigned int count, QsTransform* pOut);
    // the clips' extracted motions blended over dt
    void getDeltaExtractMotion(float dt, QsTransform* pOut) const;
    // the slot's values, each clamped to its bounds
    void sampleExtraTrucks(unsigned short slot, unsigned int count, float* pOut);
    bool addClip(AsmClip& clip);
    void removeClip(AsmClip& clip);

    Blender* m_pBlender;  // anm_asm_blender.cpp asserts `m_pBlender`
    mm::mtl::IntrusiveList<AsmClip> m_clips;
    // set by the samplers when every clip is flagged so (they then skip the next sampling; the name is not the
    // original's)
    bool m_skipSample;
};

}  // namespace anm

#endif
