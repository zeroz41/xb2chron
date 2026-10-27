#include "classes/ml/DrGlobalIBLPack.h"
#include "ml/DrEnvColiObj.h"
#include "ml/DrEnvColiMan.h"
#include "ml/DrGlobalIBLMan.h"
#include "ml/DrEnvColiMan.h"
#include "ml/DrGlobalIBLMan.h"
#include "classes/ml/DrMan.h"
#include "mtl/MemManager.h"

namespace ml {

DrEnvColiMan::~DrEnvColiMan() { clear(); }

void DrEnvColiMan::List::clear() {
    for (DrEnvColiObj* obj = m_head; obj;) {
        DrEnvColiObj* next = obj->m_next;
        if (obj->m_work) {
            mtl::MemManager::deallocate(obj->m_work, 0, false);
        }
        delete obj;
        obj = next;
    }
    m_head = nullptr;
    m_tail = nullptr;
}

void DrEnvColiMan::clear() {
    for (int i = 0; i < 2; i++) {
        m_stock[i].clear();
    }
    m_list.clear();
}

DrEnvColiObj* DrEnvColiMan::createObj(const void* resource) {
    DrEnvColiObj* obj = new (m_drMan->m_resHandle, nullptr, 0, 4, false) DrEnvColiObj(m_drMan);
    obj->setDataAdd(resource);
    m_stock[DrMan::s_nDblStockIdx].push_back(obj);
    return obj;
}

bool DrEnvColiMan::testEnvColi(DrEnvColiResult* result, const mm::Vec3& pos, float range) {
    if (!result) {
        result = &m_result;
        m_result.clear();
    }
    bool hit = false;
    for (DrEnvColiObj* obj = m_list.m_head; obj;) {
        DrEnvColiObj* next = obj->m_next;
        if (!(obj->m_flags & 3)) {
            bool objHit;
            if (obj->m_flags & 4) {
                objHit = false;
            } else if (obj->m_data) {
                objHit = obj->testTreeColi(result, obj->m_tree, pos, range);
            } else {
                objHit = false;
            }
            hit |= objHit;
        }
        obj = next;
    }
    return hit;
}

void DrEnvColiObj::setDataAdd(const void* data) {
    if (m_work) {
        mtl::MemManager::deallocate(m_work, 0, false);
        m_work = nullptr;
    }
    if (!data) {
        m_data = nullptr;
        return;
    }
    const EnvColiDataHeader* header = static_cast<const EnvColiDataHeader*>(data);
    m_data = static_cast<const unsigned char*>(data);
    m_list = m_data + header->m_listOfs;
    m_tree = reinterpret_cast<const EnvColiListTreeData*>(m_data + header->m_treeOfs);
    m_work = static_cast<EnvColiWork*>(
        mtl::MemManager::allocate(m_drMan->m_allocHandle, header->m_listNum * 0x30, 0x10, false, "no name", 0));
    for (int i = 0; i < header->m_listNum; i++) {
        switch (*reinterpret_cast<const unsigned short*>(m_list + i * 0x20 + 4)) {
        case 0: {
            const float* m = reinterpret_cast<const float*>(m_data + *reinterpret_cast<const unsigned int*>(m_list + i * 0x20));
            m_work[i].m_axis[0] = mm::Vec3(m[0], m[4], m[8]);
            m_work[i].m_axis[1] = mm::Vec3(m[1], m[5], m[9]);
            m_work[i].m_axis[2] = mm::Vec3(m[2], m[6], m[10]);
            break;
        }
        case 1: {
            const float* c = reinterpret_cast<const float*>(m_data + *reinterpret_cast<const unsigned int*>(m_list + i * 0x20));
            m_work[i].m_axis[0] = mm::Vec3(c[0], c[1], c[2]);
            m_work[i].m_axis[1] = mm::Vec3(c[0], c[1], c[2]);
            m_work[i].m_axis[2] = mm::Vec3(c[0], c[1], c[2]);
            break;
        }
        case 2: {
            const float* m = reinterpret_cast<const float*>(m_data + *reinterpret_cast<const unsigned int*>(m_list + i * 0x20));
            m_work[i].m_axis[0] = mm::Vec3(m[0], m[4], m[8]);
            m_work[i].m_axis[1] = mm::Vec3(m[1], m[5], m[9]);
            m_work[i].m_axis[2] = mm::Vec3(m[2], m[6], m[10]);
            break;
        }
        case 3: {
            const float* c = reinterpret_cast<const float*>(m_data + *reinterpret_cast<const unsigned int*>(m_list + i * 0x20));
            m_work[i].m_axis[0] = mm::Vec3(c[0], c[1], c[2]);
            m_work[i].m_axis[1] = mm::Vec3(c[0], c[1], c[2]);
            m_work[i].m_axis[2] = mm::Vec3(c[0], c[1], c[2]);
            break;
        }
        case 4: {
            const float* c = reinterpret_cast<const float*>(m_data + *reinterpret_cast<const unsigned int*>(m_list + i * 0x20));
            m_work[i].m_axis[0] = mm::Vec3(c[0], c[1], c[2]);
            m_work[i].m_axis[1] = mm::Vec3(c[0], c[1], c[2]);
            m_work[i].m_axis[2] = mm::Vec3(c[0], c[1], c[2]);
            break;
        }
        }
    }
}

void DrEnvColiObj::release() { m_flags |= 1 << DrMan::s_nDblStockIdx; }

bool DrEnvColiObj::envcoli_box(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work) {
    const float* d = reinterpret_cast<const float*>(data);
    mm::Vec3 center = *reinterpret_cast<const mm::Vec3*>(data + 0x30);
    mm::Vec3 diff = pos - center;
    float dx = diff.x;
    float dy = diff.y;
    float dz = diff.z;
    float r = d[15] + range;
    if (!(dx * dx + dy * dy + dz * dz <= r * r)) return false;
    float t = dx * work[0].x + dy * work[0].y + dz * work[0].z;
    if (!(d[16] + range >= t)) return false;
    if (!(-d[16] - range <= t)) return false;
    t = dx * work[2].x + dy * work[2].y + dz * work[2].z;
    if (!(d[18] + range >= t)) return false;
    if (!(-d[18] - range <= t)) return false;
    t = dx * work[1].x + dy * work[1].y + dz * work[1].z;
    if (!(d[17] + range >= t)) return false;
    return -d[17] - range <= t;
}

bool DrEnvColiObj::envcoli_sphere(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work) {
    const float* d = reinterpret_cast<const float*>(data);
    float dx = pos.x - work->x;
    float dy = pos.y - work->y;
    float dz = pos.z - work->z;
    float r = d[3] + range;
    return dx * dx + dy * dy + dz * dz <= r * r;
}

bool DrEnvColiObj::envcoli_cylinder(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work) {
    const float* d = reinterpret_cast<const float*>(data);
    mm::Vec3 center = *reinterpret_cast<const mm::Vec3*>(data + 0x30);
    mm::Vec3 diff = pos - center;
    float dx = diff.x;
    float dy = diff.y;
    float dz = diff.z;
    float r = d[15] + range;
    if (!(dx * dx + dy * dy + dz * dz <= r * r)) return false;
    float t = dx * work[1].x + dy * work[1].y + dz * work[1].z;
    if (!(d[17] + range >= t)) return false;
    if (!(-d[17] - range <= t)) return false;
    float u = dx * work[0].x + dy * work[0].y + dz * work[0].z;
    float v = dx * work[2].x + dy * work[2].y + dz * work[2].z;
    float rr = d[16] + range;
    return u * u + v * v <= rr * rr;
}

bool DrEnvColiObj::envcoli_notrot_box(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work) {
    const float* d = reinterpret_cast<const float*>(data);
    float dx = pos.x - work->x;
    float dy = pos.y - work->y;
    float dz = pos.z - work->z;
    float r = d[3] + range;
    if (!(dx * dx + dy * dy + dz * dz <= r * r)) return false;
    if (!(d[4] + range >= dx)) return false;
    if (!(-d[4] - range <= dx)) return false;
    if (!(d[6] + range >= dz)) return false;
    if (!(-d[6] - range <= dz)) return false;
    if (!(d[5] + range >= dy)) return false;
    return -d[5] - range <= dy;
}

bool DrEnvColiObj::envcoli_notrot_cylinder(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work) {
    const float* d = reinterpret_cast<const float*>(data);
    float dy = pos.y - work->y;
    if (!(d[4] + range >= dy)) return false;
    if (!(-d[4] - range <= dy)) return false;
    float dx = pos.x - work->x;
    float dz = pos.z - work->z;
    float r = d[3] + range;
    return dx * dx + dz * dz <= r * r;
}

bool (DrEnvColiObj::*DrEnvColiObj::s_pColiTest[5])(const unsigned char*, const mm::Vec3&, float, const mm::Vec3*) = {
    &DrEnvColiObj::envcoli_box,        &DrEnvColiObj::envcoli_sphere,          &DrEnvColiObj::envcoli_cylinder,
    &DrEnvColiObj::envcoli_notrot_box, &DrEnvColiObj::envcoli_notrot_cylinder,
};

DrGlobalIBLMan::DrGlobalIBLMan(DrMan* drMan, int view) : m_drMan(drMan), m_view(view) {
    for (int i = 0; i < 2; i++) {
        m_stock[i].m_head = nullptr;
        m_stock[i].m_tail = nullptr;
    }
    m_list.m_head = nullptr;
    m_list.m_tail = nullptr;
    m_release.m_head = nullptr;
    m_release.m_tail = nullptr;
}

DrGlobalIBLMan::~DrGlobalIBLMan() {
    for (int i = 0; i < 2; i++) {
        m_stock[i].clear();
    }
    m_release.clear();
    m_list.clear();
}

}  // namespace ml
