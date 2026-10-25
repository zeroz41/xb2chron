#ifndef GF_GFDATANANAKOORI_H
#define GF_GFDATANANAKOORI_H

namespace gf {
// (functions, by their symbols)
class GfDataNanakoori {
public:
    static bool isMissionComplete(unsigned int mission);
    static void setMissionComplete(unsigned int mission);
    static unsigned int getVocalLevel();
    static unsigned int getVisualLevel();
    static unsigned int getSoulLevel();
    static unsigned int getItemForVocalLevelUp();
    static unsigned int getItemForVisualLevelUp();
    static unsigned int getItemForSoulLevelUp();
    static void setVocalLevel(unsigned int level);
    static void setVisualLevel(unsigned int level);
    static void setSoulLevel(unsigned int level);
    static unsigned int getLevelForNanakoori(unsigned int count);  // the level an item count gives
    static unsigned int getClearMissionForSpecial();
    static unsigned int getClearMissionForLive();
    static unsigned int getClearMissionForLesson();
    static void setFan(unsigned int fan);
};
}  // namespace gf

#endif
