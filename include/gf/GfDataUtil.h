#ifndef GF_GFDATAUTIL_H
#define GF_GFDATAUTIL_H

namespace gf {
// the game data's helpers (functions, by its symbols)
class GfDataUtil {
public:
    static int getMoney();
    static int getObjTypeByCharaId(unsigned int chara);  // the object type of a character
    static void setScenarioFlag(unsigned short flag);
    static void setRandomInn();  // picks one of 16 inns at random (the comment is not the original's)
    static void setMoney(unsigned int value);
    static unsigned int getEventChapterSave();
    // GfPlayComMenuChapterSave::start passes its id and GfDataBlade::fn_7100231884()
    static void setChapterSave(unsigned int id, unsigned short value);
    static unsigned int getSkipTravelID();
    static float getPlayerCameraDistance();
    static void setPlayerCameraDistance(float value);
    static unsigned int getCoin();
    static void setCoin(unsigned int value);
    static float getCameraHeight();
    static void setCameraHeight(float value);
    static float getCameraYaw();
    static void setCameraYaw(float value);
    static float getCameraPitch();
    static void setCameraPitch(float value);
    static bool isCameraFreeMode();
    static void setCameraFreeMode(bool value);
    static unsigned int getAutoEventAfterLoad();
    static bool isCollectFlagNewVersion();
    static unsigned char getCameraSide();
    static void setCameraSide(unsigned char value);
    static void convertNewCollectFlagPatch();
    static const char* getAttributeFileName(unsigned int attribute);
};
}  // namespace gf

#endif
