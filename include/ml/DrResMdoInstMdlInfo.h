#ifndef ML_DRRESMDOINSTMDLINFO_H
#define ML_DRRESMDOINSTMDLINFO_H

#include "mm/Vec3NA.h"
#include "mm/mtl/FixStr.h"

namespace ml { class DrMdlBase; }
namespace mm { class Vec3; class Mat44; }

namespace ml {
// DrResMdoInstMdlInfo::update's argument (0x58 bytes: DrMdoCtlPos::dispOffUpdate/beginRenderListPos build it on
// the stack). The field names are not the original's.
struct DrResMdlInstMdlArg;

// a group of instance objects in DrResMdoInstMdlInfo's data (0x1C bytes; the names are not the original's)
struct DrResMdoInstMdlGroup {
    unsigned int m_ofs0;  // 0x0: offset in the data
    unsigned int m_ofs4;  // 0x4: offset in the data
    unsigned int m_top;   // 0x8: the group's first object
    int m_num;            // 0xC: the group's objects
    unsigned char pad_10[0xC];
};

// one instance model of a DrResMdoInstMdlInfo (0x10 bytes; DrResMdoInstMdlInfo::setup clears it in its work buffer)
class DrResMdoInstMdlObj {
public:
    void update(DrResMdlInstMdlArg& arg);

    DrMdlBase* m_mdl;  // 0x0: DrResMdoInstMdlInfo::releaseCall/release call its setDeleteCall
    int pad_8;         // 0x8: setup clears it
    unsigned char pad_C[0x4];
};

struct DrResMdlInstMdlArg {
    const mm::Vec3* m_viewPos;  // 0x0: the view work's position
    void* pad_8;                // 0x8: null from DrMdoCtlPos
    bool m_disp;                // 0x10: false from dispOffUpdate, true from beginRenderListPos
    int m_viewNum;              // 0x14: the model's DrMdlBase::m_viewNum
    float m_speed;              // 0x18: the model's DrMdoMat::m_speed
    bool m_gpuCheckAllVisible;  // 0x1C: the view work's flag
    unsigned char pad_1D[0x3];
    // set by DrResMdoInstMdlInfo::update for each of its objects (the names are not the original's)
    const mm::mtl::FixStr<256>* m_name;  // 0x20: the info's name
    const unsigned char* m_data;         // 0x28: the info's data
    const unsigned char* m_groupData4;   // 0x30: the data at the group's second offset
    const unsigned char* m_groupData0;   // 0x38: the data at the group's first offset
    const DrResMdoInstMdlGroup* m_group;  // 0x40: the group being updated
    const mm::Vec3NA* m_pos;             // 0x48: the object's position in the data
    const mm::Mat44* m_mtx;              // 0x50: the object's matrix in the data
};

// An instance model's info, built in a work buffer by create: the object (0x128 bytes) followed by setup's data
// (0x10 bytes per entry of the data's count at +0x8). Only what create/calcWorkSize show; field names are not the
// original's.
class DrResMdoInstMdlInfo {
public:
    // DrMdoCtlPos::setDeleteCall calls it: passes the delete call on to every entry's model
    void releaseCall();
    void update(DrResMdlInstMdlArg& arg);
    // DrMdoCtlPos::releasePos and DrMdoCtlSeam::releaseSeam call it: passes the delete call on to every entry's model,
    // clears the entries and info
    static void release(DrResMdoInstMdlInfo*& info);
    static unsigned int calcWorkSize(const unsigned char* data);
    static unsigned int create(unsigned char* work, DrResMdoInstMdlInfo*& out, const unsigned char* data,
                               const char* name);
    unsigned int setup(unsigned char* work, const unsigned char* data, const char* name);

    // (the names are not the original's)
    struct Data {
        unsigned int m_groupOfs;  // 0x0: offset of the DrResMdoInstMdlGroup table
        int m_groupNum;           // 0x4
        unsigned int m_num;       // 0x8: setup's objects, 0x10 work bytes each
        unsigned int m_mtxOfs;    // 0xC: offset of the objects' matrices (0x40 bytes each)
        unsigned int m_posOfs;    // 0x10: offset of the objects' positions (0xC bytes each)
    };

    int m_num;                 // 0x0
    unsigned char pad_4[0x4];
    DrResMdoInstMdlObj* m_list;  // 0x8: m_num objects
    // 0x10: create clears it; setup stores the name's directory with a '/' (FixStr<256>: asserts `pszName != 0`,
    // `m_nLen < LEN`, `m_nLen + nBackLen < LEN`)
    mm::mtl::FixStr<256> m_name;
    unsigned char pad_114[0x4];
    const unsigned char* m_data;  // 0x118: setup's data
    // 0x120: create clears it; releaseCall sets bit 1 << (DrMan::s_nDblStockIdx + 1) (the name is not the original's)
    unsigned int m_deleteFlags;
    unsigned char pad_124[0x4];
};
}  // namespace ml

#endif
