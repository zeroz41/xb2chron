#ifndef CLASSES_FW_COMMONRESOURCE_H
#define CLASSES_FW_COMMONRESOURCE_H

namespace fw {
// table 0x7100B42980
class CommonResource {
public:
    virtual ~CommonResource();  // slot 0
    virtual void update();  // slot 2
    virtual void valid() const;  // slot 3
    virtual void getAssetName() const;  // slot 4
    unsigned char pad_8[0xC0];  // fields: size from its derived classes
};
}  // namespace fw

#endif
