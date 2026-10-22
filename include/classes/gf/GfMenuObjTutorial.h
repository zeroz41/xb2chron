#ifndef CLASSES_GF_GFMENUOBJTUTORIAL_H
#define CLASSES_GF_GFMENUOBJTUTORIAL_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B64E48
class GfMenuObjTutorial : public ::gf::GfMenuObject {
public:
    class MainListener;
    // what openText shows: a text of BDAT file 0x12A (the name is not the original's)
    struct TextParam {
        unsigned int m_text;
    };
    GfMenuObjTutorial(unsigned int handle);
    virtual ~GfMenuObjTutorial();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // the tutorial window attached under 0x7A: its text (event 0x101), focus (0x102) and icon (0x103) of an index
    // open (with a parameter) or close, start (0x104) begins it and closeAll (0x22) ends it
    static void openText(unsigned int index, const TextParam& param);
    static void closeText(unsigned int index);
    static bool isWaiting();  // the tutorial's call context is running
    static void closeFocus(unsigned int index);
    static void closeIcon(unsigned int index);
    static void start();
    static void closeAll();
    bool seqTelopStart();
    bool seqTelopEnd();
    bool seqEnd();
    GfMenuSequence<GfMenuObjTutorial, 8> m_seq;
    // seqTelopStart and seqTelopEnd: the telop's animation was started (the name is not the original's)
    bool m_telopStarted;
    // seqTelopStart: frames left before it ends the call context (5 at its start; the name is not the original's)
    int m_termWait;
};
}  // namespace gf

#endif
