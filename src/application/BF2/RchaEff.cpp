#include "rcha/RchaAnm.h"
#include "classes/RchaCam.h"
#include "classes/RchaCamEff.h"
#include "classes/RchaChrEff.h"
#include "classes/RchaEff.h"
#include "classes/CRchaEx.h"
#include "mm/Col4.h"
#include "mm/Vec3.h"

// what each setup does with its table of names (the name is not the original's): every anm of `node` whose id is the
// RchaNode::hashStr of one of the `count` names gets that name and its index goes in index[name], and `found` is set.
// The table is passed in: read in place, clang would make the never-written table constant (.data.rel.ro), where the
// original's stays in .data and is read again after each hashStr call.
static void findAnms(RchaNode& node, const char** names, int count, int* index, bool& found) {
    for (int i = 0; i < node.m_anmCount; i++) {
        for (int j = 0; j < count; j++) {
            if (node.m_anm[i].m_id == node.hashStr(names[j])) {
                node.m_anm[i].m_name = names[j];
                index[j] = i;
                found = true;
            }
        }
    }
}

// the anm names setup looks for, by RchaNode::hashStr of each; an anm found gets the name and its index goes in
// m_anmIndex (proposed name, not the original's: the symbols leave this table unnamed, lbl_7100B71DC8)
static const char* s_effAnmNames[RchaEff::ANM_NUM] = {
    "eff/translate_x",
    "eff/translate_y",
    "eff/translate_z",
    "eff/rotate_x",
    "eff/rotate_y",
    "eff/rotate_z",
    "eff/scale_x",
    "eff/scale_y",
    "eff/scale_z",
    "effAtr/translate_x",
    "effAtr/translate_y",
    "effAtr/translate_z",
    "effAtr/rotate_x",
    "effAtr/rotate_y",
    "effAtr/rotate_z",
    "effAtr/scale_x",
    "effAtr/scale_y",
    "effAtr/scale_z",
    "effAtr/end",
    "effAtr/kill",
};

RchaEff::RchaEff() : m_hasAnm(false) {
    // a loop: the original calls memset where clang would make a tail call of a memset of its own
    for (int i = 0; i < ANM_NUM; i++) {
        m_anmIndex[i] = -1;
    }
}

void RchaEff::clear() {
    RchaNode::clear();
}

bool RchaEff::getPos(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_TRANSLATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_TRANSLATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_TRANSLATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::getRot(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_ROTATE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ROTATE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ROTATE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::getScl(mm::Vec3& vec, float frame) const {
    int index = m_anmIndex[ANM_SCALE_X];
    vec.x = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_SCALE_Y];
    vec.y = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_SCALE_Z];
    vec.z = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::getProgress(int& current, int& total, float frame) const {
    int index = m_anmIndex[ANM_ATR_SCALE_X];
    current = index < 0 ? 0 : static_cast<int>(m_anm[index].getValue(frame));
    index = m_anmIndex[ANM_ATR_SCALE_Y];
    total = index < 0 ? 0 : static_cast<int>(m_anm[index].getValue(frame));
    return true;
}

bool RchaEff::getCol(mm::Col4& col, float frame) const {
    int index = m_anmIndex[ANM_ATR_ROTATE_X];
    col.r = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ATR_ROTATE_Y];
    col.g = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ATR_ROTATE_Z];
    col.b = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    index = m_anmIndex[ANM_ATR_TRANSLATE_Z];
    col.a = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::isGenelate(float frame) const {
    int index = m_anmIndex[ANM_ATR_TRANSLATE_Y];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.8f;
}

bool RchaEff::isEnd(float frame) const {
    int index = m_anmIndex[ANM_ATR_END];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.8f;
}

bool RchaEff::isKill(float frame) const {
    int index = m_anmIndex[ANM_ATR_KILL];
    if (index < 0) {
        return false;
    }
    return m_anm[index].getValue(frame) > 0.8f;
}

bool RchaEff::getSpeed(float& value, float frame) const {
    int index = m_anmIndex[ANM_ATR_TRANSLATE_X];
    value = index < 0 ? 0.0f : m_anm[index].getValue(frame);
    return true;
}

bool RchaEff::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    m_hasAnm = false;
    RchaNode::setup(handle, data);
    findAnms(*this, s_effAnmNames, ANM_NUM, m_anmIndex, m_hasAnm);
    return m_hasAnm;
}
