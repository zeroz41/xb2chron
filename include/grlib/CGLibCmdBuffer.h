#ifndef GRLIB_CGLIBCMDBUFFER_H
#define GRLIB_CGLIBCMDBUFFER_H

#include "grlib/CGLibMemPool.h"
#include "nvn/nvn.h"

namespace grlib {
// a command buffer (0xF0 bytes: CGLibSystemContext builds five in a row from 0x88) recording into a part of a
// memory pool: control memory at the part's start, command memory after it. The constructor and destructor are
// out of line (ScnRenderDrSysParmAcc's unit). The field names are not the original's.
class CGLibCmdBuffer {
public:
    CGLibCmdBuffer();
    ~CGLibCmdBuffer();
    void release();
    // the part at offset (size bytes, the first ctrlSize of them control memory) of the pool
    void setup(unsigned int offset, unsigned int size, CGLibMemPool& pool, unsigned int ctrlSize);
    void begin();
    void end();
    // calls the recorded commands into the context's command buffer
    void call();

    NVNcommandBuffer m_cmdBuf;   // 0x00
    CGLibMemPool m_memPool;      // 0xA0: released with the buffer (nothing in this unit sets it up)
    NVNcommandHandle m_handle;   // 0xC0: end's
    unsigned int m_offset;       // 0xC8
    unsigned int m_cmdSize;      // 0xCC
    unsigned int m_ctrlSize;     // 0xD0
    CGLibMemPool* m_pPool;       // 0xD8
    unsigned int m_cmdUsed;      // 0xE0: end's
    unsigned int m_ctrlUsed;     // 0xE4: end's
    bool m_init;                 // 0xE8: setup sets it
};
}  // namespace grlib

#endif
