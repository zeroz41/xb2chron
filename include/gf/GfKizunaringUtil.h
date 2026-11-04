#ifndef GF_GFKIZUNARINGUTIL_H
#define GF_GFKIZUNARINGUTIL_H

namespace gf { struct GfQuestReward; }

namespace gf {
// the affinity chart (kizunaring) helpers (functions, by their symbols)
class GfKizunaringUtil {
public:
    // the reward of a blade's completed affinity chart (a driver-type blade's from GfBdatChrDr, else a GfBdatBlade
    // create config row by its crown points plus mtRand(4)); stores the blade as the reward's trust blade. False when
    // there is none.
    static bool getCompleteKizunaringReward(GfQuestReward& reward, unsigned int blade);
    // the reward of a driver's completed affinity chart (GfBdatChrDr's row; the bool picks getChrIrKizunaReward2's over
    // getChrIrKizunaReward1's), reward 0x3A3 when there is none. 1.0.0's symbol at this place (same caller,
    // GfMenuObjDrKizunaRing::seqComplete), getCompleteKizunaringRewardForDriver, takes only the reward and returns
    // reward 0x3A3, so the name stays a placeholder
    static bool getCompleteKizunaringRewardForDriver(GfQuestReward& reward, unsigned int driver, bool);
};
}  // namespace gf

#endif
