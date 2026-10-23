#ifndef ML_MTRAND_H
#define ML_MTRAND_H

namespace ml {

// monolib's random floats, drawn from the Mersenne Twister ml::mtInit seeds (src/ml/ErrViewer.cpp's s_rand)
float mtRandf1();                      // in [0, 1]
float mtRandf1(float min, float max);  // min plus that times (max - min); min when max is not above it
int mtRand(int max);  // a random int below max (0 for 0), from the same twister; the parameter name is not the original's

}  // namespace ml

#endif
