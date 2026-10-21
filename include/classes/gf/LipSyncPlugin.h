#ifndef CLASSES_GF_LIPSYNCPLUGIN_H
#define CLASSES_GF_LIPSYNCPLUGIN_H

#include "classes/gf/Plugin.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B658D0
class LipSyncPlugin : public ::gf::Plugin {
public:
    LipSyncPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~LipSyncPlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual void onSetup(gf::GfComBehavior& behavior) { setup(behavior); }  // slot 5
    virtual void onCleanup(gf::GfComBehavior& behavior) { cleanup(behavior); }  // slot 6
    virtual void onUpdate(gf::GfComBehavior& behavior, fw::UpdateInfo const& info) {  // slot 7
        update(behavior, info);
    }
    virtual bool setup(gf::GfComBehavior&);  // slot 8
    virtual void cleanup(gf::GfComBehavior&);  // slot 9
    virtual void update(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 10
    void setSpeed(float speed);
    void setWeight(float weight);

    static mm::mtl::RTTI m_rtti;

    gf::GfComBehavior* m_behavior;  // the behavior setup was given
    float m_speed;                  // setSpeed's: the lip animation's speed
    float m_weight;                 // setWeight's: the lip animation's weight
    bool m_isPlaying;               // whether update has eased the lip animation in
    bool m_forcePlay;               // update plays the lip animation while it is set, voice or not
};
}  // namespace gf

#endif
