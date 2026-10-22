#ifndef GF_ACCESSPARAM_H
#define GF_ACCESSPARAM_H

namespace gf {

// the reach within which the PC can access (AccessPlugin) or lure (LurePlugin) an object; the field names are
// 1.0.0's AccessParam::createReflection's, which registers them by name and offset
struct AccessParam {
    float offsetFront;   // the reach's centre, this far ahead of the PC
    float accessRadius;  // its radius across the ground
    float accessUpper;   // how far above the centre it reaches
    float accessDown;    // and below
};

}  // namespace gf

#endif
