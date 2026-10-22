#ifndef CLASSES_GF_GFCOMPACKANIM_H
#define CLASSES_GF_GFCOMPACKANIM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/FixedVector.h"
#include "classes/anm/Control.h"
#include "classes/fw/AnimControlUpdater.h"
#include "classes/fw/AnimSinglePoseSamper.h"
#include "classes/gf/GfComAnimation.h"

namespace arc { class CArcData; }
namespace gf { class GfComModel; }

namespace gf {
// table 0x7100B65610: plays an animation found by name in the archives it was set up with on the model
// component's pose
class GfComPackAnim : public ::gf::GfComAnimation {
public:
    // one animation played on a model's pose (1.0.0's names; its constructor, setup, cleanup, isPlayEnd and
    // setSpeed are inline in 3.0.1)
    class Mot {
    public:
        Mot() : m_model(nullptr), m_control(nullptr), m_playBackTime(0.0f) {}
        void setup(GfComModel* model, unsigned int layer) { m_model = model; }
        void cleanup(unsigned int layer) { stop(layer); }
        void stop(unsigned int layer);
        void play(unsigned int layer, void* data, bool sampleFlag);
        bool isPlayEnd() const {
            if (m_control == nullptr) {
                return true;
            }
            return m_playBackTime <= m_control->m_localTime;
        }
        void setSpeed(float speed) {
            if (m_control != nullptr) {
                m_control->m_speed = speed;
            }
        }

        GfComModel* m_model;  // setup's
        anm::Control* m_control;  // play's: the control it created; stop releases it
        fw::AnimControlUpdater m_updater;
        fw::AnimSinglePoseSamper m_sampler;
        float m_playBackTime;  // the animation's length (anm::Util::getPlayBackTime); stop clears it
    };
    // what setup takes (the field names are not the original's)
    struct SetupInfo {
        mm::mtl::FixedVector<void*, 8> m_archives;  // archive binaries (none skipped)
        const char* m_name;  // the animation to play: "<name>.anm" in one of them
        bool m_sampleFlag;  // the samplers' flag (fw::AnimSinglePoseSamper::m_sampleFlag)
    };

    GfComPackAnim();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComPackAnim();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    void cleanup();
    void setup(const SetupInfo& info);
    void play(const char* name);
    void play(void* data);
    bool isPlayEnd() const;
    void setSpeed(float speed);
    static mm::mtl::RTTI m_rtti;

    Mot m_mot;
    mm::mtl::FixedVector<arc::CArcData*, 8> m_archives;  // setup's, from the setup info's binaries
    bool m_sampleFlag;  // true until setup sets it (the name is not the original's)
};
}  // namespace gf

#endif
