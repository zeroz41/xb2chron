#ifndef CLASSES_GF_EYEBLINKPLUGIN_H
#define CLASSES_GF_EYEBLINKPLUGIN_H

#include "classes/fw/ParamList.h"
#include "classes/gf/Plugin.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComBehavior; }

namespace gf {
// table 0x7100B65648: blinks the eyes through the asm component's "S_eye_close" state on layer 3, now and then
// twice
class EyeBlinkPlugin : public ::gf::Plugin {
public:
    // where a blink is (1.0.0's type name; the value names are not the original's)
    enum Mode {
        MODE_WAIT = 0,          // open, waiting out the interval to the next blink
        MODE_CLOSE = 1,         // closing (easeIn)
        MODE_OPEN = 2,          // opening (easeOut)
        MODE_CLOSE_DOUBLE = 3,  // closing again for a double blink
        MODE_OPEN_DOUBLE = 4,   // opening again
    };
    // its parameter block: entry 0 of the param manager's list 11 (the names are not the original's)
    struct Param {
        float m_intervalMin;  // the wait between blinks is a random blend of the two
        float m_intervalMax;
        float m_closeTime;    // the easeIn's time
        float m_openTime;     // the easeOut's time, and the opening's
        float m_closedTime;   // added to the close time: how long a closing lasts
        float m_doubleRate;   // the chance a blink is followed by a second one
    };

    static Plugin* create();
    EyeBlinkPlugin();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~EyeBlinkPlugin() {}  // slot 1
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
    // 1.0.0 has them out of line; 3.0.1 keeps no copy (inline, defined in its unit)
    void setMode(Mode mode);
    void resetTimer();
    const Param* getParameter() const;
    bool testDouble();

    static mm::mtl::RTTI m_rtti;

    gf::GfComBehavior* m_behavior;              // the behavior setup was given
    float m_timer;                              // the time left in the current mode
    Mode m_mode;                                // setMode's
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // setup takes the param manager's list 11
};
}  // namespace gf

#endif
