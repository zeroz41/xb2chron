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
};
}  // namespace gf

#endif
