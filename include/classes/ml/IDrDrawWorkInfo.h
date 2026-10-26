#ifndef CLASSES_ML_IDRDRAWWORKINFO_H
#define CLASSES_ML_IDRDRAWWORKINFO_H

namespace ml {
// what ml's draw system hands each IDrDrawCallback stage; only what the code reads is named
class IDrDrawWorkInfo {
public:
    unsigned char pad_0[0x560];
    // layer::LayerManager's apply and finalRender draw only when it is 0 (the name is not the original's)
    int m_subPass;
};
}  // namespace ml

#endif
