#ifndef CLASSES_GF_GFCOMEVTANIM_H
#define CLASSES_GF_GFCOMEVTANIM_H

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B655A8
class GfComEvtAnim {
public:
    class Asm;
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComEvtAnim();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
};
}  // namespace gf

#endif
