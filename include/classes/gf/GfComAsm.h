#ifndef CLASSES_GF_GFCOMASM_H
#define CLASSES_GF_GFCOMASM_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/Delegate.h"
#include "classes/gf/GfComAnimation.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class CallBackCache; }

namespace gf {
// which animation layer (the names are unknown; the code passes 0)
enum AnimLayer : int {};

// table 0x7100B65540
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
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_10[0x60];
    // executeCallback's: the first takes the events no other one's name matches
    CallBack m_callbacks[5];
    unsigned char pad_138[0x50];
};
}  // namespace gf

#endif
