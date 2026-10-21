#ifndef CLASSES_GF_GFCOMIK_H
#define CLASSES_GF_GFCOMIK_H

#include "mm/mtl/RTTI.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B66300
class GfComIK {
public:
    class FootGround;
    class Ground;
    class ViewerListener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComIK();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
