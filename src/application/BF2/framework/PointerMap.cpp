#include "mm/mtl/Array.h"
#include "classes/fw/PointerMap.h"
#include "fw/RenderParam.h"
#include "fw/Prim.h"
#include "ml/ScnRenderDrSysParmAcc.h"
#include "ml/ScnRenderDrEnvColi.h"
#include "idcoli/IDColiAccMan.h"
#include "classes/fw/Framework.h"
#include "classes/ml/Scn.h"
#include "classes/ml/DevGraph.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace fw {

PtrMapIterator PtrMapIterator::operator++() {
    const ptr_detail::PtrParam* end = m_params->end();
    if (m_param != end) {
        ++m_param;
        while (m_param != end && (m_param->m_ptr == nullptr || m_param->m_handle == 0)) {
            ++m_param;
        }
    }
    return *this;
}

PointerMap::~PointerMap() {
    destroy();
}

void PointerMap::destroy() {
    m_params.clear();
    m_count = 0;
    m_registCount = 0;
}

PtrMapIterator PointerMap::begin() const {
    PtrMapIterator it(&m_params, m_params.begin());
    while (it.m_param != m_params.end() && (it.m_param->m_ptr == nullptr || it.m_param->m_handle == 0)) {
        ++it;
    }
    return it;
}

PtrMapIterator PointerMap::end() const {
    return PtrMapIterator(&m_params, m_params.end());
}

void PointerMap::setRange(unsigned int first, unsigned int last, unsigned int mask) {
    m_first = first;
    m_last = last;
    m_mask = mask;
}

void PointerMap::reserve(mm::mtl::IAllocator* allocator, unsigned long count) {
    m_params.setAllocator(allocator);
    m_params.reserve(count);
    m_count = count;
}

unsigned int PointerMap::nextID(unsigned int id) {
    unsigned int next = id + 1;
    if ((next >= m_first) & (next <= m_last)) {
        return next;
    }
    return m_first;
}

unsigned int PointerMap::regist(const void* ptr) {
    unsigned int index;
    unsigned int tries = 0;
    do {
        if (++tries >= m_count) {
            return 0;
        }
        m_lastHandle = nextID(m_lastHandle);
        index = m_lastHandle % m_count;
    } while (m_params[index].m_ptr != nullptr);
    m_params[index].m_ptr = ptr;
    m_params[index].m_handle = m_lastHandle;
    m_registCount++;
    return m_lastHandle;
}

void PointerMap::remove(unsigned int handle) {
    if (m_count != 0) {
        handle &= m_mask;
        unsigned int index = handle % m_count;
        if (m_params[index].m_ptr != nullptr) {
            m_params[index] = ptr_detail::PtrParam();
            m_registCount--;
        } else {
            mm::MMStdBase::mmPrint("[fw] not exist handle:%x", handle);
        }
    }
}

void* PointerMap::getPtr(unsigned int handle) const {
    if (handle != 0 && m_count != 0) {
        handle &= m_mask;
        unsigned int index = handle % m_count;
        if (m_params[index].m_handle == handle) {
            return const_cast<void*>(m_params[index].m_ptr);
        }
    }
    return nullptr;
}

bool PointerMap::isValid(unsigned int handle) const {
    if (handle == 0 || m_count == 0) {
        return false;
    }
    handle &= m_mask;
    return m_params[handle % m_count].m_handle == handle;
}

void PrimCapsule::setup(const mm::Vec3& start, const mm::Vec3& end, float radius) {
    m_dir.x = start.x - end.x;
    m_dir.y = start.y - end.y;
    m_dir.z = start.z - end.z;
    float length = m_dir.length();
    if (length <= 1e-6f) {
        m_dir = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        m_dir.x = scale * m_dir.x;
        m_dir.y = scale * m_dir.y;
        m_dir.z = scale * m_dir.z;
    }
    m_start = start;
    m_end = end;
    m_radius = radius;
}

