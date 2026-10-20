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
    virtual ~GfMenuObjFade();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void start(const StartParam& param);
    static void dispLoading(bool disp, unsigned short id);
    static void getFadeColor(unsigned char channel, mm::Col4& color);
};
}  // namespace gf

#endif
