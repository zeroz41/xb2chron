#ifndef ML_DRMDOCTLMPFINST_H
#define ML_DRMDOCTLMPFINST_H

namespace ml {
// The instanced mpf part of a model control (its constructor is empty: no table). Field and type names are not
// the original's.
class DrMdoCtlMpfInst {
public:
    // the head of the instanced mpf resource setupInstMpf takes: its instance data sits m_instOfs bytes from it
    struct ResHeader {
        unsigned char pad_0[0x4];
        unsigned int m_instOfs;  // 0x4
    };

    DrMdoCtlMpfInst();
    void setupInstMpf(const unsigned char* data);

    const unsigned char* m_pInstData;  // 0x0
};
}  // namespace ml

#endif
