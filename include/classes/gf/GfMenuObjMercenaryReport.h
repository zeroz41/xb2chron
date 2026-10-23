#ifndef CLASSES_GF_GFMENUOBJMERCENARYREPORT_H
#define CLASSES_GF_GFMENUOBJMERCENARYREPORT_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfMenuBladeList; }
namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuReferenceNumber; }

namespace gf {
// table 0x7100B63500
class GfMenuObjMercenaryReport : public ::gf::GfMenuObject {
public:
    class MainListener;
    class RewardListener;
    GfMenuObjMercenaryReport(unsigned int handle);
    virtual ~GfMenuObjMercenaryReport();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // its sequence's jobs (1.0.0's names)
    bool seqDispReward();
    bool seqStart();
    bool seqEnd();
    bool seqDispBlade();
    bool seqDispInfo();
    bool seqClose();
    bool seqCheckAchive();
    bool seqWaitLoadKizuna();
    bool seqWaitEndKizuna();
    unsigned int m_teamId;           // GfMenuReference::setReferenceTeamID's (the name is not the original's)
    GfMenuBladeList* m_bladeList;    // the team's blades for the adapters (the name is not the original's)
    GfMenuSequence<GfMenuObjMercenaryReport, 10> m_seq;
    // seqDispReward's steps: the reward shown, then closed (the names are not the original's)
    bool m_rewardShown;
    bool m_rewardClosed;
    bool m_waitVoice;  // update waits for the voice, then shows the reward (the name is not the original's)
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_number;  // the reference adapters' number (the name is not the original's)
    GfMenuCallContext* m_rewardContext;  // GfMenuObjQuestReward's (the name is not the original's)
    GfMenuCallContext* m_kizunaContext;  // GfMenuObjBlKizunaRing's (the name is not the original's)
    long m_voice;  // the voice update stops, -1 for none (the name is not the original's)
};
}  // namespace gf

#endif
