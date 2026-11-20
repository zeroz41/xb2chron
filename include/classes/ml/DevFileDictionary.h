#ifndef CLASSES_ML_DEVFILEDICTIONARY_H
#define CLASSES_ML_DEVFILEDICTIONARY_H

#include <string.h>

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

// A file dictionary loaded from an archive's table (symbol-named: clear, loadFromMemory, restoreBlock, restoreNinfo,
// reallocArray<block>/<ninfo>, findImpl). Layout from DevFileArchiver::addArchive (0x45 bytes zeroed, then the
// allocator pointer at 0x48). The code follows the cedar double-array trie (da<value, NO_VALUE, NO_PATH, ORDERED>:
// _restore_block, _restore_ninfo, _realloc_array, _find), with the allocator's MemManager calls for realloc; the
// cedar names of the fields are inferred, not the original's.
template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
class DevFileDictionary {
public:
    // A trie node (8 bytes, m_table's element; the struct name is not the original's): base, or a leaf's value or
    // the negated tail offset; check is the parent index (negative when the node is empty).
    struct node {
        int m_base;
        int m_check;
    };
    // The per-node first-child/next-sibling labels (symbol-named by reallocArray<ninfo>; 2 bytes).
    struct ninfo {
        ninfo() : m_sibling(0), m_child(0) {}
        unsigned char m_sibling;  // 0x0
        unsigned char m_child;    // 0x1
    };
    // One 256-node block's free-list entry (symbol-named by reallocArray<block>; 0x14 bytes). The constructor's
    // values are reallocArray<block>'s static T0 (0, 0, 256, 257, 0, 0).
    struct block {
        block() : m_prev(0), m_next(0), m_num(256), m_reject(257), m_trial(0), m_ehead(0) {}
        int m_prev;      // 0x0
        int m_next;      // 0x4
        short m_num;     // 0x8: empty nodes in the block
        short m_reject;  // 0xA
        int m_trial;     // 0xC
        int m_ehead;     // 0x10: first empty node
    };

    ~DevFileDictionary() {
        clear(false);
    }
    void clear(bool);
    void loadFromMemory(void* data, unsigned long, void* table, unsigned long tableSize);
    void restoreBlock();
    void restoreNinfo();
    template <typename T>
    void reallocArray(T*& p, int sizeN, int sizeP);
    Key findImpl(const char* key, unsigned long& from, unsigned long& pos, unsigned long len) const;
    // Puts block bi at the head of the list head (inlined into restoreBlock; the name is cedar's _push_block, inferred).
    void pushBlock(int bi, int& head, bool empty) {
        block& b = m_blocks[bi];
        if (empty) {
            head = b.m_prev = b.m_next = bi;
        } else {
            int& tail = m_blocks[head].m_prev;
            b.m_prev = tail;
            b.m_next = head;
            head = tail = m_blocks[tail].m_next = bi;
        }
    }
    // Links label into from's child list (inlined into restoreNinfo; the name is cedar's _push_sibling, inferred).
    void pushSibling(unsigned long from, int base, unsigned char label, bool flag) {
        unsigned char* c = &m_ninfo[from].m_child;
        if (flag && (Flag ? label > *c : !*c)) {
            do {
                c = &m_ninfo[base ^ *c].m_sibling;
            } while (Flag && *c && *c < label);
        }
        m_ninfo[base ^ label].m_sibling = *c;
        *c = label;
    }
    // The value stored for key, EmptyKey when there is none (inlined into DevFileArchiver::getFileInfo; the name
    // and the overloads are cedar's exactMatchSearch, inferred, not the original's).
    Key exactMatchSearch(const char* key) const {
        return exactMatchSearch(key, strlen(key));
    }
    Key exactMatchSearch(const char* key, unsigned long len, unsigned long from = 0) const {
        unsigned long pos = 0;
        Key result = findImpl(key, from, pos, len);
        if (result == DeletedKey) {
            result = EmptyKey;
        }
        return result;
    }

