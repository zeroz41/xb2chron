#include "gf/GfSlotMapping.h"
#include "gf/GfSlotAll.h"
#include "classes/gf/GfSlotAllocator.h"
#include "classes/gf/GfAllocator.h"
#include "mtl/MemManager.h"
#include "classes/gf/GfAssetPack.h"
#include "classes/gf/GfInfo.h"
#include "classes/fw/SoundManager.h"
#include "classes/gf/GfSlotBase.h"
#include "gf/GfAssetUtil.h"
#include "fw/UpdateInfo.h"
#include "gf/GfSetupParam.h"
#include "algorithm"

namespace gf {

inline bool GfSlotMapping::BiggerPrio::operator()(const REQ& a, const REQ& b) const {
    return a.m_pack->m_prio > b.m_pack->m_prio;
}

unsigned long GfSlotMapping::getAllSize() {
    return 0x24eb0000;
}

void GfSlotMapping::createMapping(const GfSetupParam& param) {
    destroyMapping();
    if (param.pad_1c == 0) {
        m_slotAll->createSlot(static_cast<GfAssetType>(3), 1, "SLOT_MA", 0x22a0000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(4), 8, "SLOT_PC", 0x28000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(5), 64, "SLOT_PM", 0x78000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(6), 22, "SLOT_BL", 0x28000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(7), 272, "SLOT_BM", 0x4a000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(8), 168, "SLOT_WP", 0x20000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(16), 192, "SLOT_WM", 0x50000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(9), 512, "SLOT_WE", 0x20000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(10), 160, "SLOT_EN", 0x4000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(11), 480, "SLOT_EM", 0x20000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(12), 160, "SLOT_EA", 0x2000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(13), 240, "SLOT_EF", 0x20000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(14), 32, "SLOT_FO", 0x20000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(15), 300, "SLOT_MO", 0x30000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(17), 304, "SLOT_OP", 0x14000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(18), 1304, "SLOT_TP", 0x10000, m_slotAllocator, false);
        m_slotAll->createSlot(static_cast<GfAssetType>(19), 150, "SLOT_SE", 0x40000, m_slotAllocator, false);
    }
    unsigned long size;
    void* buffer;
    if (m_slotAll->getSlotInfo(buffer, size, static_cast<GfAssetType>(18))) {
        if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
            sound->attachPoolMemory(buffer, size);
        }
    }
    if (m_slotAll->getSlotInfo(buffer, size, static_cast<GfAssetType>(19))) {
        if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
            sound->attachPoolMemory(buffer, size);
        }
    }
}

void GfSlotMapping::destroyMapping() {
    unsigned long size;
    void* buffer;
    if (m_slotAll->getSlotInfo(buffer, size, static_cast<GfAssetType>(19))) {
        if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
            sound->detachPoolMemory(buffer, size);
        }
    }
    if (m_slotAll->getSlotInfo(buffer, size, static_cast<GfAssetType>(18))) {
        if (fw::SoundManager* sound = mm::mtl::PtrSingleton<fw::SoundManager>::get()) {
            sound->detachPoolMemory(buffer, size);
        }
    }
    m_slotAll->destroyMapping();
}

GfSlotMapping::GfSlotMapping() : m_slotAll(nullptr), m_memTop(0), m_memEnd(0) {
#line 382
    m_slotAll = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSlotAll();
    m_slotAllocator = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) GfSlotAllocator();
}

GfSlotMapping::~GfSlotMapping() {
    if (m_slotAllocator != nullptr) {
        delete m_slotAllocator;
        m_slotAllocator = nullptr;
    }
    if (m_slotAll != nullptr) {
        delete m_slotAll;
        m_slotAll = nullptr;
    }
}

void GfSlotMapping::setup(const GfSetupParam& param, GfAllocator* allocator, unsigned long size) {
    m_slotAllocator->setupSizeAlloc("SLOT_ALL", allocator, size, 0x2000, false);
    createMapping(param);
    m_memTop = (unsigned long)mtl::MemManager::getTopAdr(getAllocator(ALLOCATOR(3))->getMemHandle());
    m_memEnd = m_memTop + mtl::MemManager::getTotalSize(getAllocator(ALLOCATOR(3))->getMemHandle());
}

