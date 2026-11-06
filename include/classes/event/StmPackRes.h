#ifndef CLASSES_EVENT_STMPACKRES_H
#define CLASSES_EVENT_STMPACKRES_H

namespace event {
// one read cut's region of StmPackMemory's buffer (no table, 0x58 bytes): 1.0.0 names the class and its constructor
// (0x71000A3A28), isLoading, loadCompleate and getFileAdr (0x71000A3A60..0x71000A3A7C); 3.0.1 inlines them. The
// field names are not the original's.
class StmPackRes {
public:
    StmPackRes(void* adr, unsigned long size, unsigned long dataOfs, unsigned long first, unsigned long last,
               unsigned long pageStart, unsigned long pageEnd, int prio, int id, unsigned long pack)
        : pad_0(0), pad_4(1), pad_8(2), pad_10(reinterpret_cast<unsigned long>(adr)), pad_18(size), pad_20(dataOfs),
          pad_28(first), pad_30(last), pad_38(pageStart), pad_40(pageEnd), pad_48(prio), pad_4c(id), pad_50(pack) {}
    // a user copy (the original's FixedVector::erase moves the cuts one by one, not in one memcpy)
    StmPackRes(const StmPackRes& other)
        : pad_0(other.pad_0), pad_4(other.pad_4), pad_8(other.pad_8), pad_10(other.pad_10), pad_18(other.pad_18),
          pad_20(other.pad_20), pad_28(other.pad_28), pad_30(other.pad_30), pad_38(other.pad_38), pad_40(other.pad_40),
          pad_48(other.pad_48), pad_4c(other.pad_4c), pad_50(other.pad_50) {}
    StmPackRes& operator=(const StmPackRes&) = default;
    bool isLoading() const { return pad_4 & 1; }
    void loadCompleate() { pad_4 &= ~1u; }
    // where the data at file offset ofs sits in the buffer
    void* getFileAdr(unsigned long ofs) const { return reinterpret_cast<void*>(ofs - pad_20 + pad_10); }

    int pad_0;  // adr counts it up, free down
    unsigned int pad_4;  // bit 0: still reading (loadCompleate clears it); bit 1: set by free
    int pad_8;  // 2 from the constructor; StmPackMemory::update counts it down before dropping the cut
    unsigned char pad_c[4];
    unsigned long pad_10;  // address of the region (free's range start)
    unsigned long pad_18;  // size of the region
    unsigned long pad_20;  // file offset of its first entry's data
    unsigned long pad_28;  // first entry index
    unsigned long pad_30;  // last entry index
    unsigned long pad_38;  // first page of the buffer it uses
    unsigned long pad_40;  // the page after its last
    int pad_48;  // its entries' priority (StmPackHeader::getPrio)
    int pad_4c;  // StmPackMemory's read counter at its read
    unsigned long pad_50;  // pack index adr compares with StmPackMemory's current pack
};
}  // namespace event

#endif
