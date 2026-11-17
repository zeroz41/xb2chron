#define MM_LIB_FROM_GRLIB
#include "classes/grlib/CGLibManager.h"
#include "classes/grlib/context/CGLibSystemContext.h"
#include "grlib/CGLibMemHandle.h"
#include "ml/font/File.h"
#include "mtl/MemManager.h"

File::File(void* data, unsigned long size) {
    m_data = data;
    m_err = 1;
    m_pos = 0;
    m_size = size;
    if (!data) {
        m_err = 0;
    }
}

File::~File() {
    if (m_data) {
        m_data = nullptr;
    }
}

unsigned char File::read_byte() {
    unsigned char value = *(static_cast<unsigned char*>(m_data) + m_pos);
    m_pos += 1;
    return value;
}

unsigned short File::read_le16() {
    unsigned short value = *reinterpret_cast<unsigned short*>(static_cast<unsigned char*>(m_data) + m_pos);
    m_pos += 2;
    return value;
}

unsigned int File::read_le32() {
    unsigned int value = *reinterpret_cast<unsigned int*>(static_cast<unsigned char*>(m_data) + m_pos);
    m_pos += 4;
    return value;
}

unsigned long File::pos() {
    return m_pos;
}

unsigned long File::pos(unsigned long pos) {
    m_pos = pos;
    return 0;
}

bool File::is_eof() {
    return m_pos >= m_size;
}

// ---- grlib/CGLibManager.cpp (the split puts it in this unit) ----

namespace grlib {

int CGLibManager::s_nDblNowIdx;
int CGLibManager::s_nStkNowIdx = 1;
int CGLibManager::s_nTriNowIdx;
bool CGLibManager::s_nReleaseOk = true;

CGLibManager::CGLibManager() : m_pSystemContext(nullptr) {
    s_nReleaseOk = false;
}

CGLibManager::~CGLibManager() {
    if (m_pSystemContext) {
        delete m_pSystemContext;
        m_pSystemContext = nullptr;
    }
    s_nReleaseOk = true;
}

bool CGLibManager::isRelease() {
    if (m_pSystemContext) {
        return m_pSystemContext->isRelease();
    }
    return false;
}

bool CGLibManager::deviceInit() {
    if (m_pSystemContext) {
        return true;
    }
    CGLibMemHandle::ArgMemInfo info;
    info.m_memSize = 0x200000;
    info.m_fetSize = 0x40000;
    info.m_cntSize = 0x80000;
    info.m_etc128Size = context::CGLibSystemContext::ETCBUFFER_128_SIZE;
    info.m_etc256Size = context::CGLibSystemContext::ETCBUFFER_256_SIZE;
    info.m_etc512Size = context::CGLibSystemContext::ETCBUFFER_512_SIZE;
    info.m_etc768Size = context::CGLibSystemContext::ETCBUFFER_768_SIZE;
    info.m_etc1024Size = context::CGLibSystemContext::ETCBUFFER_1024_SIZE;
    info.m_topSize = 0x2800000;
    info.m_pxlSize = 0x16A00000;
    info.m_shdSize = 0x200000;
    info.m_vtxSize = 0x2A00000;
    info.m_uniSize = 0x1C00000;
    CGLibMemHandle::setup(info);
    bool result = init();
    if (!m_pSystemContext) {
        m_pSystemContext = new (CGLibMemHandle::s_hMemHandle, nullptr, 0, 4, false) context::CGLibSystemContext;
    }
    m_pSystemContext->setup();
    return result;
}

bool CGLibManager::deviceRelease() {
    bool result = true;
    if (m_pSystemContext) {
        result = m_pSystemContext->cleanup();
        if (m_pSystemContext) {
            delete m_pSystemContext;
            m_pSystemContext = nullptr;
        }
        CGLibDeviceObj::release();
        CGLibMemHandle::release();
    }
    s_nReleaseOk = true;
    return result;
}

void CGLibManager::begin() {
    m_pSystemContext->m_display.updateSignaled();
    context::CGLibSystemContext* context = m_pSystemContext;
    if (context->m_display.m_needWait) {
        int dbl = s_nDblNowIdx;
        s_nDblNowIdx = dbl == 0;
        s_nStkNowIdx = dbl != 0;
        s_nTriNowIdx = s_nTriNowIdx > 1 ? 0 : s_nTriNowIdx + 1;
    }
    context->begin();
}

bool CGLibManager::isReleaseOk() {
    return s_nReleaseOk;
}

void CGLibManager::end() {
    m_pSystemContext->end();
}

void CGLibManager::swap() {
    swapChain();
}

void CGLibManager::tail() {}

unsigned long CGLibManager::getGpuTimeStamp() const {
    return m_pSystemContext->m_gpuTimeStamp.m_time;
}

}  // namespace grlib
