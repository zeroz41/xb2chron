#ifndef CLASSES_GF_GFCOMEVTANIM_H
#define CLASSES_GF_GFCOMEVTANIM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"
#include "anm/AsmListener.h"
#include "classes/fw/AnimAsmUpdater.h"
#include "classes/fw/AnimBlenderUpdater.h"
#include "classes/fw/AnimEventAsmPoseSampler.h"
#include "classes/fw/AnimEventMotPoseSamper.h"
#include "classes/gf/GfComAnimation.h"
#include "classes/gf/GfComAsm.h"
#include "gf/CallBackCache.h"
#include "classes/gf/GfAllocator.h"
namespace anm { class ASMControl; }
namespace anm { class Blender; }
namespace anm { class Control; }
namespace anm { class QsTransform; }
namespace anm { class ResASM; }
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class GfComModel; }

namespace gf {
// table 0x7100B655A8; its constructor builds a GfComAnimation first. An event's animation: a state machine (Asm)
// and up to eight motions blended over it (Mot)
class GfComEvtAnim : public ::gf::GfComAnimation {
public:
    // the receiver of its animation events, as GfComAsm::CallBack (GfComSound::setup stores its name and delegate;
    // the names are not the original's)
    struct CallBack {
        CallBack() : name(nullptr) {}
        const char* name;
        mm::mtl::Delegate<void(GfComEvtAnim*, const CallBackCache&)> delegate;
    };
    // the state machine half (GfComAsm's members without the component)
    class Asm {
    public:
        // table 0x7100B655E0: queues the state machine's annotations for executeCallback
        class AsmLisener : public ::anm::AsmListener {
        public:
            AsmLisener() {}
            // slot 0 (inline: emitted after the class's own functions)
            virtual void callback(anm::AsmListener::CallBackType type, anm::AsmAnnotetion const& annotation) {
                m_owner->m_caches.push_back(CallBackCache(type, &annotation));
            }

            Asm* m_owner;  // (the name is not the original's)
        };
        // table 0x7100B655F8
        class ViewerListener {
        public:
            ViewerListener() {}
            // slot 0 (inline: emitted after the class's own functions)
            virtual void onWkStandbyLogout() {
                if (m_pOwner != nullptr) {
                    m_pOwner->m_pViewer = nullptr;
                }
            }

            Asm* m_pOwner;  // (the name is not the original's)
        };

        Asm() : m_flags(0), m_model(nullptr), m_control(nullptr), m_caches(getAllocator(ALLOCATOR(0))), m_pViewer(nullptr) {
            m_asmListener.m_owner = this;
            m_viewerListener.m_pOwner = this;
        }
        void cleanup(unsigned int layer);
        void setup(unsigned int layer, GfComModel* model, anm::ResASM* res, const char* state, bool sampleFlag);
        // hands every queued event to its callback, then empties the queue
        void executeCallback(GfComEvtAnim* owner);

        unsigned int m_flags;  // bit 0: the updater and sampler are in the manager (the name is not the original's)
        GfComModel* m_model;  // setup's
        anm::ASMControl* m_control;  // setup's (anm::Factory::createASMControl); cleanup releases it
        fw::AnimAsmUpdater m_updater;
        fw::AnimEventAsmPoseSampler m_sampler;
        // executeCallback's: the first takes the events no other one's name matches
        CallBack m_callbacks[5];
        AsmLisener m_asmListener;
        mm::mtl::Vector<CallBackCache> m_caches;  // the annotations the listener queued (setup reserves 32)
        ViewerListener m_viewerListener;
        void* m_pViewer;  // the viewer listener's onWkStandbyLogout clears it
    };
    // the motion half: up to eight motions on one blender (the field names are not the original's)
    class Mot {
    public:
        Mot() : m_flags(0), m_model(nullptr), m_res(nullptr), m_blender(nullptr), m_count(0), m_current(0), m_speed(1.0f) {}
        void cleanup(unsigned int layer);
        void stop(unsigned int layer);
        void init(unsigned int layer, void** data, unsigned long* sizes, unsigned long count);
        bool easeIn(const char* name, AnimLayer layer);
        bool easeOut(const char* name, AnimLayer layer);

        unsigned int m_flags;  // bit 0: the updater and sampler are in the manager
        GfComModel* m_model;  // GfComEvtAnim::updateSetup's
        anm::ResASM* m_res;  // GfComEvtAnim::updateSetup's (its setup info's)
        anm::Blender* m_blender;  // anm::Factory::createBlender's
        fw::AnimBlenderUpdater m_updater;
        fw::AnimEventMotPoseSamper m_sampler;
        // the motions eased in over the state machine, with their names (easeIn/easeOut)
        mm::mtl::FixedVector<anm::Control*, 16> m_easeControls;
        mm::mtl::FixedVector<mm::mtl::FixStr<32>, 16> m_easeNames;
        anm::Control* m_controls[8];  // init's (anm::Factory::createControl)
        float m_playbackTimes[8];  // init's (anm::Util::getPlayBackTime)
        unsigned long m_count;  // how many of m_controls init made
        unsigned int m_current;  // the one playing (playMulti's)
        float m_speed;  // setSpeed's
    };
    // what setup takes (the field names are not the original's)
    struct SetupInfo {
        anm::ResASM* m_res;
        const char* m_state;
        bool m_sampleFlag;
    };

    GfComEvtAnim();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEvtAnim();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    void cleanup();
    void setup(const SetupInfo& info);
    void updateSetup();
    bool execCmd(const char* cmd);
    const char* getStateName() const;
    bool setState(const char* state);
    void setVariable(const char* name, float value);
    void setVariable(const char* name, int value);
    void setLocalTime(float time, AnimLayer layer);
    bool getPlaybackTime(const char* state, float* pTime) const;
    bool getLocomotionReference(const char* state, float time, anm::QsTransform* pOut) const;
    const anm::QsTransform* getLocomotion() const;
    bool isEnd(AnimLayer layer) const;
    bool play(void* data, unsigned long size, float time);
    bool stop();
    void initMulti(void** data, unsigned long* sizes, unsigned long count);
    bool playMulti(unsigned int index, float time);
    bool stopMulti();
    bool isEndMulti() const;
    void setWeightMulti(float* weights, unsigned long count);
    void setSpeed(float speed, AnimLayer layer);
    bool easeIn(const char* name, AnimLayer layer);
    bool easeOut(const char* name, AnimLayer layer);
    bool setEaseWeight(const char* name, AnimLayer layer, float weight);
    bool setEaseSpeed(const char* name, AnimLayer layer, float speed);
    static mm::mtl::RTTI m_rtti;

    Asm m_asm;  // (the name is not the original's)
    Mot m_mot;  // (the name is not the original's)
    anm::ResASM* m_res;  // setup's (its info's)
    mm::mtl::FixStr<32> m_state;  // setup's: the state the state machine starts in
    unsigned int m_setupFlags;  // bit 0: updateSetup found the model and set both halves up
    bool m_sampleFlag;  // setup's; the constructor's true
};
}  // namespace gf

#endif
