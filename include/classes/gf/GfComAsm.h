#ifndef CLASSES_GF_GFCOMASM_H
#define CLASSES_GF_GFCOMASM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComAnimation.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class CallBackCache; }

namespace gf {
// which animation layer of an object's state machines (GfComAsm's functions ignore one past 6); LipSyncPlugin
// plays its lip animation on 4 (the name is not the original's); the code otherwise passes 0
enum AnimLayer : int {
    ANIM_LAYER_LIP = 4,
};

// which of an object's animation attributes GfComAsm::getAttribute reads; GfComDynamics::applyAttribute and
// FootIkControllerPlugin ask for 0 (no value has a name yet)
enum AsmCategory : int {};

// table 0x7100B65540; its constructor builds a GfComAnimation first
class GfComAsm : public ::gf::GfComAnimation {
public:
    class AsmLisener;
    class ViewerListener;
    // a receiver of animation events: executeCallback hands an event to the one whose name it carries
    struct CallBack {
        const char* name;
        mm::mtl::Delegate<void(GfComAsm*, const CallBackCache&)> delegate;
    };
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComAsm();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
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
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_10[0x60];
    // executeCallback's: the first takes the events no other one's name matches
    CallBack m_callbacks[5];
    unsigned char pad_138[0x50];
};
}  // namespace gf

#endif
