#ifndef CLASSES_GF_GFMENUOBJHELPHUD_H
#define CLASSES_GF_GFMENUOBJHELPHUD_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuObjUtil.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B62A30
class GfMenuObjHelpHud : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjHelpHud(unsigned int handle);
    virtual ~GfMenuObjHelpHud();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void enable();
    static void disable();
    bool seqPageFadeOut();
    bool seqPageLoad();
    bool seqPageFadeIn();
    // 1.0.0's (out of line there; 3.0.1 has no copies): IMG_help's fades
    static int ctrlFadeOut(unsigned int handle) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 2;
        param.m_time = 0.1f;
        param.m_startFlags = 2;
        return GfMenuObjUtil::startCtrl(handle, param, nullptr);
    }
    static int ctrlFadeIn(unsigned int handle) {
        GfMenuObjUtil::CtrlParam param;
        param.m_methods = 1;
        param.m_time = 0.1f;
        return GfMenuObjUtil::startCtrl(handle, param, nullptr);
    }
    // the help page IMG_help shows: 0 none, 1-2, 3-4 and 5 the three buttons' pages (the name is not the original's)
    unsigned int m_page;
    unsigned char pad_28[8];
    GfMenuSequence<GfMenuObjHelpHud, 8> m_seq;
    // the fade or load the page sequence's job started is running (the name is not the original's)
    bool m_jobStarted;
};
}  // namespace gf

#endif
