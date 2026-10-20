#ifndef CLASSES_GF_SCOM_OBJ_VFADE_H
#define CLASSES_GF_SCOM_OBJ_VFADE_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6A9B0
class SCOM_OBJ_VFADE {
public:
    virtual ~SCOM_OBJ_VFADE();  // slot 0
    virtual void exec(fw::UpdateInfo const&);  // slot 2
    virtual void getObjHandle() const;  // slot 3
};
}  // namespace gf

#endif
