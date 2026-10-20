#ifndef CLASSES_GF_SCOM_H
#define CLASSES_GF_SCOM_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B6A8E8
class SCOM {
public:
    virtual ~SCOM();  // slot 0
    virtual void exec(fw::UpdateInfo const&) = 0;  // slot 2
    virtual void getObjHandle() const;  // slot 3
    unsigned char pad_8[0x18];  // fields: size from its derived classes
};
}  // namespace gf

#endif
