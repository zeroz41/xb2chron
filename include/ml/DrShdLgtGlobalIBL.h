#ifndef ML_DRSHDLGTGLOBALIBL_H
#define ML_DRSHDLGTGLOBALIBL_H

namespace ml {
// The global IBL light (DrShdLgtMan::m_pGlobalIBL). Only what DrMan::isIBLSkip/isTemporalUPSToGlobalIBL call is
// declared so far.
class DrShdLgtGlobalIBL {
public:
    bool isEnable() const;
};
}  // namespace ml

#endif
