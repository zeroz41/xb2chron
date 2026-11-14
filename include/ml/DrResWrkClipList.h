#ifndef ML_DRRESWRKCLIPLIST_H
#define ML_DRRESWRKCLIPLIST_H

namespace ml {
class DrCalcClipMan;

// A clip list's work: one bit per entry of the list the data holds at a given offset. Field and struct names are not
// the original's.
class DrResWrkClipList {
public:
    // the list header at the given offset of the data
    struct ListHead {
        unsigned int m_ofs;  // 0x0: the entries, from the data
        int m_num;           // 0x4
    };
    // one 8-byte clip entry of a list (update): the entries are walked while their level is not below the last
    // clipped one's; a clipped entry of type 0 makes the list visible, an unclipped entry of type 1 too
    struct ClipEntry {
        unsigned short m_bitNo;  // 0x0: DrCalcClipMan::m_pBitTbl's bit
        unsigned short m_type;   // 0x2
        unsigned short m_level;  // 0x4
        unsigned short pad_6;
    };
    // the bits' bytes, rounded up to 0x20
    static int calcWorkSize(const unsigned char* data, unsigned int ofs);
    int setupWork(unsigned char* work, const unsigned char* data, unsigned int ofs);
    void changeMemCall(const unsigned char* data, unsigned int ofs);
    void update(DrCalcClipMan* clipMan);

    const unsigned char* m_data;  // 0x00
    const unsigned char* m_list;  // 0x08: the entries
    int m_num;                    // 0x10
    int m_workSize;               // 0x14
    unsigned int* m_work;         // 0x18: the bits, one per entry in 32-bit words (update, DrEnvironmentObjLgt::callback_Chk_Point)
};
}  // namespace ml

#endif
