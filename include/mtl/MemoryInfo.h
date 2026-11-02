#ifndef MTL_MEMORYINFO_H
#define MTL_MEMORYINFO_H

namespace mtl {

// an allocator's figures (IMemAllocator::memoryInfo/log fill it). The struct name is the original's (the slots'
// signatures); the field names are inferred from DlAllocator's mspace walk (0x71006EB61C), which fills 0..0x2C
struct MemoryInfo {
    // every field zeroed, the alignment gap at 0x2C left alone (MemManager::Region::maxAllocSize's local, 1.0.0)
    MemoryInfo()
        : m_totalSize(0), m_freeSize(0), m_usedSize(0), m_maxFreeSize(0), m_usedRate(0), m_chunkUsedRate(0),
          m_footerCount(0), m_top(nullptr), m_name(nullptr), pad_40(0) {}

    unsigned long m_totalSize;  // the mspace's max_footprint
    unsigned long m_freeSize;  // m_totalSize less the chunks in use
    long m_usedSize;  // footprint less the free chunks and top
    unsigned long m_maxFreeSize;  // the largest free chunk (or untouched tail)
    float m_usedRate;  // m_usedSize in percent of m_totalSize
    float m_chunkUsedRate;  // the chunks in use in percent of all chunks
    int m_footerCount;  // the chunks in use that carry a DlAllocator footer
    void* m_top;  // +0x30: the region's first address (MemManager::Region::memoryInfo; the name is inferred)
    const char* m_name;  // +0x38: the allocator's getName (DlAllocator::memoryInfo)
    unsigned long pad_40;  // +0x40: zeroed by the constructor; no kept code fills it
};

}  // namespace mtl

#endif
