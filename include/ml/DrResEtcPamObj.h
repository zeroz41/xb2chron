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
    void mdonode_etcpam_volfadeanm(const MdsEtcParamsCallBack* cb, DrResEtcParams* params, wrkCallbackArg& arg);
    // the model data's header: its etc-params resource sits m_etcPamOfs bytes from it (names are not the original's)
    struct MdoHeader {
        unsigned char pad_0[0x84];
        unsigned int m_etcPamOfs;  // 0x84
    };
    struct MdoEtcPams {
        unsigned int m_dataOfs;  // 0x0: m_data, from the MdoEtcPams
        unsigned int m_num;      // 0x4: 0x18 work bytes each after the 0x20-byte object
        unsigned int m_cbOfs;    // 0x8: m_cbNum MdsEtcParamsCallBack, from the MdoEtcPams
        int m_cbNum;             // 0xC
        unsigned int m_initOfs;  // 0x10: m_num initial float values, from the MdoEtcPams (0: none)
        unsigned int m_flags;    // 0x14: bit 0: a callback's parameter is its m_paramNo, else its own index
    };
    typedef void (DrResEtcPamObj::*NodeFunc)(const MdsEtcParamsCallBack* cb, DrResEtcParams* params,
                                             wrkCallbackArg& arg);
    static NodeFunc s_pMdoNodeEtcParm[2];
    void callback(DrResMdoMeshObj* mesh, MdoWrkVanishEffect* vanishEffect);
    void update();
    static unsigned int calcWorkSize(const unsigned char* mdo);
    static void release(DrResEtcPamObj*& obj);

    // Names below are not the original's.
    const MdoEtcPams* m_pams;   // 0x0
    const void* m_data;         // 0x8
    DrResEtcParams* m_params;   // 0x10: MdoEtcPams::m_num entries (the name is not the original's)
    unsigned int m_paramNum;    // 0x18 (the name is not the original's)
    unsigned int m_flags;       // 0x1C: bit 0 (set by create) lets mdonode_etcpam_volfadeanm work
};
}  // namespace ml

#endif
