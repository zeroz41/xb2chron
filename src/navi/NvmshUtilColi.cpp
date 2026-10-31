#include "classes/navi/NvmshResMan.h"
#include "classes/navi/NvmshManager.h"
#include "classes/ml/DevFileTh.h"
#include "ml/EventFileTh.h"
#include "mtl/MemManager.h"
#include "navi/NvmshAccUtil.h"
#include "navi/NvmshResData.h"
#include "navi/NvmshUtil.h"
#include "mm/Math.h"

namespace navi {

void NvmshResData::resetNavi() {
    const ReadInfo* info = m_info;
    m_navi[0].clear();
    m_navi[1].clear();
    if (info->m_flags & 1) {
        m_navi[0].set(m_memObj->m_data);
        if (info->m_flags & 2) {
            m_navi[1].set(m_memObj->m_data + info->m_secondOfs);
        }
    } else if (info->m_flags & 2) {
        m_navi[1].set(m_memObj->m_data);
    }
}

void NvmshResData::createNavi() {
    const ReadInfo* info = m_info;
    if (info->m_flags & 1) {
        m_navi[0].create(m_memObj->m_data);
        if (info->m_flags & 2) {
            m_navi[1].create(m_memObj->m_data + info->m_secondOfs);
        }
    } else if (info->m_flags & 2) {
        m_navi[1].create(m_memObj->m_data);
    }
    m_counter = 0;
    m_flags = 0x11;
}

NvmshResMan::~NvmshResMan() {
    for (int i = 0; i < 4; i++) {
        if (m_fileHandles[i] != nullptr) {
            ml::DevFileTh::cancel(m_fileHandles[i], false);
        }
        m_fileHandles[i] = nullptr;
    }
    if (m_memMan != nullptr) {
        delete m_memMan;
        m_memMan = nullptr;
    }
    if (m_buffer != nullptr) {
        mtl::MemManager::deallocate(m_buffer, 0, false);
        m_buffer = nullptr;
    }
}

void NvmshResMan::releaseResource() {
    m_flags = (m_flags & 0xff00fff4) | 9;
    for (int i = 0; i < 26; i++) {
        m_resData[i].m_flags |= 4;
        m_resData[i].m_counter = 0;
    }
    for (int i = 0; i < 4; i++) {
        if (m_fileHandles[i] != nullptr) {
            ml::DevFileTh::cancel(m_fileHandles[i], false);
        }
        m_fileHandles[i] = nullptr;
        m_fileData[i] = nullptr;
    }
}

void NvmshResMan::update() {
    if (m_flags & 0x20) {
        m_flags &= ~0x20;
    } else if ((m_flags & 0x12) == 2) {
        resourceNaviUpdate();
    }
    if (!(m_flags & 0xf0000)) {
        NvmshResMemObj* obj = m_memMan->m_usedList.m_head;
        while (obj != nullptr) {
            bool used = obj->m_flags & 1;
            NvmshResMemObj* next = obj->m_next;
            if (!used) {
                if (next != nullptr) {
                    obj->m_flags |= 2;
                    m_flags |= 0x10;
                }
                break;
            }
            obj = next;
        }
    }
}

bool NvmshResMan::OnFileEvent(ml::EventFileTh* event) {
    if (event->m_kind == 2) {
        for (int i = 0; i < 4; i++) {
            if (m_fileHandles[i] == event->m_handle) {
                m_fileHandles[i] = nullptr;
                m_flags &= ~(0x10000 << i);
                break;
            }
        }
    }
    return true;
}

NvmshAccUtil::NvmshAccUtil() : m_manager(mm::mtl::PtrSingleton<NvmshManager>::sys()), m_flag(false) {}

bool NvmshAccUtil::testNaviColi(mm::Vec3& out, const mm::Vec3& pos, float param0, float param1, int param2) {
    return testNaviColiRange(out, pos, 0.01f, param0, param1, param2);
}

void NvmshUtilColi::setAttr(bool clear, unsigned int attr) {
    if (clear) {
        m_attr &= ~attr;
    } else {
        m_attr |= attr;
    }
}

bool NvmshUtilConect::seachSeamConectAStar(NvmshConectResult* result, bool flag) {
    m_result = result;
    m_flag = flag;
    return calcSeamAStar();
}

void NvmshUtil::getConectDirXY(int& x, int& y, const _NvMhMeshAdjacency* adj) {
    int dir = (adj->m_info >> 4) & 3;
    x = NAVI_UTIL_OFFX[dir];
    y = NAVI_UTIL_OFFY[dir];
}

void NvmshUtil::getPosCenterToLine(mm::Vec3& out, const mm::Vec3& pos, const mm::Vec3& a, const mm::Vec3& b,
                                   float min, float max) {
    mm::Vec3 d = b - a;
    float lenSq = d.dot(d);
    float t;
    if (mm::fabs(lenSq) >= 0.001f) {
        t = d.dot(pos - a) / lenSq;
    } else {
        t = 0.0f;
    }
    if (t < min) {
        t = min;
    }
    if (t > max) {
        t = max;
    }
    mm::Vec3 move = d * t;
    out.x = a.x + move.x;
    out.y = a.y + move.y;
    out.z = a.z + move.z;
}

void NvmshUtil::getPosCenterToXZLineLength(mm::Vec3& out, const mm::Vec3& pos, const mm::Vec3& a,
                                           const mm::Vec3& b, float len) {
    mm::Vec3 d = b - a;
    float lenSq = d.x * d.x + d.z * d.z;
    float t;
    float min = 0.5f;
    float max = 0.5f;
    if (mm::fabs(lenSq) >= 0.001f) {
        t = (d.x * (pos.x - a.x) + d.z * (pos.z - a.z)) / lenSq;
        if (len * len <= lenSq) {
            min = len / ::sqrtf(lenSq);
            max = 1.0f - min;
        }
    } else {
        t = 0.0f;
    }
    if (min > t) {
        t = min;
    }
    if (max < t) {
        t = max;
    }
    mm::Vec3 move = d * t;
    out.x = a.x + move.x;
    out.y = a.y + move.y;
    out.z = a.z + move.z;
}

bool NvmshUtil::getSubLineToLine(const mm::Vec3& pos, const mm::Vec3& dir, const mm::Vec3& a, const mm::Vec3& b) {
    float ex = b.x - a.x;
    float ez = b.z - a.z;
    float cross = dir.x * ez - ex * dir.z;
    if (cross <= 0.0001f && cross >= -0.0001f) {
        return false;
    }
    float px = pos.x - a.x;
    float pz = pos.z - a.z;
    float s = (ex * pz - ez * px) / cross;
    if (s < 0.0f || s > 1.0f) {
        return false;
    }
    float t = (dir.x * pz - dir.z * px) / cross;
    return !(t < 0.0f) && !(t > 1.0f);
}

bool NvmshUtil::getSubLineToLine(const mm::Vec3& pos, const mm::Vec3& dir, const mm::Vec3& a, const mm::Vec3& b,
                                 float min, float max) {
    float ex = b.x - a.x;
    float ez = b.z - a.z;
    float cross = dir.x * ez - ex * dir.z;
    if (cross <= 0.0001f && cross >= -0.0001f) {
        return false;
    }
    float px = pos.x - a.x;
    float pz = pos.z - a.z;
    float s = (ex * pz - ez * px) / cross;
    if (s < min || s > max) {
        return false;
    }
    float t = (dir.x * pz - dir.z * px) / cross;
    return !(t < min) && !(t > max);
}

NvmshUtilConect::NvmshUtilConect() : m_running(false) {}

bool NvmshUtilConect::seachConectAStar(NvmshConectResult* result, bool flag) {
    m_result = result;
    m_flag = flag;
    return calcConectAStar();
}

NvmshUtilSeach::NvmshUtilSeach() : m_count(0) {}

bool NvmshUtilSeach::seachAStar(NvmshAStarResult* result) {
    m_result = result;
    result->m_count = 0;
    return calcAStar();
}

const int NvmshUtil::NAVI_UTIL_OFFX[4] = {1, 0, -1, 0};
const int NvmshUtil::NAVI_UTIL_OFFY[4] = {0, 1, 0, -1};

// Proposed names, not the original's: the symbols leave them unnamed (lbl_71009D5058, lbl_71009D5061,
// lbl_71009D5071, lbl_71009D508A). NAVI_UTIL_ADJTBL's four entries point at them.
static const unsigned char s_adjTbl3[3 * 3] = {0, 0, 1, 0, 0, 2, 1, 2, 0};
static const unsigned char s_adjTbl4[4 * 4] = {0, 0, 1, 2, 0, 0, 3, 4, 1, 3, 0, 5, 2, 4, 5, 0};
static const unsigned char s_adjTbl5[5 * 5] = {0, 0, 1, 2, 3, 0, 0, 4, 5, 6, 1, 4, 0, 7, 8,
                                               2, 5, 7, 0, 9, 3, 6, 8, 9, 0};
static const unsigned char s_adjTbl6[6 * 6] = {0, 0, 1, 2,  3,  4,  0, 0,  5,  6,  7,  8,  1,  5, 0,  9,  10, 11,
                                               2, 6, 9, 0, 12, 13, 3, 7, 10, 12, 0, 14, 4, 8, 11, 13, 14, 0};

const unsigned char* NvmshUtil::NAVI_UTIL_ADJTBL[4] = {s_adjTbl3, s_adjTbl4, s_adjTbl5, s_adjTbl6};

}  // namespace navi
