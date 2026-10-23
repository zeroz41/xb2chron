#ifndef CLASSES_GF_GFCOMASM_H
#define CLASSES_GF_GFCOMASM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/Vector.h"
#include "anm/AsmListener.h"
#include "classes/fw/AnimAsmPoseSampler.h"
#include "classes/fw/AnimAsmUpdater.h"
#include "classes/gf/GfComAnimation.h"
#include "gf/CallBackCache.h"
namespace anm { class ASMControl; }
namespace anm { class QsTransform; }
namespace anm { class ResASM; }
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// which animation layer of an object's state machines (GfComAsm's functions ignore one past 6); LipSyncPlugin
// plays its lip animation on 4 (the name is not the original's); the code otherwise passes 0. Unsigned: GfComAsm's
// functions compare it unsigned and index with it zero-extended
enum AnimLayer : unsigned int {
    ANIM_LAYER_LIP = 4,
};

// which of an object's animation attributes GfComAsm::getAttribute reads; GfComDynamics::applyAttribute and
// FootIkControllerPlugin ask for 0 (no value has a name yet)
enum AsmCategory : int {};

// table 0x7100B65540; its constructor builds a GfComAnimation first
class GfComAsm : public ::gf::GfComAnimation {
public:
    // table 0x7100B65578: queues the state machine's annotations for executeCallback
    class AsmLisener : public ::anm::AsmListener {
    public:
        AsmLisener() {}
        // slot 0 (inline: emitted after the class's own functions)
        virtual void callback(anm::AsmListener::CallBackType type, anm::AsmAnnotetion const& annotation) {
            m_owner->m_caches.push_back(CallBackCache(type, &annotation));
        }

        GfComAsm* m_owner;  // (the name is not the original's)
    };
    // table 0x7100B65590
    class ViewerListener {
    public:
        ViewerListener() {}
        // slot 0 (inline: emitted after the class's own functions)
        virtual void onWkStandbyLogout() {
            if (m_pOwner != nullptr) {
                m_pOwner->m_pViewer = nullptr;
            }
        }

        GfComAsm* m_pOwner;  // (the name is not the original's)
    };
    // a receiver of animation events: executeCallback hands an event to the one whose name it carries
    struct CallBack {
        CallBack() : name(nullptr) {}
        const char* name;
        mm::mtl::Delegate<void(GfComAsm*, const CallBackCache&)> delegate;
    };
    // what setup takes (the field names are not the original's)
    struct SetupInfo {
        const anm::ResASM* m_res;  // the state machine to play: setup does nothing without one
        const char* m_state;  // the state the first layer starts in, if any
        unsigned char m_startFrame;  // how it starts (anm::StartFrameType)
        bool m_sampleFlag;  // the sampler's flag (fw::AnimAsmPoseSampler::m_sampleFlag)
    };

    GfComAsm();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComAsm();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    void setup(const SetupInfo& info);
    void cleanup();
    const anm::ResASM* getResource() const;
    bool getPlaybackTime(const char* state, float* pTime) const;
    bool getLocomotionReference(const char* state, float time, anm::QsTransform* pOut) const;
    bool getLocomotionDeltaReference(const char* state, float time, float dt, anm::QsTransform* pOut) const;
    // the data of the resource's appendix of the name, none without one
    const void* getAppendix(const char* name) const;
    bool existState(const char* state);
    // hands every queued event to its callback, then empties the queue
    void executeCallback();
    const char* getStateName(AnimLayer layer) const;
    bool execCmd(const char* cmd, gf::AnimLayer layer);
    bool easeIn(const char* state, float time, gf::AnimLayer layer);
    bool easeOut(const char* state, float time, gf::AnimLayer layer);
    // the attribute bits of a category on a layer: GfComDynamics::applyAttribute tests 0x4 and 0x40,
    // FootIkControllerPlugin 0x1, 0x2 and 0x8
    unsigned long getAttribute(AsmCategory category, AnimLayer layer) const;  // 64 bits (it returns xzr)
    bool setState(const char* state, gf::AnimLayer layer);
    // the inverse frame rate of a state's clip (into invFps)
    bool getClipInvFps(const char* state, unsigned int index, float* invFps) const;
    bool isActiveAdditiveState(const char* state, gf::AnimLayer layer);
    bool setWeightAdditiveState(const char* state, float weight, gf::AnimLayer layer);
    bool setSpeedAdditiveState(const char* state, float speed, gf::AnimLayer layer);
    bool isEnd(AnimLayer layer) const;
    bool isLoop(AnimLayer layer) const;
    bool isInterpolate(AnimLayer layer) const;
    void setLocalTime(float time, AnimLayer layer);
    float getLocalTime(AnimLayer layer) const;
    void setSpeed(float speed, AnimLayer layer);
    float getSpeed(AnimLayer layer) const;
    // the control's locomotion, an identity transform without a control
    const anm::QsTransform* getLocomotion() const;
    void setVariable(const char* name, float value);
    void getVariable(const char* name, float* value) const;
    void setVariable(const char* name, int value);
    static mm::mtl::RTTI m_rtti;

    anm::ASMControl* m_control;  // setup's (anm::Factory::createASMControl); cleanup releases it
    fw::AnimAsmUpdater m_updater;
    fw::AnimAsmPoseSampler m_sampler;
    // executeCallback's: the first takes the events no other one's name matches
    CallBack m_callbacks[5];
    AsmLisener m_asmListener;
    mm::mtl::Vector<CallBackCache> m_caches;  // the annotations the listener queued (setup reserves 32)
    ViewerListener m_viewerListener;
    void* m_pViewer;  // the viewer listener's onWkStandbyLogout clears it
};
}  // namespace gf

#endif
