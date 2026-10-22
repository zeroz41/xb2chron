#ifndef CLASSES_GF_GFMENUOBJEVENTSUBTITLE_H
#define CLASSES_GF_GFMENUOBJEVENTSUBTITLE_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61FD0
class GfMenuObjEventSubtitle : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjEventSubtitle(unsigned int handle);
    virtual ~GfMenuObjEventSubtitle();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // shows a message table's text on a subtitle line (0-2: TXT_str00-02, or TXT_str_v for a vertical first line)
    static void dispText(unsigned char* bdat, unsigned int id, unsigned int line);
    static void hideText();  // hides every line
    static void endText();   // hides the first line and clears its texts
};
}  // namespace gf

#endif