    // The names of these fields are not the original's (no symbol names them); what they hold is read from
    // loadFromMemory (0x71006BCBDC), clear, restoreBlock and restoreNinfo.
    node* m_table;              // 0x0: loadFromMemory's third argument; clear frees it only when the dictionary owns it
    char* m_data;               // 0x8: loadFromMemory's first argument (the tail: its first word is its length)
    int* m_work;                // 0x10: 4 bytes loadFromMemory allocates with m_allocator's handle
    ninfo* m_ninfo;             // 0x18: restoreNinfo builds it (loadFromMemory calls it while it is null)
    block* m_blocks;            // 0x20: restoreBlock builds it (loadFromMemory calls it while it is null)
    int m_bheadF;               // 0x28: first full block (restoreBlock)
    int m_bheadC;               // 0x2C: first closed block (one empty node)
    int m_bheadO;               // 0x30: first open block
    int m_capacity;             // 0x34: loadFromMemory copies m_tableSize here
    int m_tableSize;            // 0x38: loadFromMemory's fourth argument (the node count)
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
    if (m_ninfo != nullptr) {
        mtl::MemManager::deallocate(m_ninfo, 0, false);
        m_ninfo = nullptr;
    }
    if (m_blocks != nullptr) {
        mtl::MemManager::deallocate(m_blocks, 0, false);
        m_blocks = nullptr;
    }
    m_bheadF = 0;
    m_bheadC = 0;
    m_bheadO = 0;
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
    m_table = static_cast<node*>(table);
    m_data = static_cast<char*>(data);
    m_work = static_cast<int*>(mtl::MemManager::allocate(m_allocator->m_handle, 4, 8, false, "no name", 0));
    m_tableSize = tableSize;
    m_external = true;
    *m_work = 0;
    if (m_ninfo != nullptr && m_blocks != nullptr) {
        return;
    }
    if (m_blocks == nullptr) {
        restoreBlock();
    }
    if (m_ninfo == nullptr) {
        restoreNinfo();
    }
    m_capacity = m_tableSize;
    m_entryNum = *reinterpret_cast<int*>(m_data);
    m_state = 1;
}
template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
void DevFileDictionary<Key, Allocator, EmptyKey, DeletedKey, Flag>::restoreBlock() {
    reallocArray(m_blocks, m_tableSize >> 8, 0);
    m_bheadF = m_bheadC = m_bheadO = 0;
    for (int bi = 0, e = 0; e < m_tableSize; ++bi) {
        block& b = m_blocks[bi];
        b.m_num = 0;
        for (; e < (bi << 8) + 256; ++e) {
            if (m_table[e].m_check < 0 && ++b.m_num == 1) {
                b.m_ehead = e;
            }
        }
        int& head = b.m_num == 1 ? m_bheadC : (b.m_num == 0 ? m_bheadF : m_bheadO);
        pushBlock(bi, head, !head && b.m_num);
    }
}

template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
void DevFileDictionary<Key, Allocator, EmptyKey, DeletedKey, Flag>::restoreNinfo() {
    reallocArray(m_ninfo, m_tableSize, 0);
    for (int to = 0; to < m_tableSize; ++to) {
        const int from = m_table[to].m_check;
        if (from < 0) {
            continue;
        }
        const int base = m_table[from].m_base;
        if (const unsigned char label = static_cast<unsigned char>(base ^ to)) {
            pushSibling(from, base, label,
                        !from || m_ninfo[from].m_child || m_table[base ^ m_ninfo[from].m_child].m_check == from);
        }
    }
}

template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
template <typename T>
void DevFileDictionary<Key, Allocator, EmptyKey, DeletedKey, Flag>::reallocArray(T*& p, int sizeN, int sizeP) {
    T* old = p;
    const unsigned long size = sizeof(T) * sizeN;
    if (old == nullptr) {
        p = static_cast<T*>(mtl::MemManager::allocate(m_allocator->m_handle, size, 4, false, "no name", 0));
    } else {
        p = static_cast<T*>(mtl::MemManager::reallocate(old, size, false));
    }
    static const T T0 = T();
    T* q = p + sizeP;
    T* const r = p + sizeN;
    while (q != r) {
        *q++ = T0;
    }
}

template <typename Key, typename Allocator, Key EmptyKey, Key DeletedKey, bool Flag>
Key DevFileDictionary<Key, Allocator, EmptyKey, DeletedKey, Flag>::findImpl(const char* key, unsigned long& from,
                                                                            unsigned long& pos, unsigned long len) const {
    unsigned long offset = from >> 32;
    if (!offset) {
        const unsigned char* const ukey = reinterpret_cast<const unsigned char*>(key);
        while (m_table[from].m_base >= 0) {
            if (pos == len) {
                const node& n = m_table[m_table[from].m_base ^ 0];
                if (n.m_check != static_cast<int>(from)) {
                    return EmptyKey;
                }
                return n.m_base;
            }
            unsigned long to = static_cast<unsigned long>(m_table[from].m_base);
            to ^= ukey[pos];
            if (m_table[to].m_check != static_cast<int>(from)) {
                return DeletedKey;
            }
            ++pos;
            from = to;
        }
        offset = static_cast<unsigned long>(-m_table[from].m_base);
    }
    const unsigned long posOrig = pos;
    const char* const tail = &m_data[offset] - pos;
    if (pos < len) {
        do {
            if (key[pos] != tail[pos]) {
                break;
            }
        } while (++pos < len);
        if (const unsigned long moved = pos - posOrig) {
            from &= 0xFFFFFFFFul;
            from |= (offset + moved) << 32;
        }
        if (pos < len) {
            return DeletedKey;
        }
    }
    if (tail[pos]) {
        return EmptyKey;
    }
    return *reinterpret_cast<const Key*>(&tail[len + 1]);
}
}  // namespace ml

#endif
