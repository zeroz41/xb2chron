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

// the slow-in curve, 1 - cos(t * pi / 2) written as a sine, blended by nothing toward 1 (as gf_camera_chain_attack's;
// the original's helper is inline; its form and name are not the original's)
static inline float slowIn(float t) {
    float v = ::sinf(t * 1.5707964f + 4.712389f) + 1.0f;
    return v + (1.0f - v) * 0.0f;
}

// the rotation of a key's pitch and yaw (its roll left out), as getDirection builds it (inline; the name is not the
// original's)
static inline mm::Quat getRotation(const mm::Vec3& rot) {
    mm::Vec3 euler(rot.x, rot.y, 0.0f);
    mm::Vec3 half = euler * 0.5f;
    float hx = half.x, hy = half.y, hz = half.z;
    float sx = ::sinf(hx), cx = ::cosf(hx), sy = ::sinf(hy), cy = ::cosf(hy), sz = ::sinf(hz), cz = ::cosf(hz);
    return mm::Quat(sx * cy * cz - cx * sy * sz, sx * cy * sz + cx * sy * cz, cx * cy * sz - sx * sy * cz,
                    sx * sy * sz + cx * cy * cz);
}

GimmickCamera::~GimmickCamera() {}

float GimmickCamera::getPitch(const mm::Vec3& dir, const mm::Vec3& front) {
    float yaw = getYaw(dir, front);
    mm::Vec3 a = dir;
    mm::Vec3 b = front;
    float half = -yaw * 0.5f;
    float s = ::sinf(half);
    float c = ::cosf(half);
    mm::Quat q(0.0f, s, 0.0f, c);
    mm::Vec3 r = q.rotate(a);
    {
        float length = r.length();
        if (length <= 1e-6f) {
            r = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            r.x = scale * r.x;
            r.y = scale * r.y;
            r.z = scale * r.z;
        }
    }
    {
        float length = b.length();
        if (length <= 1e-6f) {
            b = mm::Vec3::zero;
        } else {
            float scale = 1.0f / length;
            b.x = b.x * scale;
            b.y = b.y * scale;
            b.z = b.z * scale;
        }
    }
    float cosine = b.dot(r);
    if (cosine < -1.0f) {
        cosine = -1.0f;
    } else if (cosine > 1.0f) {
        cosine = 1.0f;
    }
    float angle = mm::acos(cosine);
    return b.cross(r).x < 0.0f ? -angle : angle;
}

float GimmickCamera::getYaw(const mm::Vec3& from, const mm::Vec3& to) {
    mm::Vec3 a(from.x, 0.0f, from.z);
    mm::Vec3 b(to.x, 0.0f, to.z);
    if (a.isZero() || b.isZero()) {
        return 0.0f;
    }
    float length = a.length();
    if (length <= 1e-6f) {
        a = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        a.x = a.x * scale;
        a.y = a.y * scale;
        a.z = a.z * scale;
    }
    length = b.length();
    if (length <= 1e-6f) {
        b = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        b.x = b.x * scale;
        b.y = b.y * scale;
        b.z = b.z * scale;
    }
    // the dot of copies: reading a and b in place puts the x term after the y term
    float cosine = mm::Vec3(b).dot(mm::Vec3(a));
    if (cosine < -1.0f) {
        cosine = -1.0f;
    } else if (cosine > 1.0f) {
        cosine = 1.0f;
    }
    float yaw = mm::acos(cosine);
    if (a.x * b.z - a.z * b.x < 0.0f) {
        yaw = 6.28318548f - yaw;
    }
    return yaw;
}

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

void GimmickCamera::update(const fw::UpdateInfo& info) {
    if (m_readEntry != nullptr) {
        if (m_auto) {
            play();
        }
        m_readEntry = nullptr;
    }
    if (m_playing) {
        updatePlayCamera(info);
    }
    updateParams();
}

void GimmickCamera::play() {
    if (!m_playing && !m_params.empty()) {
        m_playing = true;
        m_started = true;
        m_keyIndex = 0;
        m_keyTime = 0.0f;
        const Param& first = m_params[0];
        m_pos = first.m_pos;
        m_rot = first.m_rot;
        m_curFov = first.m_fov;
    }
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


mm::Vec3 GimmickCamera::calcAxisRotatePosition(const mm::Vec3& from, const mm::Vec3& to, float t, float scale,
                                               float offset) {
    float fromRadius = (mm::Vec3(0.0f, from.y, 0.0f) - from).length();
    float toRadius = (mm::Vec3(0.0f, to.y, 0.0f) - to).length();
    float radius = fromRadius + (toRadius - fromRadius) * offset + (toRadius - fromRadius) * scale * t;
    mm::Vec3 pos = from + (to - from) * offset + (to - from) * scale * t;
    mm::Vec3 axis(0.0f, pos.y, 0.0f);
    mm::Vec3 dir = pos - axis;
    float length = dir.length();
    if (length <= 1e-6f) {
        dir = mm::Vec3::zero;
    } else {
        float inv = 1.0f / length;
        dir.x = dir.x * inv;
        dir.y = dir.y * inv;
        dir.z = dir.z * inv;
    }
    return axis + dir * radius;
}

void GimmickCamera::onActivate() {}

mm::mtl::RTTI GimmickCamera::m_rtti("GimmickCamera", &::fw::Camera::m_rtti, nullptr);

}  // namespace gf
