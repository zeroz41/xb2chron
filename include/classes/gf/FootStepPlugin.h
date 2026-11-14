#ifndef CLASSES_GF_FOOTSTEPPLUGIN_H
#define CLASSES_GF_FOOTSTEPPLUGIN_H

#include "classes/gf/Plugin.h"
#include "gf/GfEnvProperty.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B65718
class FootStepPlugin : public ::gf::Plugin {
public:
    // its index in a behavior's plugins (GfComBehavior::procAsmCallbackCommon reads it from index 0)
    enum { PLUGIN_ID = 0 };
    // the first block of the 25th param list (fw::ParamManager::m_paramLists[24]) that setAnkleHeight and update
    // read (the type and field names are not the original's)
    struct Param {
        float pad_0;  // the run speed in km/h: update sets m_running at or above it
        // the ankle height in centimetres: setAnkleHeight hands it to the effect caster (in metres) and to the
        // sound's "water_th" variable
        unsigned int pad_4;
    };
    FootStepPlugin();
    static Plugin* create();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~FootStepPlugin() {}  // slot 1
    virtual void onActivate();  // slot 3
    virtual void onDeactivate();  // slot 4
    virtual bool onSetup(gf::GfComBehavior& behavior) { return setup(behavior); }  // slot 5
    virtual void onCleanup(gf::GfComBehavior& behavior) { cleanup(behavior); }  // slot 6
    virtual void onUpdate(gf::GfComBehavior& behavior, fw::UpdateInfo const& info) {  // slot 7
        update(behavior, info);
    }
    virtual bool setup(gf::GfComBehavior&);  // slot 8
    virtual void cleanup(gf::GfComBehavior&);  // slot 9
    virtual void update(gf::GfComBehavior&, fw::UpdateInfo const&);  // slot 10
    void setAnkleHeight(gf::GfComBehavior& behavior);
    void notifyStep(gf::GfComBehavior& behavior, const char* name);
    // plays the step sound of the object's foot step kind (GfObjSetup::getFootStep) for the foot on that ground
    void playSe(gf::GfComBehavior& behavior, GfEnvProperty::GROUND_INDEX ground);

    static mm::mtl::RTTI m_rtti;

    // update sets it while the object moves (across x, z) at least as fast as its run speed; steps pass it on
    bool m_running;
};

// the ground of a foot by its name: "right"/"right00" 2, "left"/"left00" 1, "right01" 4, "left01" 3, "right02" 6,
// "left02" 5, any other 0 (FootStepPlugin::notifyStep passes it to playSe)
GfEnvProperty::GROUND_INDEX getFootGroundIndex(const char* name);
}  // namespace gf

#endif
