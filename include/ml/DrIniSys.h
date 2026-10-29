#ifndef ML_DRINISYS_H
#define ML_DRINISYS_H

#include "grlib/CGLibTextureBuffer.h"

namespace ml {
class FileResTh;
class DrMan;

// DrMan's (DrMan::DrMan makes it, 0x1BA0 bytes)
class DrIniSys {
public:
    // the data of the resource loadGlassBreakage read
    const void* getGlassBreakage() const;
    // reads /monolib/shader/<name>.witex (the scene's entry resource, else a FileResTh of its own)
    FileResTh* readTextureMapFile(const char* name);
    void loadRainDropTexture();
    void loadToonGradTexture();
    void loadIBLEnvTexture();
    void loadGlassBreakage();
    void loadCameraLight();
    void loadFlagWaveTexture();
    void loadFilterLutTexture();

    DrMan* m_pDrMan;  // 0x0 (the name is not the original's)
    // 0x8: the file each m_texture was made from; the load functions release it before reading again (the name is
    // not the original's)
    FileResTh* m_texRes[18];
    // 0x98, the constructor constructs 18 textures; DrMdoSetup::varStTex_VolumeTex00 indexes them (the name is not
    // the original's). Bound by DrMdoSetup: [1] dither, [3] ambient BRDF, [6] toon rim, [7] volume, [12] specular
    // IBL fallback, [15] orientation, [16]/[17] flag wave.
    grlib::CGLibTextureBuffer m_texture[18];
    unsigned char pad_878[0x18];
    FileResTh* m_camLight;  // 0x890, loadCameraLight's night_light.wilgt (the name is not the original's)
    // 0x898: the glass breakage resource loadGlassBreakage reads (the name is not the original's)
    FileResTh* m_glassBreakage;
    FileResTh* m_filterLut;  // 0x8A0, loadFilterLutTexture's filterlut file (the name is not the original's)
    unsigned char pad_8A8[0x2C4];
    bool m_motBlurDefault;  // ScnRenderDrSysParmAcc::setMotBlurDefault writes it (the name is not the original's)
    unsigned char pad_B6D[0xF13];
    // 0x1A80: the path loadIBLEnvTexture reads (the name is not the original's; its length is not known, it runs to
    // the end of the class here)
    char m_iblEnvPath[0x120];
};
}  // namespace ml

#endif
