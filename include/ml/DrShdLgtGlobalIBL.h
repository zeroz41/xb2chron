#ifndef ML_DRSHDLGTGLOBALIBL_H
#define ML_DRSHDLGTGLOBALIBL_H

namespace ml {
class DrMan;
// The global IBL light (DrShdLgtMan::m_pGlobalIBL). Only what DrMan::isIBLSkip/isTemporalUPSToGlobalIBL call is
// declared so far.
class DrShdLgtGlobalIBL {
public:
    DrShdLgtGlobalIBL(DrMan* drMan);
    ~DrShdLgtGlobalIBL();
    void update(int viewIdx);
    void delViewInfo(int viewIdx);
    void resetColorBuff(int viewIdx);

    unsigned char pad_0[0x8190];  // the size DrShdLgtMan's constructor allocates
    bool isEnable() const;
};
}  // namespace ml

#endif
