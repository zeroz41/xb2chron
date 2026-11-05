#ifndef ML_DRRESMDOINSTMDLINFO_H
#define ML_DRRESMDOINSTMDLINFO_H

namespace ml { class DrMdlBase; }
namespace mm { class Vec3; }

namespace ml {
// DrResMdoInstMdlInfo::update's argument (0x58 bytes: DrMdoCtlPos::dispOffUpdate/beginRenderListPos build it on
// the stack). The field names are not the original's.
struct DrResMdlInstMdlArg {
    const mm::Vec3* m_viewPos;  // 0x0: the view work's position
    void* pad_8;                // 0x8: null from DrMdoCtlPos
    bool m_disp;                // 0x10: false from dispOffUpdate, true from beginRenderListPos
    int m_viewNum;              // 0x14: the model's DrMdlBase::m_viewNum
    float m_speed;              // 0x18: the model's DrMdoMat::m_speed
    bool m_gpuCheckAllVisible;  // 0x1C: the view work's flag
    unsigned char pad_1D[0x3B];
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

    struct Data {
        unsigned char pad_0[0x8];
        unsigned int m_num;  // 0x8: setup's entries, 0x10 work bytes each
    };

    // one per instance model (0x10 bytes; the names are not the original's)
    struct Entry {
        DrMdlBase* m_mdl;  // 0x0: releaseCall/release call its setDeleteCall
        unsigned char pad_8[0x8];
    };

    int m_num;                 // 0x0
    unsigned char pad_4[0x4];
    Entry* m_list;             // 0x8: m_num entries
    char m_name[0x100];        // 0x10
    int pad_110;               // 0x110: create clears it
    unsigned char pad_114[0xC];
    // 0x120: create clears it; releaseCall sets bit 1 << (DrMan::s_nDblStockIdx + 1) (the name is not the original's)
    unsigned int m_deleteFlags;
    unsigned char pad_124[0x4];
};
}  // namespace ml

#endif
