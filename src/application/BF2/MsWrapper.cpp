#include "lms/libms.h"
#include "ms/MsWrapper.h"
#include "mtl/MemManager.h"
#include <string.h>

namespace ms {

LMS_ProjectBinary* MsWrapper::m_pProj;
mtl::ALLOC_HANDLE MsWrapper::m_allocHandle;

void MsWrapper::init(mtl::ALLOC_HANDLE handle) {
    m_pProj = nullptr;
    m_allocHandle = handle;
    LMS_SetMemFuncs(myAlloc, myFree);
}

void* MsWrapper::myAlloc(unsigned long size) {
    return mtl::MemManager::allocate(m_allocHandle, size, 4, false, "no name", 0);
}

void MsWrapper::myFree(void* memory) {
    mtl::MemManager::deallocate(memory, 0, false);
}

void MsWrapper::regist(const char* data) {
    m_pProj = LMS_InitProject(data);
}

void MsWrapper::unregist() {
    LMS_CloseProject(m_pProj);
    m_pProj = nullptr;
}

int MsWrapper::getColorNum() {
    return LMS_GetColorNum(m_pProj);
}

bool MsWrapper::getColor(unsigned int index, LMSColor* color) {
    return LMS_GetColor(m_pProj, index, color) == 0;
}

bool MsWrapper::getColorName(unsigned int index, char* buffer, unsigned int size) {
    LMS_ProjectBinary* project = m_pProj;
    if (project->clr1 == -1) {
        return true;
    }
    const LMSiColorBlock* colors = static_cast<const LMSiColorBlock*>(project->common.blocks[project->clr1].data);
    if (colors->count <= static_cast<int>(index) || project->clb1 == -1) {
        return false;
    }
    const unsigned char* labels = static_cast<const unsigned char*>(project->common.blocks[project->clb1].data);
    const unsigned int* slots = reinterpret_cast<const unsigned int*>(labels);
    for (unsigned int i = 0; i < slots[0]; i++) {
        unsigned long offset = slots[static_cast<int>(i * 2 + 2)];
        unsigned char length = labels[offset];
        if (*reinterpret_cast<const unsigned int*>(labels + (offset + 1 + length)) == index) {
            if (length + 1 < static_cast<int>(size)) {
                memcpy(buffer, labels + (offset + 1), length);
                buffer[length] = '\0';
            }
            return true;
        }
    }
    return false;
}

unsigned short MsWrapper::getTagNum(int group) {
    return LMS_GetTagNum(m_pProj, group);
}

unsigned short MsWrapper::getTagParamListItemNum(int group, int tag, int param) {
    return LMS_GetTagListItemNum(m_pProj, group, tag, param);
}

const char* MsWrapper::getTagName(int group, int tag) {
    return LMS_GetTagName(m_pProj, group, tag);
}

const char* MsWrapper::getTagParamListItemName(int group, int tag, int param, int item) {
    return LMS_GetTagListItemName(m_pProj, group, tag, param, item);
}

}  // namespace ms
