#ifndef ML_IRRVOL_DRIRRVOLCASCADE_H
#define ML_IRRVOL_DRIRRVOLCASCADE_H

#include "grlib/CGLibTextureBuffer.h"

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

// The cascade's resource manager (1.0.0 name); the cascade deletes it through its table (slot 1, D0). Only the
// destructor is declared.
class DrIrrVolResMan {
public:
    virtual ~DrIrrVolResMan();  // slot 0
};

// One cascade of the irradiance volume (0x900 bytes: 1.0.0's DrIrrVolMan::createResources allocates so). Only the
// destructor is declared.
class DrIrrVolCascade {
public:
    // one of the 81 blocks the destructor deletes (trivially destructible; the name is not the original's)
    struct Block {};

    enum { BLOCK_NUM = 81 };

    ~DrIrrVolCascade();

    unsigned char pad_0[0x18];
    DrIrrVolResMan* m_resMan;  // 0x18, deleted by the destructor (the name is not the original's)
    Block* m_blocks[BLOCK_NUM];  // 0x20, deleted by the destructor (the name is not the original's)
    unsigned long m_blockInfo[BLOCK_NUM];  // 0x2A8, zeroed by the destructor (the name is not the original's)
    unsigned char pad_530[0xB8];
    grlib::CGLibTextureBuffer m_textures[6];  // 0x5E8 (the name is not the original's)
    unsigned char pad_888[0x78];
};
}}  // namespace ml::irrvol

#endif
