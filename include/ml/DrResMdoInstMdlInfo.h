#ifndef ML_DRRESMDOINSTMDLINFO_H
#define ML_DRRESMDOINSTMDLINFO_H

namespace ml {
// An instance model's info, built in a work buffer by create: the object (0x128 bytes) followed by setup's data
// (0x10 bytes per entry of the data's count at +0x8). Only what create/calcWorkSize show; field names are not the
// original's.
class DrResMdoInstMdlInfo {
public:
    static unsigned int calcWorkSize(const unsigned char* data);
    static unsigned int create(unsigned char* work, DrResMdoInstMdlInfo*& out, const unsigned char* data,
                               const char* name);
    unsigned int setup(unsigned char* work, const unsigned char* data, const char* name);

    struct Data {
        unsigned char pad_0[0x8];
        unsigned int m_num;  // 0x8: setup's entries, 0x10 work bytes each
    };

    int m_num;                 // 0x0
    unsigned char pad_4[0x4];
    void* m_list;              // 0x8: m_num entries of 0x10 bytes (release calls each one's virtual slot 16)
    char m_name[0x100];        // 0x10
    int pad_110;               // 0x110: create clears it
    unsigned char pad_114[0xC];
    int pad_120;               // 0x120: create clears it
    unsigned char pad_124[0x4];
};
}  // namespace ml

#endif
