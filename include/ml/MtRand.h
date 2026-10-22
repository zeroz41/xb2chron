#ifndef ML_MTRAND_H
#define ML_MTRAND_H

namespace ml {

// monolib's random floats, drawn from the Mersenne Twister ml::mtInit seeds (src/ml/ErrViewer.cpp's s_rand)
float mtRandf1();                      // in [0, 1]
float mtRandf1(float min, float max);  // min plus that times (max - min); min when max is not above it

}  // namespace ml

#endif
