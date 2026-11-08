#define MM_LIB_FROM_MONOLIB_MM
#include "classes/ml/ScnDebug.h"
#include "classes/ml/ScnDebugManipu.h"
#include "classes/ml/ScnObj.h"
#include "classes/ml/ScnObjClip.h"
#include "classes/ml/ScnObjEnvColi.h"
#include "classes/ml/ScnObjLight.h"
#include "classes/ml/ScnObjCam.h"
#include "classes/ml/ScnObjModel.h"
#include "classes/ml/ScnObjIBLDr.h"
#include "classes/ml/ScnRender.h"
#include "classes/ml/ScnRenderDrSys.h"
#include "classes/ml/Scn.h"
#include "classes/ml/ScnPoolObj.h"
#include "classes/ml/ScnCamMan.h"
#include "nn/os.h"
#include "ml/CriticalSection.h"
#include "classes/ml/Thread.h"
#include "classes/ml/ThreadNx.h"
#include "classes/ml/WorkCpu.h"
#include "classes/ml/threadval.h"
#include "classes/ml/ScnDebugManipuObj.h"
#include "classes/ml/ScnObjIBL.h"
#include "classes/ml/ScnDebugManipuRot.h"
#include "classes/ml/ScnDebugManipuTrans.h"
#include "classes/ml/DevClock.h"
#include "ml/EdianUtil.h"
#include "ml/TimeCount.h"
#include "ml/WorkUtil.h"
#include "mtl/MemManager.h"
#include "mm/mtl/FixStr.h"
#include "ml/AttrTransform.h"
#include "ml/CamUtil.h"
#include "ml/PathUtil.h"
#include <string.h>

namespace ml {

unsigned int EdianUtil::read(const unsigned int& value) {
    return __builtin_bswap32(value);
}

short EdianUtil::read(const short& value) {
    return __builtin_bswap16(value);
}

void TimeCount::reset() {
    DevClock::getClockNow(pad_0);
}

void TimeCount::start() {
    DevClock::getClockNow(pad_0);
}

void TimeCount::getClockLap(long& lap) const {
    long now;
    DevClock::getClockNow(now);
    lap = now - pad_0;
}

float TimeCount::getSecLap() const {
    float sec;
    DevClock::getTimeNow(sec, pad_0);
    return sec;
}

void AttrTransform::clear() {
    m_pos = mm::Vec3::zero;
    m_scl = mm::Vec3(1.0f, 1.0f, 1.0f);
    m_mat = mm::Mat44::identity;
    m_worldMat = mm::Mat44::identity;
    pad_B0 = mm::Mat44::identity;
    m_posGbl = mm::Vec3::zero;
    m_flags = 0;
    m_rot = mm::Vec3::zero;
    pad_120 = mm::Quat::identity;
    pad_100 = mm::Vec3::zero;
}

void CamUtil::getViewLocalToDeviceCoord(mm::Vec3& out, const mm::Mat44& proj, const mm::Vec3& pos) {
    out.x = proj.m[0][0] * (pos.x / pos.z) - proj.m[2][0];
    out.y = proj.m[1][1] * (pos.y / pos.z) - proj.m[2][1];
    out.z = -proj.m[3][2] / pos.z - proj.m[2][2];
}

void CamUtil::getDeviceCoordToViewLocal(mm::Vec3& out, const mm::Mat44& proj, const mm::Vec3& pos) {
    out.z = -proj.m[3][2] / (pos.z + proj.m[2][2]);
    out.x = out.z * ((pos.x + proj.m[2][0]) / proj.m[0][0]);
    out.y = (pos.y + proj.m[2][1]) / proj.m[1][1] * out.z;
}

const char* PathUtil::getFilePtrFromPath(const char* path) {
    int len = strlen(path);
    for (int i = len - 1; i >= 0; i--) {
        char c = path[i];
        if (c == '/' || c == '\\' || c == ':') {
            return &path[i + 1];
        }
    }
    return path;
}

const char* PathUtil::getFileExtPtr(const char* path) {
    int len = strlen(path);
    for (int i = 0; i < len - 1; i++) {
        if (path[i] == '.') {
            return &path[i + 1];
        }
    }
    return nullptr;
}

mm::mtl::FixStr<64> PathUtil::getNoPathExtName(const char* path) {
    mm::mtl::FixStr<64> name;
    const char* file = getFilePtrFromPath(path);
    if (file != nullptr) {
        name = file;
        int dot = name.findLast('.');
        if (dot == -1 || dot == 0) {
            return name;
        }
        return name.substr(0, dot);
    }
    return name;
}

}  // namespace ml
