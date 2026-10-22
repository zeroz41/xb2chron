#ifndef CLASSES_GF_GFGAMECAMERA_H
#define CLASSES_GF_GFGAMECAMERA_H

#include "classes/fw/Camera.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class GfGameCamera; }
namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B546D8: the game's sub view cameras, one per gf::VIEWCAM, each on its own camera layer
class GfGameCamera : public ::mm::mtl::PtrSingleton< ::gf::GfGameCamera> {
public:
    GfGameCamera(const GfSetupParam& param);
    virtual ~GfGameCamera();  // slot 0
    // out of line in 1.0.0; inline in 3.0.1
    void initialize(const GfSetupParam& param) {
        createSubViewCamera();
        m_initialized = true;
    }
    void finalize() {
        destroySubViewCamera();
        m_initialized = false;
    }
    static void build(const GfSetupParam& param);
    static void destroy();
    void createSubViewCamera();
    void destroySubViewCamera();
    void clear();
    static void setCameraControlType(int type);

    mm::mtl::FixedArray<mm::mtl::IntrusivePtr<fw::Camera>, 3> m_subViewCameras;  // VIEWCAM 1 to 3
    bool m_initialized;  // initialize sets it, finalize clears it
};
}  // namespace gf

#endif
