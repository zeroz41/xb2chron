#ifndef CLASSES_GF_GFCOMBEHAVIOR_H
#define CLASSES_GF_GFCOMBEHAVIOR_H

#include "classes/gf/GfComponent.h"

namespace fw { class UpdateInfo; }
namespace gf { class CallBackCache; }
namespace gf { class GfComAsm; }

namespace gf {
// table 0x7100B65EE0
class GfComBehavior : public ::gf::GfComponent {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfComBehavior();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 5
    virtual void procAnimCallback(gf::GfComAsm*, gf::CallBackCache const&);  // slot 6
    unsigned char pad_10[0x88];  // fields: size from its derived classes
};
}  // namespace gf

#endif
