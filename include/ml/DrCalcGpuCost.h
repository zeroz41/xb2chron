#ifndef ML_DRCALCGPUCOST_H
#define ML_DRCALCGPUCOST_H

namespace ml {

class DrPixlPostParm;

// The GPU cost governor DrMan builds: update compares DevGraph::getCost() with the target cost and steps a level
// (0..5) that scales the two resolution rates between their minimum and maximum. Field names are inferred from
// update and the constructor's values; they are not the original's.
class DrCalcGpuCost {
public:
    DrCalcGpuCost();
    ~DrCalcGpuCost();
    void update(const DrPixlPostParm* pParm);

    bool m_debug;           // 0x0: false from the constructor (no reader known)
    float m_targetCost;     // 0x4: 95; update steps the level up when the cost reaches it
    float m_lowCost;        // 0x8: 95 * 0.95 (update recomputes it)
    float m_minCost;        // 0xC: 95 * 0.89 (update recomputes it)
    float m_maxRate[2];     // 0x10
    float m_minRate[2];     // 0x18
    float m_rate[2];        // 0x20: the rates of the current level
    float m_rateStep[2];    // 0x28: (max - min) / 5
    float m_margin;         // 0x30: 0.1 from the constructor (no reader known)
    int m_level;            // 0x34
    int m_counter;          // 0x38
    bool m_lock;            // 0x3C: update keeps the level while set
};

}  // namespace ml

#endif
