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
// m_anmIndex (proposed name, not the original's: the symbols leave this table unnamed, lbl_7100B71CA8)
static const char* s_camEffAnmNames[RchaCamEff::ANM_NUM] = {
    "camAtr/ColFilter",
    "camAtr/ColFilterNear",
    "camAtr/ColFilterFar",
    "camAtr/ColFilterFr",
};

RchaCamEff::RchaCamEff() : m_hasAnm(false) {
    // a loop: the original calls memset where clang would make a tail call of a memset of its own
    for (int i = 0; i < ANM_NUM; i++) {
        m_anmIndex[i] = -1;
    }
}

bool RchaCamEff::getColFilter(int& value, float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER];
    if (index < 0) {
        return false;
    }
    value = m_anm[index].getValueInt(frame);
    return true;
}

int RchaCamEff::getNearColFilter(float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER_NEAR];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

int RchaCamEff::getFarColFilter(float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER_FAR];
    if (index < 0) {
        return 0;
    }
    return m_anm[index].getValueInt(frame);
}

float RchaCamEff::getFrColFilter(float frame) const {
    int index = m_anmIndex[ANM_ATR_COL_FILTER_FR];
    if (index < 0) {
        return 0.0f;
    }
    return m_anm[index].getValue(frame);
}

bool RchaCamEff::setup(mtl::ALLOC_HANDLE handle, void const* data) {
    m_hasAnm = false;
    RchaNode::setup(handle, data);
    findAnms(*this, s_camEffAnmNames, ANM_NUM, m_anmIndex, m_hasAnm);
    return m_hasAnm;
}
