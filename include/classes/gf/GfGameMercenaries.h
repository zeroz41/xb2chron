#ifndef CLASSES_GF_GFGAMEMERCENARIES_H
#define CLASSES_GF_GFGAMEMERCENARIES_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameMercenaries; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {
// table 0x7100B56D30
class GfGameMercenaries : public ::mm::mtl::PtrSingleton< ::gf::GfGameMercenaries> {
public:
    // SCOM_ADD_MERCENARIES_POINT and SCOM_SET_MERCENARIES_LEVEL pass their request's value
    static void addPoint(unsigned int point);
    static void setLevel(unsigned int level);
    virtual ~GfGameMercenaries();  // slot 0
    // a mission's rewards (team: GfDataMercenaries::isMissionOrderTeam), the bonus parts ("Hosei") on their own
    static int getRewardGold(unsigned int mission, bool team);
    static int getRewardGoldHosei(unsigned int mission, bool team);
    static int getRewardExp(unsigned int mission, bool team);
    static int getRewardDevelop(unsigned int mission, bool team);
    static int getRewardDevelopHosei(unsigned int mission, bool team);
    static int getRewardTrust(unsigned int mission);
    static int getRewardMercenariesPoint(unsigned int mission);
    static void getZoneMission(mm::mtl::FixedVector<unsigned short, 500>& missions, unsigned int zone);  // a zone's missions
};
}  // namespace gf

#endif
