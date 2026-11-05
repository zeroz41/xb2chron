#ifndef ML_DRINISYS_H
#define ML_DRINISYS_H

#include "grlib/CGLibTextureBuffer.h"
#include "ml/DrPixlPostParm.h"
#include "mm/mtl/FixStr.h"

namespace csvb { class CCsvbData; }
namespace ml { class ScnObjModel; }

namespace ml {
class FileResTh;
class DrMan;

// DrMan's (DrMan::DrMan makes it, 0x1BA0 bytes)
class DrIniSys {
public:
    // what getWetnessSetting reads from a wetness_param row (DrEnvColiParameter::calcParams asks for it; the field
    // names are not the original's)
    struct WetSetting {
        bool m_enable;  // column 0 == 1
        int m_param1;   // column 1
        int m_param2;   // column 2
        float m_value;  // column 3, else the default at 0x1A0C
    };

    // releases every texture's resource, the other resources and the wetness table (the destructor calls it)
    void dataWorkClear();
    DrIniSys(DrMan* drMan);
    ~DrIniSys();
    void getWetnessSetting(unsigned short row, WetSetting& setting) const;
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
    // reads /monolib/shader/mirror_ball.wimdo and makes the scene model from it (the previous one is set to delete)
    void loadMirrorBallModel();
    // mode 1: reads lib_dlc_nx.ini's s_pAttrDlcTbl keys; else takes m_dlcIniValue (the parameter name is inferred)
    void setupDlcIni(int mode);

    // the keys setupDlcIni reads from lib_dlc_nx.ini (2.0.0's symbols name it)
    static const char* s_pAttrDlcTbl[1];

    DrMan* m_pDrMan;  // 0x0 (the name is not the original's)
    // 0x8: the file each m_texture was made from; the load functions release it before reading again (the name is
    // not the original's)
    FileResTh* m_texRes[18];
    // 0x98, the constructor constructs 18 textures; DrMdoSetup::varStTex_VolumeTex00 indexes them (the name is not
    // the original's). Bound by DrMdoSetup: [1] dither, [3] ambient BRDF, [6] toon rim, [7] volume, [12] specular
    // IBL fallback, [15] orientation, [16]/[17] flag wave.
    grlib::CGLibTextureBuffer m_texture[18];
    // 0x878: loadMirrorBallModel's model resource (the name is not the original's)
    FileResTh* m_mirrorBallRes;
    // 0x880: the model loadMirrorBallModel makes from m_mirrorBallRes (the name is not the original's)
    ScnObjModel* m_mirrorBall;
    bool m_active;  // 0x888, the constructor sets it; no reader is known (the name is not the original's)
    unsigned char pad_889[0x7];
    FileResTh* m_camLight;  // 0x890, loadCameraLight's night_light.wilgt (the name is not the original's)
    // 0x898: the glass breakage resource loadGlassBreakage reads (the name is not the original's)
    FileResTh* m_glassBreakage;
    FileResTh* m_filterLut;  // 0x8A0, loadFilterLutTexture's filterlut file (the name is not the original's)
    unsigned char pad_8A8[0xC8];
    // 0x970: the constructor constructs it; ScnRenderDrSysParmAcc::setMotBlurDefault and getWetnessSetting use it
    // (the name is not the original's)
    DrPixlPostParm m_postParm;
    // 0x1A80: the path loadIBLEnvTexture reads; the constructor formats the dummy cube map's path into it (the name
    // is not the original's)
    mm::mtl::FixStr<256> m_iblEnvPath;
    // 0x1B88: the wetness_param table getWetnessSetting reads; dataWorkClear deletes it (the name is not the
    // original's)
    csvb::CCsvbData* m_wetnessCsv;
    // 0x1B90: the constructor sets 0.5; setupDlcIni passes it on outside DLC mode, else the DLC ini's value (the
    // name is not the original's)
    float m_dlcIniValue;
    unsigned char pad_1B94[0xC];
};
}  // namespace ml

#endif
