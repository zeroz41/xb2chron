#ifndef CLASSES_GF_GFFIELDMAPSE_H
#define CLASSES_GF_GFFIELDMAPSE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfFieldMapSe; class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B521E8
class GfFieldMapSe : public ::mm::mtl::PtrSingleton< ::gf::GfFieldMapSe> {
public:
    class SEOBJ;
    GfFieldMapSe();  // GfFieldSound::initialize creates it
    virtual ~GfFieldMapSe();  // slot 0
    // GfFieldSound's forwards (its update, postUpdate, clear and gev* functions call them)
    void update(const fw::UpdateInfo& info);
    void postUpdate(const fw::UpdateInfo& info);
    void destroy();
    void gevGameMapModel(GF_OBJ_HANDLE* handle, bool flag);
    void gevPause(unsigned int flags0, unsigned int flags1);

    // not mapped yet: GfFieldSound::initialize allocates 0x1150 bytes for it (clear's inline loop reads a vector of
    // SE data pointers at +0x10 with its count at +0x110, and a bitmap at +0x1138)
    unsigned char pad_8[0x1148];
};
}  // namespace gf

#endif
