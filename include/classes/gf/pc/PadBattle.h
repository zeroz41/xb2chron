#ifndef CLASSES_GF_PC_PADBATTLE_H
#define CLASSES_GF_PC_PADBATTLE_H

namespace fw { class UpdateInfo; }
namespace gf { class GfComPropertyPc; }

namespace gf { namespace pc {
// table 0x7100B66B38
class PadBattle {
public:
    virtual void update(fw::UpdateInfo const&, gf::GfComPropertyPc&);  // slot 0
};
}}  // namespace gf::pc

#endif
