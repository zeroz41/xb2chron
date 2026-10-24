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
    // the row's <prefix>gimmickType and gimmickID, kept when both are nonzero (the constructor reads those columns;
    // the names are not the original's)
    unsigned char m_gimmickType;
    unsigned char pad_1;
    unsigned short m_gimmickId;
};
}  // namespace gmk

#endif
