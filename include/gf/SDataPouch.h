#ifndef GF_SDATAPOUCH_H
#define GF_SDATAPOUCH_H

namespace gf {

// a driver's pouch slot (8 bytes: 1.0.0's GfDataDriver::setPouchData copies 4, 2 and 1 of them)
struct SDataPouch {
    float remainTime;  // GfMenuPouchAdapter::update_PouchRemainTime shows it; the name is not the original's
    // 0 for an empty slot: update_PouchRemainTime shows no time then; the name is not the original's
    unsigned short itemId;
    bool m_open;  // the slot can hold an item: GfMenuObjPouch2::updateSlotList lists open slots only (the name is not the original's)
    unsigned char pad_07[1];
};

}  // namespace gf

#endif
