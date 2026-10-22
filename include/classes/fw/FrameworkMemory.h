#ifndef CLASSES_FW_FRAMEWORKMEMORY_H
#define CLASSES_FW_FRAMEWORKMEMORY_H

#include "classes/fw/MemHandlebaseAllocator.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/Array.h"
#include "mm/mtl/FixStr.h"
#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace fw {
// how FrameworkMemory::createSection makes a section (1.0.0's fw::MemorySectionInfo; 0x60 bytes); the field names
// are not the original's
class MemorySectionInfo {
public:
    MemorySectionInfo();

    unsigned int m_kind;  // the section's index: getMem(kind) and getAllocator(kind) hand it out
    mtl::ALLOC_HANDLE m_parent;  // the memory the section is made in (MemManager::create's first)
    unsigned long m_size;  // MemManager::create's size
    unsigned int m_alignment;  // MemManager::create's sixth (32 by default)
    bool m_flag;  // MemManager::create's fourth (true by default)
    mm::mtl::FixStr<64> m_name;  // MemManager::create's name; the section's hash is its CRC
    mtl::AllocatorType m_type;  // MemManager::create's type (1 by default)
};

// table 0x7100B3A238; the framework's memory sections (Singleton<FrameworkMemory>::getPtr keeps the one instance;
// its destructor is inline: FrameworkLauncher's copy is the one the module kept)
class FrameworkMemory : public ::mm::mtl::Singleton< ::fw::FrameworkMemory> {
public:
    // a section createSection made (1.0.0's fw::FrameworkMemory::SectionRegistInfo; 0xB8 bytes, reserve's stride)
    struct SectionRegistInfo {
        SectionRegistInfo() : m_hash(0) {}
        // frees the entry: no handle, no hash, the allocator over none (removeSection and removeChildSection; the name
        // is not the original's)
        void clear() {
            m_handle = mtl::ALLOC_HANDLE();
            m_hash = 0;
            m_allocator.setMemHandle(mtl::ALLOC_HANDLE());
        }

        MemorySectionInfo m_info;  // what createSection was given
        mtl::ALLOC_HANDLE m_handle;  // MemManager::create's (none: the section is free)
        unsigned int m_hash;  // mm::mtl::hashStrCrc of the section's name
        MemHandlebaseAllocator m_allocator;  // over m_handle: getAllocator(kind)
    };

    FrameworkMemory();
    virtual ~FrameworkMemory() {}  // slot 0
    // makes the sections' array of count sections in the memory of handle (once)
    static void initialize(mtl::ALLOC_HANDLE handle, unsigned int count);
    static void finalize();  // removes every section
    void removeSection(mtl::ALLOC_HANDLE handle);
    void removeChildSection(mtl::ALLOC_HANDLE handle);
    mtl::ALLOC_HANDLE createSection(const MemorySectionInfo& info);
    // the allocator of a kind of memory (the wind framework's objects come from kind 5)
    static mm::mtl::IAllocator* getAllocator(unsigned int kind);
    static mtl::ALLOC_HANDLE getMem(unsigned int kind);  // the handle of a kind of memory

    mm::mtl::Array<SectionRegistInfo> m_sections;  // one per kind; the names are not the original's
    bool m_isInitialized;  // initialize sets it, finalize clears it
    MemHandlebaseAllocator m_allocator;  // the sections' array comes from it
};
}  // namespace fw

#endif
