#ifndef CLASSES_ML_BASEOBJECTM_H
#define CLASSES_ML_BASEOBJECTM_H

namespace ml {
// table 0x7100B77720
class BaseObjectM {
public:
    virtual ~BaseObjectM();  // slot 0
    virtual void AddRef();  // slot 2
    virtual void Release();  // slot 3
    virtual void SetName(char const*);  // slot 4
    unsigned char pad_8[0xB0];  // fields: size from its derived classes
};
}  // namespace ml

#endif
