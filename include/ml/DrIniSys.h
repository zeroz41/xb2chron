#ifndef ML_DRINISYS_H
#define ML_DRINISYS_H

namespace ml {
// DrMan's (DrMan::DrMan makes it, 0x1BA0 bytes)
class DrIniSys {
public:
    unsigned char pad_0[0xB6C];
    bool m_motBlurDefault;  // ScnRenderDrSysParmAcc::setMotBlurDefault writes it (the name is not the original's)
    unsigned char pad_B6D[0x1033];
};
}  // namespace ml

#endif
