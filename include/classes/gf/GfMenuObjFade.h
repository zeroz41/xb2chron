#ifndef CLASSES_GF_GFMENUOBJFADE_H
#define CLASSES_GF_GFMENUOBJFADE_H

#include "classes/gf/GfMenuObject.h"
#include "mm/Col4.h"

namespace gf {
// table 0x7100B62298
class GfMenuObjFade : public ::gf::GfMenuObject {
public:
    class FadeListener;
    class LoadingListener;
    struct StartParam {
        unsigned char channel;
        unsigned short time;
        mm::Col4 color;
    };
    GfMenuObjFade(unsigned int handle);
    virtual ~GfMenuObjFade();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void start(const StartParam& param);
    // shows (or hides) LAY_loading, fading over `frames` frames (0: at once)
    static void dispLoading(bool disp, unsigned short frames);
    static void dispSaving(bool disp, unsigned short frames);  // the same for LAY_saving
    static void getFadeColor(unsigned char channel, mm::Col4& color);
    unsigned char pad_24[4];
    // how many dispLoading/dispSaving calls show LAY_loading or LAY_saving: the LoadingListeners fade it in at the
    // first and out at the last (the name is not the original's)
    signed char m_loadingCount;

private:
    // IMG_fade%02d, the image of one of the three channels, under the layout handle (0 for no such channel): its
    // callers inline it (the name is not the original's)
    static unsigned int getFadeImage(unsigned int handle, unsigned char channel);
};
}  // namespace gf

#endif
