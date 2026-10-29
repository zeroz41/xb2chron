#ifndef ML_DRINISYS_H
#define ML_DRINISYS_H

#include "grlib/CGLibTextureBuffer.h"

namespace ml {
class FileResTh;

// DrMan's (DrMan::DrMan makes it, 0x1BA0 bytes)
class DrIniSys {
public:
    // the data of the resource loadGlassBreakage read
    const void* getGlassBreakage() const;

    unsigned char pad_0[0x98];
    // 0x98, the constructor constructs 18 textures; DrMdoSetup::varStTex_VolumeTex00 indexes them (the name is not
    // the original's). Bound by DrMdoSetup: [1] dither, [3] ambient BRDF, [6] toon rim, [7] volume, [12] specular
    // IBL fallback, [15] orientation, [16]/[17] flag wave.
    grlib::CGLibTextureBuffer m_texture[18];
    unsigned char pad_878[0x20];
    // 0x898: the glass breakage resource loadGlassBreakage reads (the name is not the original's)
    FileResTh* m_glassBreakage;
    unsigned char pad_8A0[0x2CC];
    bool m_motBlurDefault;  // ScnRenderDrSysParmAcc::setMotBlurDefault writes it (the name is not the original's)
    unsigned char pad_B6D[0x1033];
};
}  // namespace ml

#endif
