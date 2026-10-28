#ifndef ML_DRRESETCPAMOBJ_H
#define ML_DRRESETCPAMOBJ_H

namespace ml {
// Only release is declared so far.
class DrResEtcPamObj {
public:
    // the model data's header: its etc-params resource sits m_etcPamOfs bytes from it (names are not the original's)
    struct MdoHeader {
        unsigned char pad_0[0x84];
        unsigned int m_etcPamOfs;  // 0x84
    };
    struct MdoEtcPams {
        unsigned char pad_0[0x4];
        unsigned int m_num;  // 0x4: 0x18 work bytes each after the 0x20-byte object
    };
    static unsigned int calcWorkSize(const unsigned char* mdo);
    static void release(DrResEtcPamObj*& obj);
};
}  // namespace ml

#endif
