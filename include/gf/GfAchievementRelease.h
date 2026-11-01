#ifndef GF_GFACHIEVEMENTRELEASE_H
#define GF_GFACHIEVEMENTRELEASE_H

namespace gf { enum ACHIEVEMENT_TYPE : int; }

namespace gf {
// no table: what GfEvent::callAchievmentRelease hands on when an affinity chart node is released
// (GfGameUtil::setAchievementReleaseLevel builds it; the field names are not the original's)
class GfAchievementRelease {
public:
    unsigned short m_blade;
    unsigned short m_level;
    ACHIEVEMENT_TYPE m_type;
};
}  // namespace gf

#endif
