#ifndef CLASSES_GF_PC_GFPROPERTYBATTLE_H
#define CLASSES_GF_PC_GFPROPERTYBATTLE_H

#include "classes/gf/pc/GfPropertyPcInterface.h"

namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B66B50
class GfPropertyBattle : public ::gf::pc::GfPropertyPcInterface {
public:
    virtual void setup(gf::GfComPropertyPc const&);  // slot 0
    virtual void cleanup(gf::GfComPropertyPc const&);  // slot 1
    virtual void flush(gf::GfComPropertyPc const&);  // slot 2
};
}}  // namespace gf::pc

#endif
