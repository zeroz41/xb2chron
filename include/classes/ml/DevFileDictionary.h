#ifndef CLASSES_ML_DEVFILEDICTIONARY_H
#define CLASSES_ML_DEVFILEDICTIONARY_H

#include "mtl/AllocHandle.h"
#include "mtl/MemManager.h"

namespace ml {
// The allocator a DevFileDictionary<int, DevFileDicAllocator, -1, -2, true> uses (symbol-named template argument);
// DevFileArchiver keeps one at 0x490 and its archives point at it. The member's name is not the original's.
class DevFileDicAllocator {
public:
    explicit DevFileDicAllocator(mtl::ALLOC_HANDLE handle) : m_handle(handle) {}

    mtl::ALLOC_HANDLE m_handle;  // 0x0: DevFileArchiver's constructor copies its handle here
};

// A file dictionary loaded from an archive's table (symbol-named: clear, loadFromMemory, restoreNinfo, reallocArray).
// Layout from DevFileArchiver::addArchive (0x45 bytes zeroed, then the allocator pointer at 0x48).
template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
class DevFileDictionary {
public:
    ~DevFileDictionary() {
        clear(false);
    }
    void clear(bool);
    void loadFromMemory(void* data, unsigned long, void* table, unsigned long tableSize);
    void restoreBlock();
    void restoreNinfo();

    // The names of these fields are not the original's (no symbol names them); what they hold is read from
    // loadFromMemory (0x71006BCBDC) and clear.
    void* m_table;              // 0x0: loadFromMemory's third argument; clear frees it only when the dictionary owns it
    void* m_data;               // 0x8: loadFromMemory's first argument (its first word is the entry count)
    int* m_work;                // 0x10: 4 bytes loadFromMemory allocates with m_allocator's handle
    void* m_blocks;             // 0x18: loadFromMemory calls restoreBlock while it is null
    void* m_ninfo;              // 0x20: loadFromMemory calls restoreNinfo while it is null
    unsigned long m_used;       // 0x28
    int m_freeNum;              // 0x30
    int m_capacity;             // 0x34: loadFromMemory copies m_tableSize here
    int m_tableSize;             // 0x38: loadFromMemory's fourth argument
    int m_entryNum;             // 0x3C: loadFromMemory stores m_data's first word
    int m_state;                // 0x40: 1 after loadFromMemory
    bool m_external;            // 0x44: set by loadFromMemory (the table is not the dictionary's to free)
    unsigned char pad_45[0x3];
    Allocator* m_allocator;  // 0x48 (the name is not the original's)
};

template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
void DevFileDictionary<Key, Allocator, EmptyKey, DeletedKey, Flag>::clear(bool) {
    if (m_external) {
        m_table = nullptr;
        m_data = nullptr;
    } else if (m_table != nullptr) {
        mtl::MemManager::deallocate(m_table, 0, false);
        m_table = nullptr;
    }
    if (m_data != nullptr) {
        mtl::MemManager::deallocate(m_data, 0, false);
        m_data = nullptr;
    }
    if (m_work != nullptr) {
        mtl::MemManager::deallocate(m_work, 0, false);
        m_work = nullptr;
    }
    if (m_blocks != nullptr) {
        mtl::MemManager::deallocate(m_blocks, 0, false);
        m_blocks = nullptr;
    }
    if (m_ninfo != nullptr) {
        mtl::MemManager::deallocate(m_ninfo, 0, false);
        m_ninfo = nullptr;
    }
    m_used = 0;
    m_freeNum = 0;
    m_capacity = 0;
    m_tableSize = 0;
    m_entryNum = 0;
    m_state = 0;
    m_external = false;
}

template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
void DevFileDictionary<Key, Allocator, EmptyKey, DeletedKey, Flag>::loadFromMemory(void* data, unsigned long, void* table,
                                                                                   unsigned long tableSize) {
    clear(false);
    m_table = table;
    m_data = data;
    m_work = static_cast<int*>(mtl::MemManager::allocate(m_allocator->m_handle, 4, 8, false, "no name", 0));
    m_tableSize = tableSize;
    m_external = true;
    *m_work = 0;
    if (m_blocks != nullptr && m_ninfo != nullptr) {
        return;
    }
    if (m_ninfo == nullptr) {
        restoreBlock();
    }
    if (m_blocks == nullptr) {
        restoreNinfo();
    }
    m_capacity = m_tableSize;
    m_entryNum = *static_cast<int*>(m_data);
    m_state = 1;
}
}  // namespace ml

#endif
