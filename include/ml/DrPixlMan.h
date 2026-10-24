#ifndef ML_DRPIXLMAN_H
#define ML_DRPIXLMAN_H

#include "grlib/CGLibRenderTarget.h"

namespace grlib { class CGLibTextureBuffer; }
namespace ml { class DrPixlDeferred; }
namespace ml { class DrPixlPostMan; }

namespace ml {
// DrPixlMan::m_objTbl: getPixlObj(i) reads entry i (two pointers per entry, the second double-buffered); the
// entries DrMdoSetup reads by name are below. The type and field names are not the original's.
struct DrPixlObjTbl {
    unsigned char pad_0[0x170];
    DrPixlDeferred* m_deferred;  // 0x170
    unsigned char pad_178[0x8];
    DrPixlPostMan* m_postMan;  // 0x180
};

// DrMan's pixel manager (DrMan::m_pixlMan). Only what DrMdoSetup's texture callbacks read is known; the field
// names are not the original's. The capture and movie fields are read by DrMdoSetup::varStTex_Capture*/Movie*.
class DrPixlMan {
public:
    grlib::CGLibRenderTarget* getPixlObj(int index);
    grlib::CGLibTextureBuffer* getDammyTexObj();       // reads m_dammyObj's texture
    grlib::CGLibTextureBuffer* getDammyWhiteTexObj();  // reads m_dammyWhiteObj's texture
    grlib::CGLibRenderTarget* getBackFaceDepthTexture();
    grlib::CGLibRenderTarget* getDiffIBLObj();

    unsigned char pad_0[0x1E0];
    grlib::CGLibRenderTarget* m_captureMain;  // 0x1E0
    unsigned char pad_1E8[0x1F0];
    grlib::CGLibRenderTarget* m_capture1;  // 0x3D8
    unsigned char pad_3E0[0x1F0];
    grlib::CGLibRenderTarget* m_capture2;  // 0x5D0
    unsigned char pad_5D8[0x1F0];
    grlib::CGLibRenderTarget* m_capture3;  // 0x7C8
    unsigned char pad_7D0[0x20];
    DrPixlObjTbl* m_objTbl;  // 0x7F0
    unsigned char pad_7F8[0x10];
    grlib::CGLibTextureBuffer* m_movieTex[4];  // 0x808
    bool m_movieFilter[4];  // 0x828, true: varStTex_Movie* sample with filter mode 1, else 0
    grlib::CGLibRenderTarget* m_dammyObj;  // 0x830, getDammyTexObj
    grlib::CGLibRenderTarget* m_dammyWhiteObj;  // 0x838, getDammyWhiteTexObj
    unsigned char pad_840[0x180];
    grlib::CGLibRenderTarget* m_capture4;  // 0x9C0
};
}  // namespace ml

#endif
