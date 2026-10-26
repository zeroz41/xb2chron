#ifndef GRLIB_CGLIBVTXINDEX_H
#define GRLIB_CGLIBVTXINDEX_H

#include "grlib/GrlTypes.h"
#include "grlib/CGLibMemHandle.h"

namespace grlib {
class CGLibVtlMemPool;

// an index buffer in GPU memory (0x28 bytes). The field names are not the original's.
class CGLibVtxIndex {
public:
    CGLibVtxIndex();
    ~CGLibVtxIndex();
    void release();
    // count indices of the format in memory of its own, drawn as the primitive type
    void createIndexBuff(unsigned int count, GrlPrimitiveType type, GrlIndexFormat format);
    // count indices at offset of the pool, drawn as the primitive type (LayerVertexObj::setupVertex)
    void createMemIndexBuff(CGLibVtlMemPool* pool, unsigned int offset, unsigned int count, GrlPrimitiveType type,
                            GrlIndexFormat format);
    // a copy of count indices of the format, drawn as the primitive type
    void createCopyIndexBuff(const void* indices, unsigned int count, GrlPrimitiveType type, GrlIndexFormat format);
    // the buffer moves to offset of the pool
    void resetIndexBuff(CGLibVtlMemPool* pool, unsigned int offset);
    void drawIndex();
    // count indices from offset bytes into the buffer
    void drawIndex(unsigned int count, unsigned int offset);
    void drawInsIndex(int instances);
    void drawInsIndex(int instances, unsigned int count, unsigned int offset);
    // the buffer's memory and size, to write the indices (unlock flushes them)
    void lock(void** buffer, unsigned int* size);
    void unlock();

    // the indices' size in bytes (inline: no symbol; the name is not the original's)
    int getIndexSize() const {
        unsigned int size = m_count;
        if (m_format == 1) {
            size = m_count * 2;
        } else if (m_format == 2) {
            size = m_count * 4;
        }
        return size;
    }

    unsigned int m_count;  // 0x0
    GrlIndexFormat m_format;  // 0x4: 0 8-bit, 1 16-bit, 2 32-bit indices
    GrlPrimitiveType m_type;  // 0x8
    unsigned char pad_C[0x4];
    CGLibMemType m_mem;  // 0x10
    unsigned long m_gpuAddress;  // 0x20
};

}  // namespace grlib

#endif
