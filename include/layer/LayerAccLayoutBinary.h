#ifndef LAYER_LAYERACCLAYOUTBINARY_H
#define LAYER_LAYERACCLAYOUTBINARY_H

namespace layer { class LayerObj; }
namespace layer { class LyrLayoutPosData; }

namespace layer {
// the start of a layout binary, as LayerAccLayoutBinary's constructor reads it (the names are not the original's)
struct LyrLayoutBinHeader {
    unsigned char pad_0[0x10];
    unsigned int m_tblOfs;  // 0x10: a LyrLayoutBinTbl's offset from the start, or 0
    // 0x14: the offset of the data LayerObjTopLayout::workLayoutCreate keeps (its meaning is not known)
    unsigned int m_dataOfs;
    unsigned char pad_18[0x4];
    unsigned int m_posDataOfs;  // 0x1C: the LyrLayoutPosData records' offset from the start
    unsigned int m_posNum;  // 0x20
};
// the table the header's m_tblOfs names (the names are not the original's)
struct LyrLayoutBinTbl {
    unsigned int m_ofs;  // its data's offset from the binary's start
    unsigned int m_num;
};
// a record of the table's data: LayerObjTopLayout::workLayoutCreate creates an object from the resource at
// m_resOfs from the binary's start (the names are not the original's)
struct LyrLayoutBinObj {
    unsigned char pad_0[0x4];
    unsigned int m_resOfs;
    unsigned char pad_8[0x4];
};
// access to a layout binary's named positions (UILayoutData reads its layout through one)
class LayerAccLayoutBinary {
public:
    LayerAccLayoutBinary(const void* binary);
    int getPosIdx(const char* name) const;  // -1 when the binary has no position of that name
    void setLayoutPosData(float& x, float& y, float& width, float& height, unsigned int index);
    void setLayoutPosData(float& x, float& y, float& width, float& height, const char* name);
    void setLayoutObj(LayerObj* obj, const char* name, bool apply);

    // The names after m_binary are not the original's.
    const void* m_binary;          // the constructor's
    int m_posNum;  // 0x8: the header's m_posNum
    const LyrLayoutPosData* m_posData;  // 0x10: the named positions (getPosIdx compares their names)
    unsigned int m_tblNum;  // 0x18: the header's table's m_num, or 0
    const void* m_tbl;  // 0x20: the header's table's data, or null
};
}  // namespace layer

#endif
