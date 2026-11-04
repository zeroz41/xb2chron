#ifndef FW_RENDERPARAM_H
#define FW_RENDERPARAM_H

namespace mm { class Vec3; }

namespace fw {
// the camera (view) a render setting is for: it is the view index ml::ScnRenderDrSysParmAcc and
// ml::ScnRenderDrEnvColi take
enum CAMERA_TYPE : int;

// the game's access to the scene renderer's settings: each builds an ml::ScnRenderDrSysParmAcc on the Framework's
// scene renderer for a view and hands it on (no table; the parameter names are not the original's)
class RenderParam {
public:
    static void initialize();
    static void finalize();
    static void setPlayerPosition(const mm::Vec3& pos, CAMERA_TYPE type);
    // whether pos is in a room of the environment collision
    static bool isRoom(const mm::Vec3& pos, CAMERA_TYPE type);
    static void setMotionBlur(bool enable, CAMERA_TYPE type);
    // the time of day from hours and minutes
    static void setTime(unsigned int hour, unsigned int minute, CAMERA_TYPE type);
    // the weather, changing over sec seconds (ml::ScnRenderDrSysParmAcc::setWeatherFrame gets sec over
    // ml::DevGraph::getFrameSyncSec); 2.0.0's symbols spell the float
    static void setWeather(unsigned int weather, float sec, CAMERA_TYPE type);
    static int getWindIndex(CAMERA_TYPE type);
    static void setGlobalWindPower(const mm::Vec3& power, CAMERA_TYPE type);
    static void setColorFilter(int num, int farNum, float time, CAMERA_TYPE type);
    static void resetColorFilter(float time, CAMERA_TYPE type);
    static void setCloudSea(unsigned int num);
    static void resetScene();
    // 2.0.0's symbols name it. It takes no object (it sits among RenderParam's, after finalize). What it does:
    // whether the seam map is read (ml::ScnRenderDrSysParmAcc::isSeamMapRead for view 0 of the Framework's scene
    // renderer).
    static bool isSeamMapRead();
    // 2.0.0's symbols name it. It takes no object, and it sits at the start of CommonResource.cpp's split (1.0.0's
    // CommonResource.o starts at search; its code is RenderParam's pattern, so it likely ends the unit before). What
    // it does: builds an ml::ScnRenderDrSysParmAcc for view 0 of the Framework's scene renderer and hands the flag
    // to its setRenderTexMode (DrMan's word at 0x1D50). Called by gf::GfManager::initialize and resetGameType.
    static void setRenderTypeDlc(bool flag);
};
}  // namespace fw

#endif
