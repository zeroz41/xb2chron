#ifndef CLASSES_ML_DRRESMDOSEAMMEMOBJ_H
#define CLASSES_ML_DRRESMDOSEAMMEMOBJ_H

namespace ml {
// table 0x7100B7E430
// A block of the seam resource memory DrResMdoSeamMemMan hands out (createFreeObj splits a free block in two and
// links the rest after it). The field names are not the original's.
class DrResMdoSeamMemObj {
public:
    virtual ~DrResMdoSeamMemObj() {}  // slot 0

    DrResMdoSeamMemObj* m_prev;  // 0x08: DrResChankList links
    DrResMdoSeamMemObj* m_next;  // 0x10
    unsigned char* m_pData;      // 0x18: the block's memory
    unsigned int m_size;         // 0x20: the block's bytes
    unsigned int m_flags;        // 0x24: 1 = in use (createFreeObj), 2 = read in (the seam objects' update tests it)
};
}  // namespace ml

#endif
