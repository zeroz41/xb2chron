#include "classes/gf/GfMenuDiffAdapter.h"

namespace gf {

GfMenuDiffAdapter::~GfMenuDiffAdapter() {
    ;  // the original body has a statement the build compiles away; an empty one would drop the table store
}

// create: its code is the original's with two callee-saved registers swapped, so it waits (with its type table)

bool GfMenuDiffAdapter::update_Icon(int result) {
    switch (result) {
    case 0:
        return false;
    case 1:
        setNumber(0);
        break;
    case 2:
        setNumber(1);
        break;
    }
    return true;
}

bool GfMenuDiffAdapter::update_MulCol(int result) {
    switch (result) {
    case 0:
        setMulColor("select");
        break;
    case 1:
        setMulColor("diff_high");
        break;
    case 2:
        setMulColor("diff_low");
        break;
    }
    return true;
}

bool GfMenuDiffAdapter::update_Sub(int result) {
    setNumber(m_lhs->getNumber() - m_rhs->getNumber());
    return true;
}

bool GfMenuDiffAdapter::update_DispSameOn(int result) {
    return result == 0;
}

bool GfMenuDiffAdapter::update_DispSameOff(int result) {
    return result != 0;
}

void GfMenuDiffAdapter::update(const fw::UpdateInfo& info) {
    if (m_update.isValid() && (m_flags & 3) != 0) {
        setDisp(m_update(GfMenuAdapter::compare(m_lhs, m_rhs)));
        m_flags &= ~1;
    }
}

}  // namespace gf
