#ifndef GRLIB_CGLIBSTATE_H
#define GRLIB_CGLIBSTATE_H

#include "grlib/GrlTypes.h"

namespace grlib { class CGLibColorBuffer; class CGLibDepthBuffer; class CGLibRenderTarget; }

namespace grlib {
// a viewport: the rectangle and the depth range (the field names are not the original's)
struct LibMainStateViewPort {
    float x;
    float y;
    float width;
    float height;
    float minDepth;
    float maxDepth;
};

// the drawing context's state (grlib/context/CGLibSystemContext)
class CGLibState {
public:
    static void setMainFrameBuffer();
    // sets the viewport and the scissor rectangle and keeps the viewport
    static void setViewport(const LibMainStateViewPort& viewport);
    static void setOnlyViewport(const LibMainStateViewPort& viewport);
    static void setOnlyScissor(const LibMainStateViewPort& viewport);
    // the render targets: begin, register each colour target and the depth target, end binds them
    static void beginRegisterRenderTarget();
    static void setRegisterRenderTarget(CGLibColorBuffer& buffer, GrlMrtType mrt);
    static void setRegisterRenderTarget(CGLibRenderTarget& target, GrlMrtType mrt);
    static void setRegisterDepthTarget(CGLibDepthBuffer& buffer);
    static void endRegisterRenderTarget();
    static CGLibRenderTarget* getMainRenderTarget();
    static void setPixelResidentArea(bool enable, unsigned int size);
};
}  // namespace grlib

#endif
