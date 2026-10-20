#ifndef CLASSES_GF_GFCOMENVSENSOR_H
#define CLASSES_GF_GFCOMENVSENSOR_H

namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B66108
class GfComEnvSensor {
public:
    class EnvListener;
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComEnvSensor();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
};
}  // namespace gf

#endif
