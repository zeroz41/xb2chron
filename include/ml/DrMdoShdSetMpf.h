#ifndef ML_DRMDOSHDSETMPF_H
#define ML_DRMDOSHDSETMPF_H

namespace ml {
class DrMdoMat;
struct MdoWrkMatRes;
class DrResShdMpf;
class DrShdDataList;
struct MdsMpfMatInfoHeader;
class DrResMpfSampler;

// The mpf shader setters (mpfshd_*). A class with members: every mpfshd_ reads its first argument register as
// this and passes the DrResShdMpf* second. Only what is written so far is declared; field names are not the
// original's.
class DrMdoShdSetMpf {
public:
    void mpfshd_stm_bill(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader*, const DrResMpfSampler*, bool);
    void mpfshd_drw_bill(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                         const DrResMpfSampler* sampler, bool);
    void mpfshd_drw_mdl(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                        const DrResMpfSampler* sampler, bool);
    void mpfshd_drw_mdl_nonom(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                              const DrResMpfSampler* sampler, bool);
    void mpfshd_drw_mdl_def(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                            const DrResMpfSampler* sampler, bool);
    void mpfshd_drw_mdl_defnonom(DrResShdMpf* shd, DrShdDataList*, const MdsMpfMatInfoHeader* info,
                                 const DrResMpfSampler* sampler, bool);
    void mpfshd_cull_fade_mdl(DrResShdMpf*, DrShdDataList*, const MdsMpfMatInfoHeader*, const DrResMpfSampler*, bool);

    DrMdoMat* m_pMdo;            // 0x0: its m_pDrMan gives the view's blocks and the texture cache
    MdoWrkMatRes* m_pWrkMatRes;  // 0x8
};
}  // namespace ml

#endif
