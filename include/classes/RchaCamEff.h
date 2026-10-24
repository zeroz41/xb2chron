#ifndef CLASSES_RCHACAMEFF_H
#define CLASSES_RCHACAMEFF_H

#include "classes/RchaNode.h"

// table 0x7100B71C78
// An Rcha node whose setup looks for the anms its getters read by name (the names in the table setup reads); each getter
// returns its anm's value at a frame, or a default when the data has none. The enum and field names are not the
// original's: the enum follows those anm names.
class RchaCamEff : public ::RchaNode {
public:
    enum {
        ANM_ATR_COL_FILTER,  // "camAtr/ColFilter"
        ANM_ATR_COL_FILTER_NEAR,  // "camAtr/ColFilterNear"
        ANM_ATR_COL_FILTER_FAR,  // "camAtr/ColFilterFar"
        ANM_ATR_COL_FILTER_FR,  // "camAtr/ColFilterFr"
        ANM_NUM
    };

    RchaCamEff();
    // inline: the table's slot 0 holds RchaNode's complete destructor, which this one became
    virtual ~RchaCamEff() {}  // slot 0
    virtual bool setup(mtl::ALLOC_HANDLE handle, void const* data);  // slot 2
    bool getColFilter(int& value, float frame) const;
    int getNearColFilter(float frame) const;
    int getFarColFilter(float frame) const;
    float getFrColFilter(float frame) const;

    bool m_hasAnm;  // 0x19A0 set by setup when it finds any of its anms (1.0.0's hasAnm returns it)
    int m_anmIndex[ANM_NUM];  // 0x19A4 per name, the index in m_anm of the anm setup found for it, -1 for none
};

#endif
