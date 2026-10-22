#ifndef CLASSES_GF_GFCOMENVSENSOR_H
#define CLASSES_GF_GFCOMENVSENSOR_H

#include "mm/mtl/RTTI.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B66108
class GfComEnvSensor {
public:
    class EnvListener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEnvSensor();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
