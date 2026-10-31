#ifndef IDCOLI_IDCOLIUTILTREEACC_H
#define IDCOLI_IDCOLIUTILTREEACC_H

#include "classes/idcoli/IDColiObjBase.h"
#include "idcoli/ColiLinkList.h"
#include "idcoli/IDColiTreeTop.h"

namespace mm { class Vec3; }

namespace idcoli {

// walks the cell lists of an IDColiTreeTop: startTreeAaBbMode (IDColiManager.cpp) sets per level the range of
// cells a box covers, nextList hands out their lists one by one. IDColiGrandObj::coliCallCheck/coliCallResl/
// coliMoveCallResl build one on the stack (0xB0 bytes) over the grand object's current tree. Only what those use is
// declared; the field names, Range and nextList are not the original's.
class IDColiUtilTreeAcc {
public:
    // a level's cell range and the cell nextList hands out next
    struct Range {
        int m_x;  // 0x0
        int m_z;  // 0x4
        int m_xStart;  // 0x8
        int m_zStart;  // 0xC
        int m_xEnd;  // 0x10
        int m_zEnd;  // 0x14
    };

    IDColiUtilTreeAcc(IDColiTreeTop* top) : m_top(top), m_level(0) {}
    void startTreeAaBbMode(const mm::Vec3& max, const mm::Vec3& min);
    // the next cell's list in range (levels 0..4), nullptr when the walk is over (inlined into its callers)
    ColiLinkList<IDColiTreeObj>* nextList() {
        while (m_level < 5) {
            Range& range = m_ranges[m_level];
            while (range.m_z <= range.m_zEnd) {
                if (range.m_x <= range.m_xEnd) {
                    int x = range.m_x++;
                    return m_top->getObjList(x, range.m_z, m_level);
                }
                range.m_x = range.m_xStart;
                range.m_z++;
            }
            range.m_z = range.m_zStart;
            m_level++;
        }
        return nullptr;
    }

    IDColiTreeTop* m_top;  // 0x0
    unsigned char pad_8[0x28];
    int m_level;  // 0x30
    Range m_ranges[5];  // 0x34
};

}  // namespace idcoli

#endif
