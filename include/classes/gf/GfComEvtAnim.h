#ifndef CLASSES_GF_GFCOMEVTANIM_H
#define CLASSES_GF_GFCOMEVTANIM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComponent.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class CallBackCache; }

namespace gf {
// table 0x7100B655A8
class GfComEvtAnim : public ::gf::GfComponent {
public:
    class Asm;
    // the receiver of its animation events, as GfComAsm::CallBack (GfComSound::setup stores its name and delegate;
    // the names are not the original's)
    struct CallBack {
        const char* name;
        mm::mtl::Delegate<void(GfComEvtAnim*, const CallBackCache&)> delegate;
    };
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEvtAnim();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_10[0x110];
    CallBack m_callback;  // (the name is not the original's)
};
}  // namespace gf

#endif
