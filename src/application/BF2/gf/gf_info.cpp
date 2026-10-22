#include "mm/Mat44.h"
#include "mm/Plane.h"
#include "classes/gf/GfInfo.h"
#include "classes/fw/Framework.h"
#include "classes/ml/DevGraph.h"
#include "classes/ml/MicroThread.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

mm::Plane GfInfo::m_camPlanes[6];
mm::Mat44 GfInfo::m_frustum;
mm::Mat44 GfInfo::m_projection;
mm::Mat44 GfInfo::m_viewMat;
mm::Mat44 GfInfo::m_viewMatInv;
mm::Mat44 GfInfo::m_viewProj;
mm::Vec3 GfInfo::m_camPos;
mm::Vec3 GfInfo::m_camRot;
mm::Vec3 GfInfo::m_camTgt;
mm::Pnt<int> GfInfo::m_camSize;
float GfInfo::m_camFov;
float GfInfo::m_camFar;
float GfInfo::m_camNear;
float GfInfo::m_camAspect;
float GfInfo::m_camLength;
float GfInfo::m_fSecPerFrame;
int GfInfo::m_nScreenW;
int GfInfo::m_nScreenH;

void GfInfo::initialize(const GfSetupParam& param) {
    m_nScreenW = ml::DevGraph::getRootWidth();
    m_nScreenH = ml::DevGraph::getRootHeight();
    mm::Plane plane(mm::Vec3::unitY, mm::Vec3::zero);
    m_camPlanes[0] = plane;
    m_camPlanes[1] = plane;
    m_camPlanes[2] = plane;
    m_camPlanes[3] = plane;
    m_camPlanes[4] = plane;
    m_camPlanes[5] = plane;
    m_frustum = mm::Mat44::identity;
    m_projection = mm::Mat44::identity;
    m_viewMat = mm::Mat44::identity;
    m_viewProj = mm::Mat44::identity;
    m_camPos = mm::Vec3::zero;
    m_camRot = mm::Vec3::zero;
    m_camTgt = mm::Vec3::zero;
    m_camSize.x = m_nScreenW;
    m_camSize.y = m_nScreenH;
    m_camFov = 40.0f;
    m_camFar = 8000.0f;
    m_camNear = 0.1f;
    m_camAspect = 1.0f;
    m_camLength = 1.0f;
    m_fSecPerFrame = ml::DevGraph::getFrameSyncSec();
    m_initialized = true;
}

GfInfo::~GfInfo() {}

void GfInfo::build(const GfSetupParam& param) {
#line 70
    new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfInfo(param);
}

void GfInfo::destroy() {
    GfInfo* info = get();
    info->finalize();
    delete info;
}

// apply is not written yet

unsigned int GfInfo::getFrameCount32() {
    return fw::Framework::getFrameCount();
}

void GfSleep(unsigned int frames) {
    ml::MicroThread::get()->sleep(frames, true);
}

int GfScreenW() {
    return GfInfo::m_nScreenW;
}

bool GfIsInMicroThread() {
    return ml::MicroThread::get()->m_currentGroup != nullptr;
}

}  // namespace gf
