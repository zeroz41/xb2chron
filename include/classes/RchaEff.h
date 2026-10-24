#ifndef CLASSES_RCHAEFF_H
#define CLASSES_RCHAEFF_H

#include "classes/RchaNode.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"

// table 0x7100B71D98
// An Rcha node whose setup looks for the anms its getters read by name (the names in the table setup reads); each getter
// returns its anm's value at a frame, or a default when the data has none. The enum and field names are not the
// original's: the enum follows those anm names.
class RchaEff : public ::RchaNode {
public:
    enum {
        ANM_TRANSLATE_X,  // "eff/translate_x"
        ANM_TRANSLATE_Y,  // "eff/translate_y"
        ANM_TRANSLATE_Z,  // "eff/translate_z"
        ANM_ROTATE_X,  // "eff/rotate_x"
        ANM_ROTATE_Y,  // "eff/rotate_y"
        ANM_ROTATE_Z,  // "eff/rotate_z"
        ANM_SCALE_X,  // "eff/scale_x"
        ANM_SCALE_Y,  // "eff/scale_y"
        ANM_SCALE_Z,  // "eff/scale_z"
        ANM_ATR_TRANSLATE_X,  // "effAtr/translate_x"
        ANM_ATR_TRANSLATE_Y,  // "effAtr/translate_y"
        ANM_ATR_TRANSLATE_Z,  // "effAtr/translate_z"
        ANM_ATR_ROTATE_X,  // "effAtr/rotate_x"
        ANM_ATR_ROTATE_Y,  // "effAtr/rotate_y"
        ANM_ATR_ROTATE_Z,  // "effAtr/rotate_z"
        ANM_ATR_SCALE_X,  // "effAtr/scale_x"
        ANM_ATR_SCALE_Y,  // "effAtr/scale_y"
        ANM_ATR_SCALE_Z,  // "effAtr/scale_z"
        ANM_ATR_END,  // "effAtr/end"
        ANM_ATR_KILL,  // "effAtr/kill"
        ANM_NUM
    };

    RchaEff();
    // inline: the table's slot 0 holds RchaNode's complete destructor, which this one became
    virtual ~RchaEff() {}  // slot 0
    virtual bool setup(mtl::ALLOC_HANDLE handle, void const* data);  // slot 2
    virtual void clear();  // slot 3
    bool getPos(mm::Vec3& vec, float frame) const;
    bool getRot(mm::Vec3& vec, float frame) const;
    bool getScl(mm::Vec3& vec, float frame) const;
    bool getProgress(int& current, int& total, float frame) const;
    bool getCol(mm::Col4& col, float frame) const;
    bool isGenelate(float frame) const;
    bool isEnd(float frame) const;
    bool isKill(float frame) const;
    bool getSpeed(float& value, float frame) const;

    bool m_hasAnm;  // 0x19A0 set by setup when it finds any of its anms (1.0.0's hasAnm returns it)
    int m_anmIndex[ANM_NUM];  // 0x19A4 per name, the index in m_anm of the anm setup found for it, -1 for none
};

#endif
