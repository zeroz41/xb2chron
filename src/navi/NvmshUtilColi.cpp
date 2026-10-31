#include "classes/navi/NvmshResMan.h"
#include "classes/navi/NvmshManager.h"
#include "classes/ml/DevFileTh.h"
#include "ml/EventFileTh.h"
#include "mtl/MemManager.h"
#include "navi/NvmshAccUtil.h"
#include "navi/NvmshResData.h"
#include "navi/NvmshUtil.h"

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

}  // namespace navi
