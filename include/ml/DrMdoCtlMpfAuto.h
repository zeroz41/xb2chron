#ifndef ML_DRMDOCTLMPFAUTO_H
#define ML_DRMDOCTLMPFAUTO_H

namespace ml { struct _wkMpfAutoBuff; }

namespace ml {
// Placed at 0x48 of DrResMdoSeamWrkMpf's work memory, after DrMdoCtlMpfWork (0x170 bytes, no vtable: its
// constructor stores no table). Field names are not the original's.
class DrMdoCtlMpfAuto {
public:
    void setBuffTbl(_wkMpfAutoBuff** buffTbl, int buffNum);

    unsigned char pad_0[0x60];
    _wkMpfAutoBuff** m_pBuffTbl;  // 0x60
    int m_buffNum;  // 0x68
    unsigned char pad_6C[0x104];
};
}  // namespace ml

#endif
