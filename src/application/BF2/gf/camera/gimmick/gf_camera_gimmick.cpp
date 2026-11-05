#include "gf/FileStaticVec3.h"
#include "classes/gf/GimmickCameraParams.h"
#include "classes/gf/GimmickCamera.h"
#include "classes/fw/Framework.h"
#include "classes/fw/CommonResource.h"
#include "classes/mm/mtl/IAllocator.h"
#include "classes/gf/GfGameManager.h"
#include "gf/GfStaticRes.h"
#include "string.h"
#include "math.h"
#include "mm/Quat.h"

namespace gf {

GimmickCamera::~GimmickCamera() {}

mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create(const char* name) {
#line 119
    GimmickCamera* camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera(fw::CAMERA_PRIO(0x37));
    camera->m_readKind = 1;
    camera->m_coordType = 0;
    camera->setReadFile(name);
    return camera;
}

void GimmickCamera::setReadFile(const char* name) {
    fw::CommonResource* res =
        GfStaticRes::search(GfGameManager::isGameTypeIra() ? "/camera/params_dlc.gca" : "/camera/params.gca");
    if (res == nullptr) {
        return;
    }
    const char* file = static_cast<const char*>(res->getAssetData());
    const ParamFile* header = reinterpret_cast<const ParamFile*>(file);
    int count = header->m_count;
    int dataOffset = header->m_dataOffset;
    const char* names = file + header->m_nameOffset;
    for (int i = 0; i < count; ++i) {
        if (strcmp(names + header->m_entries[i].m_nameOffset, name) == 0) {
            void* data = const_cast<char*>(file + dataOffset + header->m_entries[i].m_dataOffset);
            int version = static_cast<const GimmickCameraParams::Header*>(data)->m_version;
            m_readEntry = data;
            if (!m_playing) {
                m_params.clear();
            }
            GimmickCameraParams params(data, version);
            for (int j = 0; j < params.getSize(); ++j) {
                const GimmickCameraParams::Param* param = params.getParam(j);
                if (!m_playing) {
                    m_params.push_back(Param(*param));
                }
            }
            const Param& first = m_params[0];
            m_pos = first.m_pos;
            m_rot = first.m_rot;
            m_curFov = first.m_fov;
            updateParamsByCoordinateType();
            updateParams();
            return;
        }
    }
}

mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create(const char* name, GF_OBJ_HANDLE* target) {
#line 130
    GimmickCamera* camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera(fw::CAMERA_PRIO(0x37));
    camera->m_readKind = 1;
    camera->m_coordType = 1;
    camera->m_target = target;
    camera->setReadFile(name);
    return camera;
}

mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create(const char* name, const mm::Vec3& pos, float rotY) {
#line 142
    GimmickCamera* camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera(fw::CAMERA_PRIO(0x37));
    camera->m_readKind = 1;
    camera->m_coordType = 2;
    camera->m_basePos = pos;
    camera->m_baseRotY = rotY;
    camera->setReadFile(name);
    return camera;
}

void GimmickCamera::updateParams() {
    mm::Vec3 target;
    target = getDirection();
    target += m_pos;
    m_fov = m_curFov;
    setLookAt(m_pos, target, m_rot.z);
}

bool GimmickCamera::isPlayEnd() const {
    if (m_started) {
        return !m_playing;
    }
    return false;
}

bool GimmickCamera::isLoaded() const { return true; }

void GimmickCamera::setAuto(bool on) { m_auto = on; }

void GimmickCamera::setCollision(bool on) { m_collision = on; }

void GimmickCamera::setNearClip(float clip) { m_nearClip = clip; }

void GimmickCamera::setPause(bool on) { m_pause = on; }

void GimmickCamera::onActivate() {}

mm::mtl::RTTI GimmickCamera::m_rtti("GimmickCamera", &::fw::Camera::m_rtti, nullptr);

}  // namespace gf