void GfSlotMapping::destroy() {
    while (m_requests.size() != 0) {
        GfSleep(1);
    }
    destroyMapping();
    m_slotAllocator->destroy();
}

void GfSlotMapping::update(const fw::UpdateInfo& info) {
    updateSlotRequest(info);
}

bool GfSlotMapping::setupFreeSlot(REQ* req) {
    GfSlotBase* slot;
    if (req->m_pack->m_slotHandle != reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
        slot = m_slotAll->getSlot(req->m_pack->m_slotHandle);
    } else {
        unsigned int prio = req->m_pack->m_prio;
        GfAssetType type = req->m_pack->m_files.m_type;
        if (GfAssetManager::isExistSameAsset(req->m_pack)) {
            return false;
        }
        unsigned long slotSize = m_slotAll->getByteSizeBySlotNum(type, req->m_pack->m_slotNum);
        unsigned long size = req->m_pack->getNeedLoadFileSize(m_slotAll->getBlockSize(type), false);
        if (size > slotSize) {
            m_slotAll->isMemoryDebug(type);
        }
        GfAssetPack* pack = req->m_pack;
        pack->m_needSlotNum = m_slotAll->getSlotNumByByteSize(type, size);
        GF_SLOT_HANDLE* handle = m_slotAll->setupSlotByte(type, size, prio);
        if (handle == reinterpret_cast<GF_SLOT_HANDLE*>(-1)) {
            GfAssetManager::destroySlotCache(type);
            if (req->m_retry < 999) {
                req->m_retry++;
            }
            if (req->m_pack->m_useCount < 2u) {
                return GfAssetUtil::isObjectDestroy(req->m_handle);
            }
            return false;
        }
        slot = m_slotAll->getSlot(handle);
        req->m_pack->m_slotHandle = handle;
    }
    GfAssetManager::loadStart(req->m_pack, slot);
    return true;
}

void GfSlotMapping::requestSlotLoad(GF_ASSET_HANDLE* handle, GfAssetPack* pack) {
    for (const REQ& req : m_requests) {
        if (req.m_pack == pack) {
            return;
        }
    }
    pack->addRef();
    REQ req = {};
    req.m_handle = handle;
    req.m_pack = pack;
    req.m_retry = 0;
    req.m_timeout = 0.5f;
    m_requests.push_back(req);
    std::sort(m_requests.begin(), m_requests.end(), BiggerPrio());
}

bool GfSlotMapping::isRequest(const GfAssetPack* pack) const {
    for (const REQ& req : m_requests) {
        if (req.m_pack == pack) {
            return true;
        }
    }
    return false;
}

void GfSlotMapping::releaseSlot(GF_SLOT_HANDLE* handle) {
    m_slotAll->releaseSlot(handle);
}

bool GfSlotMapping::isExistData(GF_SLOT_HANDLE* handle) const {
    return m_slotAll->isExistData(handle);
}

void* GfSlotMapping::allocateSize(unsigned long size, unsigned long alignment) {
    return m_slotAll->allocateSize(static_cast<GfAssetType>(18), size, alignment);
}

bool GfSlotMapping::deallocateSize(void* memory) {
    if (m_memTop > (unsigned long)memory) {
        return false;
    }
    if (m_memEnd > (unsigned long)memory) {
        m_slotAll->deallocateSize(memory);
        return true;
    }
    return false;
}

}  // namespace gf

// requestSlotLoad's std::sort instantiates the libc++ sort core for the requests.
template void std::__sort<gf::GfSlotMapping::BiggerPrio&, gf::GfSlotMapping::REQ*>(
    gf::GfSlotMapping::REQ*, gf::GfSlotMapping::REQ*, gf::GfSlotMapping::BiggerPrio&);
