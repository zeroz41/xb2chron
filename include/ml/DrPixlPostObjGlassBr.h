#ifndef ML_DRPIXLPOSTOBJGLASSBR_H
#define ML_DRPIXLPOSTOBJGLASSBR_H

#include "grlib/CGLibDblUniformBlock.h"
#include "grlib/CGLibRenderTarget.h"
#include "grlib/CGLibVtlMemPool.h"
#include "grlib/CGLibVtxIndex.h"
#include "grlib/CGLibVtxVertex.h"
#include "ml/DrPixlPostObj.h"

namespace ml {

// the glass breakage post object (ScnRenderDrSysParmAcc::setGlassBr turns it on). The field names are not the
// original's.
class DrPixlPostObjGlassBr : public DrPixlPostObj {
public:
    DrPixlPostObjGlassBr(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjGlassBr();
    void setup();
    void render();
    void renderCaputre();
    void renderGlass();

    grlib::CGLibVtxVertex m_vertex;  // 0x18
    grlib::CGLibVtxIndex m_index;  // 0x40
    grlib::CGLibVtlMemPool m_memPool;  // 0x68
    grlib::CGLibRenderTarget m_target;  // 0x98
    grlib::CGLibDblUniformBlock m_uniform;  // 0x460
    unsigned char pad_498[0x48];
    float m_param[4];  // 0x4E0: update hands these to the shader; the constructor clears the first three
    const void* m_pGlassData;  // 0x4F0, setup: DrIniSys::getGlassBreakage
    void* m_pPieceWork;  // 0x4F8, setup allocates 0x40 bytes per piece; the destructor frees it
    unsigned int m_pieceNum;  // 0x500, setup reads it from the glass data
    unsigned char pad_504[0x4];
    unsigned int m_flags;  // 0x508: the constructor and destructor set 3, setup clears 1; render skips while 4 is set
    float m_time;  // 0x50C, update advances it; the constructor clears it
};

}  // namespace ml

#endif
