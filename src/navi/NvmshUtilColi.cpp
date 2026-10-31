#define MM_LIB_FROM_NAVI
#include "classes/navi/NvmshResMan.h"
#include "classes/navi/NvmshManager.h"
#include "classes/ml/DevFileTh.h"
#include "ml/DevFileParamTh.h"
#include "ml/EventFileTh.h"
#include "mtl/MemManager.h"
#include "navi/NvmshAccUtil.h"
#include "navi/NvmshResData.h"
#include "navi/NvmshUtil.h"
#include "mm/Math.h"

namespace navi {

void NvmshResData::resetNavi() {
    const _NvMhAllReadObj* info = m_info;
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
    const _NvMhAllReadObj* info = m_info;
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

NvmshResMan::NvmshResMan(mtl::ALLOC_HANDLE handle, int size, int acSize)
    : m_memMan(nullptr), m_allHead(nullptr), m_worldHead(nullptr), m_conectHead(nullptr), m_flags(0),
      m_workBuf(nullptr), m_worldId(0), m_readBank(0), m_writeBank(1) {
    for (int i = 0; i < 4; i++) {
        m_fileHandles[i] = nullptr;
        m_fileData[i] = nullptr;
    }
    m_bufferSize = size;
    m_buffer = static_cast<unsigned char*>(mtl::MemManager::allocate(
        handle,
        m_bufferSize + acSize + 0x460, 0x40, false,
        "no name", 0));
    m_memMan = new (handle, nullptr, 0, 4, false) NvmshResMemMan(m_buffer, m_bufferSize, handle);
    m_workBuf = m_buffer + m_bufferSize;
    unsigned char* calc = m_buffer + (m_bufferSize + acSize);
    m_calcTbl = reinterpret_cast<_NaviCalcResTbl*>(calc);
    m_seachWork = reinterpret_cast<SeachWork*>(calc + sizeof(_NaviCalcResTbl) * 2);
    m_calcInfo = reinterpret_cast<_NaviCalcResInfo*>(calc + sizeof(_NaviCalcResTbl) * 2 + sizeof(SeachWork) * 2);
    memset(m_calcInfo, 0, sizeof(_NaviCalcResInfo));
    m_calcInfo->m_pos = mm::Vec3(100000.0f, 100000.0f, 100000.0f);
    m_calcInfo->m_max = mm::Vec3(-100000.0f, -100000.0f, -100000.0f);
    m_calcInfo->m_min = mm::Vec3(100000.0f, 100000.0f, 100000.0f);
    m_calcInfo->m_gridSize = 1.0f;
    m_calcInfo->m_invGridSize = 1.0f;
    m_calcTbl[0].m_info = m_calcInfo;
    m_calcTbl[1].m_info = m_calcInfo;
    for (int i = 0; i < 2; i++) {
        m_seachWork[i].m_bufs[0] = m_workBuf + i * 0x3f020;
        m_seachWork[i].m_sizes[0] = 0x3000;
        m_seachWork[i].m_bufs[2] = m_workBuf + i * 0x3f020 + 0x3000;
        m_seachWork[i].m_sizes[2] = 0x20;
        m_seachWork[i].m_bufs[1] = m_workBuf + i * 0x3f020 + 0x3020;
        m_seachWork[i].m_sizes[1] = 0x30000;
        m_seachWork[i].m_bufs[3] = m_workBuf + i * 0x3f020 + 0x33020;
        m_seachWork[i].m_bufs[4] = m_workBuf + i * 0x3f020 + 0x39020;
        m_seachWork[i].m_sizes[3] = 0x6000;
        m_seachWork[i].m_resMan = this;
    }
    m_acWork = reinterpret_cast<int*>(m_workBuf + 0x3f020 * 2);
    m_acWorkSize = acSize - 0x3f020 * 2;
    m_acWorkNum = (m_acWorkSize / 257) >> 2;
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

void NvmshResMan::setupResource(const unsigned char* resource, const char* name) {
    const _NvMhAllHead* all = reinterpret_cast<const _NvMhAllHead*>(resource);
    if (all->m_version == 0x1013) {
        m_fileName = name;
        int dot = m_fileName.findLast('.');
        if (dot != -1 && m_fileName.m_nLen > dot) {
            m_fileName.m_str[dot] = '\0';
            m_fileName.m_nLen = dot;
        }
        m_fileName += ".winvda";
        m_flags = (m_flags & 0xff00fff6) | 8;
        m_worldHead = nullptr;
        m_conectHead = nullptr;
        m_allHead = all;
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

void NvmshResMan::updateMemMove(const mm::Vec3& pos, bool flag, const mm::Vec3& target, int worldId) {
    if (m_flags & 0x10) {
        if (!(m_flags & 0xf0000)) {
            NvmshResMemMan* memMan = m_memMan;
            NvmshResMemObj* obj = memMan->m_usedList.m_head;
            NvmshResMemObj* next = nullptr;
            while (obj != nullptr) {
                next = obj->m_next;
                if (obj->m_flags & 2) {
                    break;
                }
                obj = next;
            }
            if (obj != nullptr && next != nullptr) {
                // the next block's data moves down into this one's place, the two swap places
                memcpy(obj->m_data, next->m_data, next->m_size);
                next->m_flags |= 4;
                unsigned char* data = obj->m_data;
                next->m_data = data;
                obj->m_data = data + next->m_size;
                NvmshResMemObj* prev = obj->m_prev;
                NvmshResMemObj* after = next->m_next;
                if (prev != nullptr) {
                    prev->m_next = next;
                } else {
                    memMan->m_usedList.m_head = next;
                }
                next->m_prev = prev;
                if (after != nullptr) {
                    after->m_prev = obj;
                } else {
                    memMan->m_usedList.m_tail = obj;
                }
                obj->m_prev = next;
                obj->m_next = after;
                next->m_next = obj;
                memMan->clearMemObj(obj);
            }
        }
        m_flags = (m_flags & ~0x30) | 0x20;
    }
    if (m_allHead != nullptr && !(m_flags & 1)) {
        resInfoUpdate(pos, flag, target, worldId);
        return;
    }
    unsigned int flags = m_flags;
    m_flags = flags & ~0x4000007;
    m_allHead = nullptr;
    m_worldHead = nullptr;
    m_conectHead = nullptr;
    if (flags & 8) {
        m_flags = (flags & ~0x400000f) | 4;
    }
    if (m_worldId != worldId) {
        m_worldId = worldId;
        m_flags |= 4;
    }
    if (m_flags & 4) {
        for (int i = 0; i < 26; i++) {
            m_resData[i].m_flags |= 4;
            m_resData[i].m_counter = 0;
        }
    }
    memset(m_calcTbl, 0, sizeof(_NaviCalcResTbl) * 2);
    m_calcTbl[0].m_info = m_calcInfo;
    m_calcTbl[1].m_info = m_calcInfo;
    m_freeNum = 0;
    for (long i = 0; i < 26; i++) {
        m_resData[i].update(m_memMan);
    }
}

void NvmshResMan::resInfoUpdate(const mm::Vec3& pos, bool flag, const mm::Vec3& target, int worldId) {
    for (int i = 0; i < 4; i++) {
        if ((m_flags & (0x110000 << i)) == (0x100000 << i)) {
            if (m_fileData[i] != nullptr) {
                m_fileData[i]->createNavi();
                m_fileData[i] = nullptr;
            }
            m_flags &= ~(0x100000 << i);
        }
    }
    unsigned int flags = m_flags;
    m_flags &= ~4;
    m_worldHead = nullptr;
    m_conectHead = nullptr;
    if (flags & 8) {
        m_flags = (flags & ~0xc) | 4;
    }
    if (m_worldId != worldId) {
        m_worldId = worldId;
        m_flags |= 4;
    }
    const _NvMhAllHead* all = m_allHead;
    const _NvMhAllWorldHead* worlds =
        reinterpret_cast<const _NvMhAllWorldHead*>(reinterpret_cast<const unsigned char*>(all) + all->m_worldOfs);
    int world = -1;
    for (int i = 0; i < all->m_worldNum; i++) {
        if (worlds[i].m_id == m_worldId) {
            world = i;
            break;
        }
    }
    if (m_flags & 4) {
        for (int i = 0; i < 26; i++) {
            m_resData[i].m_flags |= 4;
            m_resData[i].m_counter = 0;
        }
    }
    memset(m_calcTbl, 0, sizeof(_NaviCalcResTbl) * 2);
    m_calcTbl[0].m_info = m_calcInfo;
    m_calcTbl[1].m_info = m_calcInfo;
    if (world == -1) {
        m_flags &= ~0x4000002;
        m_freeNum = 0;
        for (int i = 0; i < 26; i++) {
            m_resData[i].update(m_memMan);
        }
        return;
    }
    m_worldHead = &worlds[world];
    calcNaviInfoUpdate(pos, m_worldHead, flag, target);
    if (all->m_conectOfs != 0) {
        m_conectHead = reinterpret_cast<const _NvMhAllWrdConectHead*>(
                           reinterpret_cast<const unsigned char*>(m_allHead) + all->m_conectOfs) +
                       world;
        calcConectInfoUpdate(m_worldHead, m_conectHead);
    }
    m_calcInfo->m_worldHead = m_worldHead;
    calcNaviObjUpdate();
}

void NvmshResMan::calcConectInfoUpdate(const _NvMhAllWorldHead* head, const _NvMhAllWrdConectHead* conect) {
    for (int i = 0; i < 2; i++) {
        if (conect->m_layerOfs[i] != 0) {
            const _NvMhConectData* data = reinterpret_cast<const _NvMhConectData*>(
                reinterpret_cast<const unsigned char*>(m_allHead) + conect->m_layerOfs[i]);
            const unsigned char* base = reinterpret_cast<const unsigned char*>(data);
            unsigned int size = (data->m_num / 32) * 4 + 4;
            int pad = 0;
            if (size % 32 != 0) {
                pad = 32 - size % 32;
            }
            m_calcTbl[i].m_conectSize = size + pad;
            _NaviCalcResTbl* tbl = &m_calcTbl[i];
            tbl->m_conect = data;
            tbl->m_conectBlocks[0] = base + data->m_blockOfs0;
            tbl->m_conectBlocks[1] = base + data->m_blockOfs1;
            tbl->m_conectBlocks[2] = base + data->m_blockOfs2;
            tbl->m_conectBlocks[3] = base + data->m_blockOfs3;
            tbl->m_conectBlocks[4] = base + data->m_blockOfs4;
            tbl->m_conectBlocks[5] = base + data->m_blockOfs7;
            if (data->m_blockNum5 != 0) {
                tbl->m_conectBlocks[6] = base + data->m_blockOfs5;
            }
            if (data->m_blockNum6 != 0) {
                tbl->m_conectBlocks[7] = base + data->m_blockOfs6;
            }
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
