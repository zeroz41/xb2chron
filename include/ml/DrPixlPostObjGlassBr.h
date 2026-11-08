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
    // the head of DrIniSys::getGlassBreakage's data as setup reads it (the type and field names are not the
    // original's)
    struct GlassData {
        unsigned char pad_0[0xC];
        unsigned int m_pieceNum;  // 0xC
        unsigned int m_bufferOfs;  // 0x10: m_memPool's buffer starts this far into the data
        unsigned int m_bufferSize;  // 0x14
        unsigned int m_vertexOfs;  // 0x18: m_vertex's offset and size in the pool
        unsigned int m_vertexSize;  // 0x1C
        unsigned char pad_20[0x4];
        unsigned int m_indexOfs;  // 0x24: m_index's offset and count in the pool
        unsigned char pad_28[0x4];
        unsigned int m_indexCount;  // 0x2C
    };

    DrPixlPostObjGlassBr(DrMan* drMan, DrPixlMan* pixlMan, DrPixlPostMan* postMan);
    ~DrPixlPostObjGlassBr();
    void setup();
    void posInt();
    void render();
    void renderCaputre();
    void renderGlass();
    void update();

    grlib::CGLibVtxVertex m_vertex;  // 0x18
    grlib::CGLibVtxIndex m_index;  // 0x40
    grlib::CGLibVtlMemPool m_memPool;  // 0x68
    grlib::CGLibRenderTarget m_target;  // 0x98
    grlib::CGLibDblUniformBlock m_uniform;  // 0x460
    unsigned char pad_498[0x48];
    float m_param[4];  // 0x4E0: update hands these to the shader; the constructor clears the first three
    const GlassData* m_pGlassData;  // 0x4F0, setup: DrIniSys::getGlassBreakage
    void* m_pPieceWork;  // 0x4F8, setup allocates 0x40 bytes per piece; the destructor frees it
    unsigned int m_pieceNum;  // 0x500, setup reads it from the glass data
    unsigned char pad_504[0x4];
    unsigned int m_flags;  // 0x508: the constructor and destructor set 3, setup clears 1; render skips while 4 is set
    float m_time;  // 0x50C, update advances it; the constructor clears it
};

}  // namespace ml

#endif
