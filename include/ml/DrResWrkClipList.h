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
    // the bits' bytes, rounded up to 0x20
    static int calcWorkSize(const unsigned char* data, unsigned int ofs);
    int setupWork(unsigned char* work, const unsigned char* data, unsigned int ofs);
    void changeMemCall(const unsigned char* data, unsigned int ofs);
    void update(DrCalcClipMan* clipMan);

    const unsigned char* m_data;  // 0x00
    const unsigned char* m_list;  // 0x08: the entries
    int m_num;                    // 0x10
    int m_workSize;               // 0x14
    unsigned char* m_work;        // 0x18: the bits
};
}  // namespace ml

#endif
