#ifndef CLASSES_MTL_DLALLOCATOR_H
#define CLASSES_MTL_DLALLOCATOR_H

#include "classes/mtl/IMemAllocator.h"
#include "ml/CriticalSection.h"
#include "mm/mtl/IntrusiveList.h"
#include "mtl/CallStackInfo.h"

namespace mtl {

// table 0x7100B79320: an allocator over a dlmalloc mspace made in the memory create is handed (MemManager::
// createAllocator's type 1; 0x88 bytes). Member names other than m_name are not the original's
class DlAllocator : public IMemAllocator {
public:
    // what allocate puts at the end of every allocation (initFooter, 1.0.0): the name and field names are
    // not the original's
    struct Footer {
        unsigned int m_magic;  // FOOTER_MAGIC
        long pad_8;  // initFooter's last argument
        CallStackInfo* m_info;  // CallStackManager::regist's record, or null
    };
    static const unsigned int FOOTER_MAGIC = 0x44434241;  // "ABCD" (name not the original's)

    // 1.0.0: the footer at the end of allocation p and the offset it is at (null and 0 when p has no room for one)
    static Footer* getNewInfo(const void* p, unsigned long& size);

    DlAllocator() : m_mspace(nullptr), m_base(nullptr), m_size(0) {}
    virtual ~DlAllocator();  // slot 0
    virtual void create(void* p, unsigned long size, const char* pszName);  // slot 2
    virtual void destroy();  // slot 3
    virtual AllocatorType getType() const { return static_cast<AllocatorType>(1); }  // slot 4
    virtual void* allocate(unsigned long size, unsigned long alignment);  // slot 5
    virtual void* allocate(unsigned long size, unsigned long alignment, const char* file, int line);  // slot 6
    virtual void deallocate(void* p, unsigned long size);  // slot 8
    virtual void* reallocate(void* p, unsigned long size);  // slot 9
    virtual void log(MemoryInfo* info, bool flag) const;  // slot 10
    virtual void log_callSTack(void* p) const;  // slot 11
    virtual void checkLeakMemory();  // slot 12
    virtual const char* getName() const;  // slot 13
    virtual bool hasMemory(const void* p) const;  // slot 14
    virtual unsigned long getAllocSize(const void* p) const;  // slot 15
    virtual void memoryInfo(MemoryInfo* info) const;  // slot 16
    virtual void getMemImage(MEMIMAGE_HEAD* head) const;  // slot 17
    virtual int getMemInfo1(MemoryInfo1* info, unsigned int flags) const;  // slot 18
    virtual bool empty() const { return m_name.m_str[0] == '\0'; }  // slot 19
    virtual bool valid() const { return m_name.m_str[0] != '\0'; }  // slot 20
    virtual bool dummy() const { return m_name.m_str[0] != '\0' && m_mspace == nullptr; }  // slot 21

    mm::mtl::FixStr<32> m_name;  // create's name
    void* m_mspace;  // the dlmalloc mspace create made in m_base (destroy forgets it)
    void* m_base;  // the memory create was handed
    unsigned long m_size;  // its size
    mm::mtl::IntrusiveListBase m_list;  // (its use is not read yet)
    ml::CriticalSection m_cs;
};

}  // namespace mtl

#endif
