#ifndef CLASSES_GF_GFMENUOBJZONETELOP_H
#define CLASSES_GF_GFMENUOBJZONETELOP_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B65198
class GfMenuObjZoneTelop : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjZoneTelop(unsigned int handle);
    virtual ~GfMenuObjZoneTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqFadeIn();
    bool seqFadeOut();
    // shows the zone's name (an id of BDAT file 0x12D's texts) through GfMenuOrderMgr's channel 1
    static void open(GfMenuCallContext* context, unsigned short name);
    static void close(float time);  // fades out over that time (0: at once)
    GfMenuSequence<GfMenuObjZoneTelop, 4> m_seq;
    // the fade seqFadeIn or seqFadeOut started is running (the name is not the original's)
    bool m_fadeStarted;
    float m_fadeOutTime;  // how long seqFadeOut's fade runs: 0.5, or close's (the name is not the original's)
};
}  // namespace gf

#endif
