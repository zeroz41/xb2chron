#ifndef CLASSES_ML_DRRESMDOSEAMTEXTURE_H
#define CLASSES_ML_DRRESMDOSEAMTEXTURE_H

#include "grlib/CGLibTextureBuffer.h"

namespace ml {
class DrResMdoSeamMemObj;

// table 0x7100B7DAA8
// A streamed seam texture: its image lives in a DrResMdoSeamMemObj block. The field and parameter names are not the
// original's.
class DrResMdoSeamTexture {
public:
    DrResMdoSeamTexture(int no);
    virtual ~DrResMdoSeamTexture();  // slot 0
    void release();
    bool update();
    bool updateHeight();
    void createTexture(int size);
    void createHeightMoveTexture(int offset, unsigned int size);
    void resetTexture(int size);
    void changeMemTexture(int size);
    void changeMemTexture(int size, int size2);

    static int SEAMRES_NOM_CNTMAX;
    static int SEAMRES_HEIGHT_CNTMAX;

    DrResMdoSeamTexture* m_prev;          // 0x08: list links, zeroed by the constructor
    DrResMdoSeamTexture* m_next;          // 0x10
    grlib::CGLibTextureBuffer m_texture;  // 0x18
    DrResMdoSeamMemObj* m_memObj;         // 0x88: the image (createTexture)
    DrResMdoSeamMemObj* m_heightMemObj;   // 0x90: the height image (createHeightMoveTexture)
    int m_heightOffset;                   // 0x98
    short m_no;                           // 0x9C: the constructor's argument
    unsigned short pad_9E;                // 0x9E: zeroed by the constructor
    unsigned char m_cnt;                  // 0xA0: frames since created, against SEAMRES_NOM_CNTMAX
    unsigned char m_readIn;               // 0xA1: set by update when the memory block is read in
    unsigned char m_heightCnt;            // 0xA2: against SEAMRES_HEIGHT_CNTMAX
    unsigned char m_heightReady;          // 0xA3: cleared by release and resetTexture
};
}  // namespace ml

#endif