bool PrimCapsule::isCollide(const PrimCapsule& other) const {
    return mm::Line2::getNearestLength(*this, other) <= m_radius + other.m_radius;
}

// mm::Line2::getNearestLength(const Line2&, const Line2&) (0x7100198EF8) is not written yet: the closest attempt
// (direction copies for the cosine and the crossing feet, the fields for the parallel case) is still about 140 words
// off in register choice and load placement.

bool PrimCapsule::isCollide(const PrimSphere& sphere) const {
    return mm::Line2::getNearestLength(*this, sphere.m_center) <= m_radius + sphere.m_radius;
}

}  // namespace fw

namespace mm {

float Line2::getNearestLength(const Line2& line, const Vec3& point) {
    float t = (point - line.m_start).dot(line.m_dir);
    Vec3 nearest = line.m_start + line.m_dir * t;
    // inside the segment when its ends lie on either side of the point's foot
    if ((line.m_start - nearest).dot(line.m_end - nearest) < 0.0f) {
        return (nearest - point).length();
    }
    float startSq = (line.m_start - point).dot(line.m_start - point);
    float endSq = (line.m_end - point).dot(line.m_end - point);
    return ::sqrtf(startSq < endSq ? startSq : endSq);
}

}  // namespace mm

namespace fw {

void PrimSphere::setup(const mm::Vec3& center, float radius) {
    m_center = center;
    m_radius = radius;
}

void RenderParam::initialize() {}

void RenderParam::finalize() {}

bool fn_7100199318() {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, 0);
    return acc.isSeamMapRead();
}

void RenderParam::setPlayerPosition(const mm::Vec3& pos, CAMERA_TYPE type) {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, type);
    acc.setPlayerPos(pos);
}

bool RenderParam::isRoom(const mm::Vec3& pos, CAMERA_TYPE type) {
    ml::ScnRenderDrEnvColi coli(type);
    if (!coli.testEnvColi(pos, 0.5f)) {
        return false;
    }
    return coli.isRoom();
}

void RenderParam::setMotionBlur(bool enable, CAMERA_TYPE type) {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, type);
    acc.setMotBlurDefault(enable);
}

void RenderParam::setTime(unsigned int hour, unsigned int minute, CAMERA_TYPE type) {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, type);
    acc.setTimeVal(static_cast<float>(hour * 60 + minute) / 1440.0f);
}

// setWeather (0x71001994C0) is not written: 3.0.1's takes a float in s0 besides the weather and the camera type
// (the weather frame it divides by DevGraph::getFrameSyncSec), so the symbol's (unsigned int, CAMERA_TYPE), 1.0.0's
// 0x54-byte function's, no longer fits it; nothing calls it directly to show where the float goes.

int RenderParam::getWindIndex(CAMERA_TYPE type) {
    ml::ScnRenderDrEnvColi coli(type);
    return coli.getWindId();
}

void RenderParam::setGlobalWindPower(const mm::Vec3& power, CAMERA_TYPE type) {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, type);
    acc.setGlobalWind(power);
}

void RenderParam::setColorFilter(int num, int farNum, float time, CAMERA_TYPE type) {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, type);
    acc.setColorFilterOverride(true);
    acc.setColorFilterNum(num);
    acc.setColorFilterFarNum(farNum);
    acc.setColorFilterFrm(time * 30.0f);
}

void RenderParam::resetColorFilter(float time, CAMERA_TYPE type) {}

void RenderParam::setCloudSea(unsigned int num) {
    {
        ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, 0);
        acc.setPlaneCloudNum(num);
    }
    {
        idcoli::IDColiAccMan coli;
        coli.setSubNum(num);
    }
}

void RenderParam::resetScene() {
    ml::ScnRenderDrSysParmAcc acc(mm::mtl::PtrSingleton<Framework>::get()->m_scn->m_renderDrSys, 0);
    acc.resetScene();
}

}  // namespace fw
