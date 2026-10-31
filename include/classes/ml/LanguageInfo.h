#ifndef CLASSES_ML_LANGUAGEINFO_H
#define CLASSES_ML_LANGUAGEINFO_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mtl/MemManager.h"

namespace ml { class LanguageInfo; }

namespace ml {
// table 0x7100B785B8
class LanguageInfo : public ::mm::mtl::PtrSingleton< ::ml::LanguageInfo> {
public:
    // a buffer of room from a handle (initialize reserves room for 64 entries of 0x68 bytes; the destructor inlines
    // release). No symbol names the type: the type's and its members' names are not the original's (the same shape
    // as ProcDesktop::IconArray)
    struct Table {
        Table() : m_items(nullptr), m_count(0), m_capacity(0) {}
        ~Table() { release(); }
        void clear() { m_count = 0; }
        void release() {
            clear();
            if (m_mem.m_handle != 0 && m_items != nullptr) {
                mtl::MemManager::deallocate(m_items, 0, false);
                m_items = nullptr;
            }
            m_items = nullptr;
            m_capacity = 0;
            m_mem.m_handle = 0;
        }
        // room for count entries of 0x68 bytes from mem, emptied (inline: initialize inlines it; the entry type is
        // not known yet)
        void reserve(mtl::ALLOC_HANDLE mem, unsigned int count) {
            m_mem = mem;
            m_items = mtl::MemManager::allocate(mem, count * 0x68, 16, false, "no name", 0);
            m_count = 0;
            m_capacity = count;
        }
        void* m_items;            // 0x00
        unsigned int m_count;     // 0x08
        unsigned int m_capacity;  // 0x0C
        mtl::ALLOC_HANDLE m_mem;  // 0x10
    };
    LanguageInfo();
    virtual ~LanguageInfo();  // slot 0
    // the instance's table: room for 64 entries from the product memory (the handle passed is not used)
    static void initialize(mtl::ALLOC_HANDLE);
    void* pad_08;
    Table m_table;
    void* pad_28;
    unsigned int pad_30;
};
}  // namespace ml

#endif
