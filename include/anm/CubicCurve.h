#ifndef ANM_CUBICCURVE_H
#define ANM_CUBICCURVE_H

namespace anm {
// one key of a cubic track: from its frame on, the value is a cubic in the frames since it (calcValue). The fields'
// names are not the original's
struct CubicCurve {
    float frame;
    float a;  // times the cube
    float b;  // times the square
    float c;  // times the frames since the key
    float d;  // the value at the key
};

// a key of a cubic track of three values: per value, the cubic's coefficients as CubicCurve's (calcVec3)
struct Cubic3Curve {
    float frame;
    float coefficients[3][4];  // per value: times the cube, the square, the frames since the key, and the value
};

// a key of a cubic track of four values (a rotation's: calcQuat)
struct Cubic4Curve {
    float frame;
    float coefficients[4][4];
};

// orders a frame against the keys of a cubic track by their frames (std::upper_bound's comparator in calcValue)
struct CmpCubic {
    template <typename T>
    bool operator()(float frame, const T& curve) const {
        return frame < curve.frame;
    }
};

template <typename T>
class Array;
// a cubic track of three values' value at a frame, into pValue[0] to pValue[2] (anm_cubic_animation.cpp)
void calcVec3(const Array<Cubic3Curve>& curves, float time, float* pValue);
}  // namespace anm

namespace mm { class Quat; }
namespace anm {
// a cubic track of a rotation's value at a frame, normalized (anm_cubic_animation.cpp)
void calcQuat(const Array<Cubic4Curve>& curves, float time, mm::Quat* pValue);
}  // namespace anm

#endif
