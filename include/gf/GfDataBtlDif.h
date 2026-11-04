#ifndef GF_GFDATABTLDIF_H
#define GF_GFDATABTLDIF_H

namespace gf { struct SSoundUiOption; enum GFDIFF : int; }

namespace gf {

// the battle difficulty data's helpers (functions on an SSoundUiOption; 2.0.0's symbols name the class)
class GfDataBtlDif {
public:
    // 2.0.0's symbols name it. What it does: when GfBdatBtl is up, stores 4 at the option's 0x23 and value at 0x24 +
    // index - 1, then calls GfDataBtlDif::setCustomFollow on the option; GfMenuObjOption::initOptionData passes each
    // difficulty bdat row's default level - 1.
    static void setOptionGameDifficultCustom(SSoundUiOption& option, unsigned int index, unsigned char value);
    // 2.0.0's symbols name it. What it does: when GfBdatBtl is up, stores (GfBdatBtl::getBTL_DifSettingDiff(11, 0) -
    // getBTL_DifSettingParamMin(11)) / getBTL_DifSettingInterval(11) (0 when that divisor is 0) at the option's 0x2E,
    // and the same for row 12 at 0x2F.
    static void setCustomFollow(SSoundUiOption& option);
    // 2.0.0's symbols name it. What it does: stores 6 at the option's 0x23, then (when GfBdatBtl is up) fills the bytes
    // from 0x24 from GfBdatBtl::getBTL_DifSettingDiff for the type it is handed (type 4: GfDataBtlDif::setCustomFollow
    // instead); SSoundUiOption::clear passes type 0.
    static void setOptionGameDifficult(SSoundUiOption& option, GFDIFF type);
    // 2.0.0's symbols name it. What it does: when GfBdatBtl is up, a value for index from the option's 0x23 (type 4:
    // its byte at 0x24 + index - 1, else from GfBdatBtl::getBTL_DifSettingDiff / getBTL_DifSettingParamMin /
    // getBTL_DifSettingInterval of index), scaled by getBTL_DifSettingParamMin / getBTL_DifSettingParamMax of index; 0
    // without GfBdatBtl. gf::GfGameUtilDiff::getBtlDifParam passes the option data's.
    static unsigned int getBtlDifParam(const SSoundUiOption& option, unsigned int index);
    // 2.0.0's symbols name it. What it does: when GfBdatBtl is up, the option's byte at 0x24 + index - 1 (m_list), else
    // 0.
    static unsigned char getBtlDifStep(const SSoundUiOption& option, unsigned int index);
};

}  // namespace gf

#endif
