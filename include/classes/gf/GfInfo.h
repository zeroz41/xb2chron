#ifndef CLASSES_GF_GFINFO_H
#define CLASSES_GF_GFINFO_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/Mat44.h"
#include "mm/Plane.h"
#include "mm/Pnt.h"
#include "mm/Vec3.h"

namespace gf { class GfSetupParam; }

namespace gf {
// table 0x7100B59228; its destructor is its singleton's
class GfInfo : public ::mm::mtl::PtrSingleton<GfInfo> {
public:
    // out of line in 1.0.0; build inlines it in 3.0.1
    GfInfo(const GfSetupParam& param) : m_initialized(false) { initialize(param); }
    virtual ~GfInfo();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    // out of line in 1.0.0; 3.0.1 keeps no copy
    void finalize() { m_initialized = false; }
    static bool isInitialized() {
        GfInfo* info = get();
        if (info != nullptr) {
            return info->m_initialized;
        }
        return false;
    }
    static void apply();
    static unsigned int getFrameCount32();

    bool m_initialized;  // cleared by the constructor and finalize

    // the current camera's, as apply copies them
    static mm::Plane m_camPlanes[6];
    static mm::Mat44 m_frustum;
    static mm::Mat44 m_projection;
    static mm::Mat44 m_viewMat;
    static mm::Mat44 m_viewMatInv;
    static mm::Mat44 m_viewProj;  // m_viewMat * m_projection
    static mm::Vec3 m_camPos;
    static mm::Vec3 m_camRot;
    static mm::Vec3 m_camTgt;
    static mm::Pnt<int> m_camSize;
    static float m_camFov;
    static float m_camFar;
    static float m_camNear;
    static float m_camAspect;
    static float m_camLength;
    static float m_fSecPerFrame;  // seconds a frame lasts (GfVolumeFade::setupKeyFrame turns frame counts into time)
    static int m_nScreenW;
    static int m_nScreenH;
};

int GfScreenW();  // GfInfo::m_nScreenW
void GfSleep(unsigned int frames);
// whether a micro-thread group is running (MicroThread::update sets the one it runs); the name is not the original's
bool GfIsInMicroThread();
}  // namespace gf

#endif
