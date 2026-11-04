#ifndef CLASSES_GMK_DISTCOND_H
#define CLASSES_GMK_DISTCOND_H

namespace mm { class Vec3; }

namespace gmk {
// a gimmick distance condition (1.0.0's name; 1.0.0 also has its debugDraw(const mm::Vec3&, const mm::Col4&) const)
class DistCond {
public:
    // whether pos lies within the square root of distSq of the interest position (gmk::getInterestPos), false while
    // there is no camera or player to measure from (1.0.0's name: 1.0.0's GfGameUtil::isUiNameDistMatch calls it in
    // the place of 3.0.1's isMatch, with the squared distance and the object's position)
    static bool isMatch(float distSq, const mm::Vec3& pos);
};
}  // namespace gmk

#endif
