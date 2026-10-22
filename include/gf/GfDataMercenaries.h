#ifndef GF_GFDATAMERCENARIES_H
#define GF_GFDATAMERCENARIES_H

namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {
// the mercenary team's data (functions, by its symbols)
class GfDataMercenaries {
public:
    // a team, as the game data keeps them (0x28 bytes); the name is not the original's
    struct Team {
        unsigned char pad_0[0x10];
        unsigned int m_teamId;  // what the functions that take a team id are given for it
        unsigned char pad_14[0x14];
    };
    static int getLevel();  // up to 5 (GfMenuGameAdapter::update_MercenariesPoint shows no points at 5)
    static int getPoint();
    static int getPointMax();
    static unsigned int getTeamNum();
    static Team* getTeamByIndex(unsigned int index);
    static bool isTeamStateReward(unsigned int teamId);  // the team is back with a reward to collect
    // the teams on a zone's missions, working on them or done with them
    static void getTeamByZoneMissionWorking(mm::mtl::FixedVector<unsigned short, 3>& teams, unsigned int zone);
    static void getTeamByZoneMissionComplete(mm::mtl::FixedVector<unsigned short, 3>& teams, unsigned int zone);
    static bool isTeamStateExpedition(unsigned int teamId);  // the team is away on a mission
    static int getMissionCategory(unsigned int mission);
    static bool isNewMission(unsigned int mission);
};
}  // namespace gf

#endif
