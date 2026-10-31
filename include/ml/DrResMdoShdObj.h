#ifndef ML_DRRESMDOSHDOBJ_H
#define ML_DRRESMDOSHDOBJ_H

namespace ml {
// A model's shaders, built in a work buffer (create): one 0x18-byte entry per shader of the model (mdo) data's
// shader resource. Only the fields getDecShdIdx and setDecShdParm use are declared; field and struct names are not
// the original's.
class DrResMdoShdObj {
public:
    // the shader resource: m_num records of 0x14 bytes sit m_dataOfs bytes from it
    struct ShdHeader {
        unsigned int m_num;      // 0x0
        unsigned int m_dataOfs;  // 0x4
    };
    struct ShdData {
        unsigned int m_nameOfs;  // 0x0: the shader's name, from the ShdHeader
        unsigned char pad_4[0x10];
    };
    struct Entry {
        const ShdData* m_data;  // 0x0
        unsigned char* m_work;  // 0x8
        unsigned int m_decShdParm;  // 0x10, set by setDecShdParm
        unsigned char pad_14[0x4];
    };
    // the index of the shader named name, -1 if none
    int getDecShdIdx(const char* name) const;
    void setDecShdParm(unsigned int idx, unsigned int parm);

    const ShdHeader* m_header;  // 0x0
    Entry* m_entries;           // 0x8, m_num of them, after the object in its work buffer
    unsigned int m_num;         // 0x10
    unsigned char pad_14[0x4];
};
}  // namespace ml

#endif
