#ifndef GF_GFALPHAPROPERTY_H
#define GF_GFALPHAPROPERTY_H

namespace gf {
// which of an object's alphas (GfObjAcc's setAlphaNormal 0, setAlphaCamera 2, setAlphaEvent 3, setAlphaLife 4,
// setAlphaEvtDisp 5 pass it)
enum OBJ_ALPHA {};

// no table: an object's alphas, held by its GfComProperty (the class name is 1.0.0's)
class GfAlphaProperty {
public:
    float m_alpha[6];  // by OBJ_ALPHA: GfObjAcc::getAlpha(OBJ_ALPHA) reads one
    // the alphas multiplied: GfObjAcc::getAlpha multiplies the object's and its parents' (the name is not the
    // original's)
    float m_total;
    // GfObjAcc::isAlphaChanged returns it (the name is not the original's)
    bool m_changed;
};
}  // namespace gf

#endif
