#ifndef CLASSES_GMK_BOOTEDGMKCOND_H
#define CLASSES_GMK_BOOTEDGMKCOND_H

class CBdatWrapper;

namespace gmk {
// a gimmick row's condition of 4 bytes (no table); GfFieldMapGimmick::BdatInfo holds one, built from the row's
// "OP_" columns by the (CBdatWrapper, row, prefix) constructor
class BootedGmkCond {
public:
    BootedGmkCond(unsigned char type, unsigned short id);
    BootedGmkCond(const CBdatWrapper& bdat, int row, const char* prefix);
    bool isMatch() const;
    unsigned char pad_0;
    unsigned char pad_1;
    unsigned short pad_2;
};
}  // namespace gmk

#endif
