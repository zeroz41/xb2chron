#ifndef ML_DRRESMDOSEAMWRKPOSINST_H
#define ML_DRRESMDOSEAMWRKPOSINST_H

#include "mtl/MemManager.h"

namespace ml {
class DrResMdoSeamMemObj;
class DrResMdoInstAnmObj;
// The instance positions of a seam map (0x80 bytes: DrResMdoSeamWrkInst::setEtcPosCache sets them up 0x80 apart).
// Only what DrResFetch.cpp's recovered functions use is recovered (the field and nested type names are not the
// original's).
class DrResMdoSeamWrkPosInst {
public:
    // one position record of m_posTbl (0x70 bytes)
    struct PosRecord {
        unsigned char pad_0[0x70];
    };
    // the object an entry is bound to: it points back at its entry
    struct EntryUser {
        unsigned char pad_0[0x28];
        void* m_entry;  // 0x28: cleared when the entry is released
    };
    // one entry of m_entries (0x28 bytes)
    struct Entry {
        EntryUser* m_user;
        const PosRecord* m_pos;  // 0x8: the entry's record of m_posTbl
        unsigned char pad_10[0x18];
    };
    // the table m_sub points at: three offsets from the position data
    struct SubTbl {
        unsigned int m_ofs0;
        unsigned int pad_4;
        unsigned int m_ofs8;
        unsigned int pad_C;
        unsigned int m_ofs10;
    };
    // the head block m_head points at
    struct HeadBlock {
        const unsigned char* m_data;
        const unsigned char* m_body;
    };
    // the position data of the base positions (the seam map's own data)
    struct BaseData {
        unsigned char pad_0[0x18];
        unsigned int m_posOfs;  // 0x18
        unsigned int pad_1C;
        unsigned int m_ofs20;
        unsigned int pad_24;
        int m_ofs28;
        unsigned char pad_2C[0x20];
        unsigned int m_subOfs;  // 0x4C
        unsigned int pad_50;
        unsigned int m_headOfs;  // 0x54
    };
    // the position data of an etc position block (a DrResMdoSeamMemObj's data)
    struct EtcData {
        unsigned int pad_0;
        unsigned int m_posOfs;  // 0x4
        unsigned int pad_8;
        unsigned int m_ofsC;
        unsigned int pad_10;
        int m_ofs14;
        unsigned char pad_18[0x14];
        unsigned int m_subOfs;  // 0x2C
        unsigned int pad_30;
        unsigned int m_headOfs;  // 0x34
    };
    void setupEtcInstPos(int index, DrResMdoSeamMemObj* memObj, mtl::ALLOC_HANDLE handle, const DrResMdoInstAnmObj* anm);
    void update();

    const unsigned char* m_data;      // 0x0
    const PosRecord* m_posTbl;        // 0x8
    const unsigned char* m_tbl10;     // 0x10
    const unsigned char* m_tbl18;     // 0x18
    const SubTbl* m_sub;              // 0x20
    const unsigned char* m_subTbl10;  // 0x28: m_data + m_sub->m_ofs10
    const unsigned char* m_subTbl0;   // 0x30: m_data + m_sub->m_ofs0
    const unsigned char* m_subTbl8;   // 0x38: m_data + m_sub->m_ofs8
    HeadBlock* m_head;                // 0x40
    Entry* m_entries;                 // 0x48: m_entryNum entries
    DrResMdoSeamMemObj* m_memObj;     // 0x50: the etc position block (null for the base positions)
    void** m_shadowCacheBuf;            // 0x58: one buffer per shadow cache
    unsigned int m_shadowCacheBufSize;  // 0x60: bytes of each buffer, 0 when there are none
    unsigned char pad_64[0x8];
    int m_entryNum;                   // 0x6C
    unsigned char pad_70[0x8];
    void* m_buf;                      // 0x78: freed on release
};
}  // namespace ml

#endif
