#ifndef CLASSES_GF_GFMENUOBJMERCENARYROOT_H
#define CLASSES_GF_GFMENUOBJMERCENARYROOT_H

#include "classes/gf/GfMenuObject.h"
#include "gf/GfMenuSequence.h"

namespace gf {
// table 0x7100B63598
class GfMenuObjMercenaryRoot : public ::gf::GfMenuObject {
public:
    class MainListener;
    GfMenuObjMercenaryRoot(unsigned int handle);
    virtual ~GfMenuObjMercenaryRoot();  // slot 0
    static void openBg(int image);
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqWaitBGStream();
    // the image IMG_bg shows: -1 until openBg's first, which fades it in, then each one fades in over it on
    // IMG_bg_front (the name is not the original's)
    int m_bgImage;
    GfMenuSequence<GfMenuObjMercenaryRoot, 4> m_seq;
    unsigned int m_bgm;  // the menu's music, from GfMenuObjUtil::playBGM (the name is not the original's)
};
}  // namespace gf

#endif
