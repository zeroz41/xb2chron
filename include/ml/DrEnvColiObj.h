#ifndef ML_DRENVCOLIOBJ_H
#define ML_DRENVCOLIOBJ_H
#include "mm/Vec3.h"
namespace ml {
class DrMan;

// what an environment collision test hit (DrEnvColiMan keeps one; testTreeColi fills it from the hit list entry).
// 0x28 bytes. The field names are not the original's.
class DrEnvColiResult {
public:
    DrEnvColiResult() { clear(); }
    // DrEnvColiMan::testEnvColi resets its own so before a test
    void clear() {
        m_priority = -1;
        m_flags = 0;
        m_subPriority = -1;
        m_option = -1;
        m_param0 = 0;
        m_param1 = 0;
        m_param2 = 0;
        m_param3 = 0;
        m_group = 0;
        m_windId = 0;
    }
    int m_priority;     // 0x0, the entry's s16 at 0x8: a hit replaces one of a lower priority
    int m_subPriority;  // 0x4, the entry's s16 at 0xA
    int m_option;       // 0x8, the entry's s16 at 0xE (when its flag bit 1 is set)
    int m_param0;       // 0xC, the entry's byte at 0x10
    int m_param1;       // 0x10, the entry's byte at 0x11
    int m_param2;       // 0x14, the entry's byte at 0x12
    int m_param3;       // 0x18, the entry's u16 at 0x14
    int m_group;        // 0x1C, the entry's u16 at 0x16
    int m_windId;       // 0x20, ScnRenderDrEnvColi::getWindId
    unsigned int m_flags;  // 0x24, the hit entries' flags or-ed; bit 2: room (ScnRenderDrEnvColi::isRoom)
};

// the start of an environment collision resource as setDataAdd reads it (the names are not the original's)
struct EnvColiDataHeader {
    unsigned char pad_0[0x4];
    int pad_4;                  // 0x4, DrEnvColiMan::update hands it to DrEnvColiParameter
    int m_listNum;              // 0x8
    unsigned int m_listOfs;     // 0xC, to m_listNum 0x20-byte entries
    unsigned char pad_10[0x4];
    unsigned int m_treeOfs;     // 0x14, to the collision tree's nodes
    unsigned int m_postOfs;     // 0x18, to the post-effect block (EnvColiPostHeader)
};

// a list entry of the resource (0x20 bytes, at the header's m_listOfs); testTreeColi tests it and copies it into
// the result. The names are not the original's.
struct EnvColiListData {
    unsigned int m_dataOfs;       // 0x0, from the resource: the shape's data
    unsigned short m_type;        // 0x4, the shape type (DrEnvColiObj::s_pColiTest index)
    unsigned short m_flags;       // 0x6, or-ed into the result; bit 1: m_option is set
    short m_priority;             // 0x8
    short m_subPriority;          // 0xA
    unsigned short m_dispBit;     // 0xC, when not 0 a DrMan::m_dispOffBits bit that hides the entry
    short m_option;               // 0xE
    unsigned char m_param0;       // 0x10
    unsigned char m_param1;       // 0x11
    unsigned char m_param2;       // 0x12
    unsigned char pad_13;
    unsigned short m_param3;      // 0x14
    unsigned short m_group;       // 0x16, the EnvColiPostGroup index
    unsigned char pad_18[0x8];
};

// the post-effect block of the resource (at the header's m_postOfs; the names are not the original's)
struct EnvColiPostHeader {
    unsigned char pad_0[0x4];
    unsigned int m_groupOfs;      // 0x4, from this block: 0x18-byte EnvColiPostGroup entries
    unsigned char pad_8[0x4];
    unsigned int m_dataOfs;       // 0xC, from this block: 0x34-byte EnvColiPostData records
};

// a group of post-effect records, by the list entry's m_group (0x18 bytes; the names are not the original's)
struct EnvColiPostGroup {
    unsigned char pad_0[0x4];
    unsigned int m_first;         // 0x4, the first record
    int m_num;                    // 0x8, the record count
    unsigned char pad_C[0xC];
};

// a post-effect record (0x34 bytes): the one of the current weather that started last before the time of day
// applies (the names are not the original's)
struct EnvColiPostData {
    unsigned char pad_0[0x4];
    unsigned int m_weatherMask;   // 0x4, a bit per weather (DrEnvColiMan::m_weather)
    unsigned int m_flags;         // 0x8
    unsigned short m_weatherNum;  // 0xC, calcParams sets DrPixlPostParm::m_weatherNum to it
    unsigned short pad_E;
    unsigned short m_minute;      // 0x10, the minute of the day it starts at
    unsigned short m_fadeMinute;  // 0x12, calcParams fades from the previous record over these minutes
    unsigned char pad_14[0x12];
    unsigned short m_windId;      // 0x26, testTreeColi's result wind id
    unsigned char pad_28[0xC];
};

// a node of the collision tree in the resource (0x24 bytes; the names are not the original's)
struct EnvColiListTreeData {
    float m_max[3];        // 0x0 (x, y, z)
    float m_min[3];        // 0xC
    unsigned int m_childOfs;  // 0x18, from the resource: u16 indexes of child nodes
    unsigned int m_listOfs;   // 0x1C, from the resource: u16 indexes of list entries
    unsigned short m_childNum;  // 0x20
    unsigned short m_listNum;   // 0x22
};

// what setDataAdd prepares for each list entry, handed to the entry's test as its `work` (0x30 bytes): a rotated
// shape's axes (the columns of its matrix), else its center three times. The names are not the original's.
struct EnvColiWork {
    mm::Vec3 m_axis[3];
};

// a view's environment collision object (DrCreator::createEnvColi makes it; ScnObjEnvColiDr keeps one); a node of
// DrEnvColiMan's lists. 0x40 bytes; the field names are not the original's.
class DrEnvColiObj {
public:
    explicit DrEnvColiObj(DrMan* drMan) : m_prev(nullptr), m_next(nullptr), m_data(nullptr), m_work(nullptr), m_drMan(drMan), m_flags(0) {}
    void setDataAdd(const void* data);
    // marks the object for release (bit s_nDblStockIdx of m_flags)
    void release();
    bool testTreeColi(DrEnvColiResult* result, const EnvColiListTreeData* tree, const mm::Vec3& pos, float range);
    bool envcoli_box(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work);
    bool envcoli_sphere(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work);
    bool envcoli_cylinder(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work);
    bool envcoli_notrot_box(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work);
    bool envcoli_notrot_cylinder(const unsigned char* data, const mm::Vec3& pos, float range, const mm::Vec3* work);

    // the test of each shape type, by the list entry's u16 at 0x4 (testTreeColi calls through it)
    static bool (DrEnvColiObj::*s_pColiTest[5])(const unsigned char*, const mm::Vec3&, float, const mm::Vec3*);

    DrEnvColiObj* m_prev;   // 0x0
    DrEnvColiObj* m_next;   // 0x8
    const unsigned char* m_data;  // 0x10, the resource setDataAdd was given
    const unsigned char* m_list;  // 0x18, m_data + its u32 at 0xC: 0x20-byte entries
    const EnvColiListTreeData* m_tree;  // 0x20, m_data + its u32 at 0x14
    EnvColiWork* m_work;    // 0x28, one per list entry (setDataAdd allocates them)
    DrMan* m_drMan;         // 0x30
    unsigned int m_flags;   // 0x38, bits 0-1: released (by s_nDblStockIdx), bit 2: skipped by the tests
};
}  // namespace ml
#endif
