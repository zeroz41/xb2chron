#ifndef CLASSES_ML_FIXED_SIZE_ALLOC_H
#define CLASSES_ML_FIXED_SIZE_ALLOC_H

#include <string.h>
#include "mtl/MemManager.h"

namespace ml {
// a template: 2 instances in the module. A fixed-size block pool (the member names are not the original's)
template <typename T0>
class fixed_size_alloc {
public:
    // empty; the count is set by create
    fixed_size_alloc() : m_buffer(nullptr), m_usedBits(nullptr), m_blocks(nullptr), m_bitWords(0), m_used(0) {}
    // releases the pool (DebDraw's destructor inlines it)
    virtual ~fixed_size_alloc() {  // slot 0
        release();
    }

    // frees the block buffer and forgets the pool (inline: the destructor and create inline it)
    void release() {
        if (m_buffer != nullptr) {
            mtl::MemManager::deallocate(m_buffer, 0, false);
            m_buffer = nullptr;
        }
        m_count = 0;
        m_blocks = nullptr;
        m_bitWords = 0;
        m_used = 0;
        m_usedBits = nullptr;
    }

    // a pool of count blocks of T from mem: one zeroed buffer holding the blocks and, after them, one used bit per
    // block in 32-bit words (inline: DebDraw's constructor inlines it)
    void create(mtl::ALLOC_HANDLE mem, int count) {
        release();
        m_count = count;
        m_bitWords = count / 32;
        unsigned long bytes = count * sizeof(T0) + m_bitWords * 4;
        m_buffer = mtl::MemManager::allocate(mem, bytes, 4, false, "no name", 0);
        memset(m_buffer, 0, bytes);
        m_used = 0;
        m_usedBits = reinterpret_cast<unsigned int*>(static_cast<unsigned char*>(m_buffer) + count * sizeof(T0));
        m_blocks = static_cast<T0*>(m_buffer);
    }

    // a free block marked in use, null when every block is (WorkCpu::allocJob inlines it; the name is not the
    // original's)
    T0* allocate() {
        unsigned int* bits = m_usedBits;
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_bitWords); ++i, ++bits) {
            unsigned int word = *bits;
            if (word != 0xFFFFFFFF) {
                unsigned int bit = (word & 0xFFFF) == 0xFFFF ? 16 : 0;
                for (unsigned int mask = 1u << bit; bit < 32; ++bit, mask <<= 1) {
                    if ((mask & word) == 0) {
                        ++m_used;
                        *bits |= mask;
                        return &m_blocks[i * 32 + bit];
                    }
                }
            }
        }
        return nullptr;
    }
    // the block back, unmarked if it was in use (WorkCpu::freeJob inlines it; the name is not the original's)
    void deallocate(T0* block) {
        unsigned int index = block - m_blocks;
        unsigned int mask = 1u << (index & 31);
        if (m_usedBits[index >> 5] & mask) {
            m_usedBits[index >> 5] &= ~mask;
            --m_used;
        }
    }

    void* m_buffer;                // 0x08
    unsigned int* m_usedBits;      // 0x10 one bit per block, after the blocks
    T0* m_blocks;                  // 0x18
    int m_bitWords;                // 0x20 32-bit words of used bits
    int m_used;                    // 0x24
    int m_count;                   // 0x28
};
}  // namespace ml

#endif
