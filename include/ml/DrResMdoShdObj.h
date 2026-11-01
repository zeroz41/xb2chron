#ifndef ML_DRRESMDOSHDOBJ_H
#define ML_DRRESMDOSHDOBJ_H

namespace ml {
// A model's shaders, built in a work buffer (create): one 0x18-byte entry per shader of the model (mdo) data's
// shader resource. Only the fields getDecShdIdx and setDecShdParm use are declared; field and struct names are not
// the original's.
class DrResMdoShdObj {
public:
    // the shader resource: m_num records of 0x14 bytes sit m_dataOfs bytes from it
    // the model (mdo) data's head: the shader resource sits m_shdOfs bytes from it
    struct MdoHeader {
        unsigned char pad_0[0x88];
        unsigned int m_shdOfs;  // 0x88
    };
    struct ShdHeader {
        int m_num;               // 0x0
        unsigned int m_dataOfs;  // 0x4
    };
    struct ShdData {
        unsigned int m_nameOfs;  // 0x0: the shader's name, from the ShdHeader
        unsigned char pad_4[0xC];
        int m_workNum;  // 0x10: bytes of the shader's work (one declaration index per byte)
    };
    struct Entry {
        const ShdData* m_data;  // 0x0
        unsigned char* m_work;  // 0x8
        unsigned int m_decShdParm;  // 0x10, set by setDecShdParm
        unsigned int m_curDecShdParm;  // 0x14: the parm last applied
    };
    // the work size create needs for the model data mdo
    static unsigned int calcWorkSize(const unsigned char* mdo);
    // builds the object in work; returns the bytes it used
    static unsigned int create(unsigned char* work, const unsigned char* mdo);
    // the index of the shader named name, -1 if none
    int getDecShdIdx(const char* name) const;
    void setDecShdParm(unsigned int idx, unsigned int parm);

    DrResMdoShdObj() : m_header(nullptr), m_entries(nullptr), m_num(0) {}

    const ShdHeader* m_header;  // 0x0
    Entry* m_entries;           // 0x8, m_num of them, after the object in its work buffer
    unsigned int m_num;         // 0x10
    unsigned char pad_14[0x4];
};
}  // namespace ml

#endif
