#ifndef GRLIB_CGLIBSTATE_H
#define GRLIB_CGLIBSTATE_H

namespace grlib { class CGLibRenderTarget; }

namespace grlib {
// the drawing context's state (grlib/context/CGLibSystemContext)
class CGLibState {
public:
    static void setMainFrameBuffer();
    static CGLibRenderTarget* getMainRenderTarget();
};
}  // namespace grlib

#endif
