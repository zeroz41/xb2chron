#ifndef ML_IRRVOL_DRIRRVOLCASCADE_H
#define ML_IRRVOL_DRIRRVOLCASCADE_H

namespace mm { class Mat44; }

namespace ml { namespace irrvol {
// The irradiance matrix of 9 spherical harmonics coefficients (Ramamoorthi-Hanrahan constants); called by
// DrLightObjGlobalIBL::initializeFromBuffer and DrLightObjLocalIBL::setup.
void convertSHMatrix(mm::Mat44& mtx, const float* sh);

// The irradiance volume's settings (1.0.0's DrIrrVolCascade constructor takes them as const SGlobalInfo*). Only what
// DrIrrVolMan reads is declared; the field names are not the original's.
struct SGlobalInfo {
    unsigned char pad_0[0x20];
    unsigned int m_cascadeNum;  // 0x20, DrIrrVolMan makes one DrIrrVolCascade each (1.0.0 createResources)
};

// One cascade of the irradiance volume (0x900 bytes: 1.0.0's DrIrrVolMan::createResources allocates so). Only the
// destructor is declared.
class DrIrrVolCascade {
public:
    ~DrIrrVolCascade();

    unsigned char pad_0[0x900];
};
}}  // namespace ml::irrvol

#endif
