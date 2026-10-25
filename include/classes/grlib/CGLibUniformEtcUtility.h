#ifndef CLASSES_GRLIB_CGLIBUNIFORMETCUTILITY_H
#define CLASSES_GRLIB_CGLIBUNIFORMETCUTILITY_H

#include "grlib/CGLibUniBaseUtility.h"
#include "grlib/CGLibEtcUniformBlock.h"

namespace grlib {
// table 0x7100B79E30: a uniform-block writer into the system context's global uniform memory (0x38 bytes), through
// the block it holds (its fields are that block's: the constructor and setMoveMem are its inlined). The field name
// is not the original's.
class CGLibUniformEtcUtility : public CGLibUniBaseUtility {
public:
    CGLibUniformEtcUtility(const CGLibDecShader* pDecShader);
    virtual ~CGLibUniformEtcUtility() {}  // slot 0
    virtual unsigned char* getBuff();  // slot 2
    virtual void updateData();  // slot 3
    virtual void setUniformBlock();  // slot 4
    virtual void setStorageBuffer();  // slot 5
    // slot 6: moves the global uniform memory past the block
    virtual void setMoveMem() { m_block.setMoveMem(m_size); }

    CGLibEtcUniformBlock m_block;  // 0x20
};
}  // namespace grlib

#endif
