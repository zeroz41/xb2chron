#ifndef ML_DRAPGXTYPE_H
#define ML_DRAPGXTYPE_H

namespace ml {
// Static setters of the drawing state for the renderer's passes (they take no object: no function reads x0 as this).
class DrAPGxType {
public:
    static void endOccQuery();
    static void beginShadow();
    static void endShadow();
    static void beginColorOff();
    static void endColorOff();
    static void setupCullingOff();
    static void setupCullingFront();
    static void setupCullingBack();
    // the depth test and write switches and the compare function (the light debug renders pass 1, 1, 3)
    static void setupDepthContl(unsigned char, unsigned char, int);
    static void setupBlend(int);
};
}  // namespace ml

#endif
