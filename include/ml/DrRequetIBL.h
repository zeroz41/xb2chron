#ifndef ML_DRREQUETIBL_H
#define ML_DRREQUETIBL_H

#include "ml/DrLightObjGlobalIBL.h"

namespace ml {
// An IBL request (0x30 bytes): DrShdLgtGlobalIBL::updateView builds one on the stack and hands it to
// DrPixlPostObjCubeMapMultiIBL::requestIBL, which copies it into its ring; cancelIBL finds entries by m_id. The getters
// read the requested light. Field names are not the original's.
class DrRequetIBL {
public:
    explicit DrRequetIBL(DrLightObjGlobalIBL* ibl);

    unsigned int getTextureNum() const;
    const grlib::CGLibTextureBuffer* getTexture(unsigned int index) const;
    const mm::Mat44* getSHMatrix(unsigned int index, unsigned int term) const;
    float getSkyIntensity() const;
    float getDirLightIntensity() const;
    const mm::Vec3* getAdditionalAmbient() const;
    unsigned int getVersion() const;

    unsigned char pad_0[0x18];  // updateView fills 0x0, 0x8 and 0x10
    DrLightObjGlobalIBL* m_pIBL;  // 0x18
    unsigned long m_id;  // 0x20, cancelIBL's key
    unsigned char* m_pState;  // 0x28, requestIBL sets 1, cancelIBL 3
};
}  // namespace ml

#endif
