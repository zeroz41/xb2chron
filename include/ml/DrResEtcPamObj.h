#ifndef ML_DRRESETCPAMOBJ_H
#define ML_DRRESETCPAMOBJ_H

namespace ml {
class DrResMdoMeshObj;
class DrResEtcParams;
class MdoWrkVanishEffect;
// one etc-param callback entry of the model data, 0x14 bytes (field names are not the original's)
struct MdsEtcParamsCallBack {
    unsigned short m_type;     // 0x0: callback's index in DrResEtcPamObj::s_pMdoNodeEtcParm
    unsigned short m_paramNo;  // 0x2
    unsigned int m_meshNo;     // 0x4: the mesh parts the callback drives
    unsigned char pad_8[0xC];
};
// Only release is declared so far.
class DrResEtcPamObj {
public:
    // what callback hands each node callback (field names are not the original's)
    struct wrkCallbackArg {
        DrResMdoMeshObj* m_mesh;           // 0x0
        MdoWrkVanishEffect* m_vanishEffect;  // 0x8
    };
    void mdonode_etcpam_etcmesh_disp(const MdsEtcParamsCallBack* cb, DrResEtcParams* params, wrkCallbackArg& arg);
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
