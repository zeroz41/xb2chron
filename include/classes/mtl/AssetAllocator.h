#ifndef CLASSES_MTL_ASSETALLOCATOR_H
#define CLASSES_MTL_ASSETALLOCATOR_H

#include "classes/mtl/IMemAllocator.h"
#include "mm/mtl/FixedList.h"

namespace mtl {

// table 0x7100B794E8: an allocator handing out blocks of a memory create is given, keeping its free and used
// chunks in two fixed lists of N (MemManager::createAllocator's type 2 is AssetAllocator<1024>, 0x110B0 bytes).
// Its members are emitted where createAllocator instantiates its table. Member names other than m_name are not the
// original's
template <int N>
class AssetAllocator : public IMemAllocator {
public:
    // a run of blocks (getAllocSize: m_numBlocks blocks of 16 bytes; its address m_top + m_blockSize * m_block);
    // allocate keeps its file and line in the run it hands out
    struct SMemChunk {
        const char* m_file;
        short m_line;
        unsigned short pad_A;  // allocate zeroes it
        unsigned int m_block;  // the run's first block
        int m_numBlocks;  // its length in blocks
        unsigned char pad_14[0x4];
    };

    AssetAllocator() : m_top(nullptr), m_size(0), m_blockSize(0x80), m_totalBlocks(0) {}
    virtual ~AssetAllocator() {}  // slot 0
    virtual void create(void* p, unsigned long size, const char* pszName);  // slot 2
    virtual void destroy();  // slot 3
    virtual AllocatorType getType() const { return static_cast<AllocatorType>(2); }  // slot 4
    virtual void* allocate(unsigned long size, unsigned long alignment) {  // slot 5
        return allocate(size, alignment, "", 0);
    }
    virtual void* allocate(unsigned long size, unsigned long alignment, const char* file, int line);  // slot 6
    virtual void* allocate_tail(unsigned long size, unsigned long alignment, const char* file, int line);  // slot 7
    virtual void deallocate(void* p, unsigned long size);  // slot 8
    virtual void* reallocate(void* p, unsigned long size) { return nullptr; }  // slot 9
    virtual void log(MemoryInfo* info, bool flag) const {}  // slot 10
    virtual const char* getName() const { return m_name.m_str; }  // slot 13
    virtual bool hasMemory(const void* p) const;  // slot 14
    virtual unsigned long getAllocSize(const void* p) const;  // slot 15
    virtual void memoryInfo(MemoryInfo* info) const;  // slot 16
    virtual void getMemImage(MEMIMAGE_HEAD* head) const;  // slot 17
    virtual int getMemInfo1(MemoryInfo1* info, unsigned int flags) const;  // slot 18
    virtual bool empty() const { return m_name.m_str[0] == '\0'; }  // slot 19
    virtual bool valid() const { return m_name.m_str[0] != '\0'; }  // slot 20
    virtual bool dummy() const { return m_name.m_str[0] != '\0'; }  // slot 21

    typedef mm::mtl::FixedList<SMemChunk, N> ChunkList;

    mm::mtl::FixStr<32> m_name;  // create's name
    ChunkList m_freeList;  // the runs not handed out (hasMemory walks it first)
    ChunkList m_usedList;  // the runs handed out (getAllocSize finds an address here)
    unsigned char* m_top;  // the memory create was given
    unsigned long m_size;  // its size, whole blocks
    unsigned long m_blockSize;  // bytes per block (create sets 16)
    unsigned long m_totalBlocks;  // blocks in the memory
};

}  // namespace mtl

#endif
