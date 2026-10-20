#ifndef CLASSES_GF_PC_PADFIELD_H
#define CLASSES_GF_PC_PADFIELD_H

namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B67E60
class PadField {
public:
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 0
};
}}  // namespace gf::pc

#endif
