#ifndef CLASSES_GF_PC_PADAGENT_H
#define CLASSES_GF_PC_PADAGENT_H

#include "classes/gf/pc/Agent.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B694E8
class PadAgent : public ::gf::pc::Agent {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~PadAgent();  // slot 1
    virtual void setup(gf::GfComPropertyPc&);  // slot 3
    virtual void cleanup(gf::GfComPropertyPc&);  // slot 4
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 5
};
}}  // namespace gf::pc

#endif
