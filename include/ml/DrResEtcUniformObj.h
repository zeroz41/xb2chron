#ifndef ML_DRRESETCUNIFORMOBJ_H
#define ML_DRRESETCUNIFORMOBJ_H

#include "grlib/CGLibDblUniformBlock.h"
#include "mm/Mat44.h"

namespace ml {
class DrMan;

// A double-buffered uniform block carved into sub-buffers per frame: createUniformBuff() hands out the next
// 0x100-aligned piece of the block and records its offset and size in m_entry, setUniformBlock/setStorageBuffer
// bind a recorded piece, begin() resets the pieces and end() uploads the bytes used. The tables come from one
// allocation from DrMan::m_allocHandle: m_entryMax entries, then m_matMax 0x40-byte matrices.
// Field names are not the original's.
class DrResEtcUniformObj {
public:
    struct Entry {
        unsigned int ofs;   // 0x0
        unsigned int size;  // 0x4
    };

    DrResEtcUniformObj(DrMan* man, int entryMax, int size, int matMax);
    ~DrResEtcUniformObj();
    void begin();
    void end();
    void setUniformBlock(short idx, unsigned int location);
    void setStorageBuffer(short idx, unsigned int location, unsigned int ofs);
    unsigned char* createUniformBuff(int size);

    int m_size;                            // 0x00: the block's size
    int m_entryMax;                        // 0x04
    int m_entryCnt;                        // 0x08
    int m_used;                            // 0x0C: bytes of the block handed out
    int m_matMax;                          // 0x10
    mm::Mat44* m_matTbl;                   // 0x18: follows the entries in m_buf
    void* m_buf;                           // 0x20: the allocation (freed by the destructor)
    Entry* m_entry;                        // 0x28
    grlib::CGLibDblUniformBlock m_block;   // 0x30
};
}  // namespace ml

#endif
