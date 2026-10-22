#ifndef CLASSES_GF_GFMENUOBJCHAPTERTELOP_H
#define CLASSES_GF_GFMENUOBJCHAPTERTELOP_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B60DB8
class GfMenuObjChapterTelop : public ::gf::GfMenuObject {
public:
    class ListListener;
    GfMenuObjChapterTelop(unsigned int handle);
    virtual ~GfMenuObjChapterTelop();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqWaitStreamBegin();
    bool seqOutChapterEnd();
    bool seqWaitChapterEnd();
    // the telops of a chapter (1-10, else 1) through the object attached under 0x44: its beginning, its end (with
    // add-on layer 3, 1-11 kept, else 12) and the avant-title
    static void openBeginTelop(GfMenuCallContext* context, int chapter);
    static void openEndTelop(GfMenuCallContext* context, int chapter);
    static void openAvanTitle(GfMenuCallContext* context, int chapter);
    static void close(unsigned short frames);  // fades out over that many frames (0: at once)
    GfMenuSequence<GfMenuObjChapterTelop, 4> m_seq;
};
}  // namespace gf

#endif
