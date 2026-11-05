#ifndef CLASSES_GMK_DISTHVCOND_H
#define CLASSES_GMK_DISTHVCOND_H

#include "mm/Vec3.h"

namespace gmk {
// a pair of squared distances (8 bytes, no table): isMatch answers whether the interest position (gmk::getInterestPos)
// lies within m_horizontalSq on the XZ plane and m_verticalSq on Y of a position. The gimmick rows keep two: the
// ene_disp_r/h distances (pop) and ene_release_r/h (depop). The field names are not the original's.
struct DistHvCond {
    bool isMatch(const mm::Vec3& pos) const;
    float m_horizontalSq;
    float m_verticalSq;
};
}  // namespace gmk

#endif
