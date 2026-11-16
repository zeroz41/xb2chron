#ifndef ML_MTRAND_H
#define ML_MTRAND_H

namespace ml {

// monolib's random numbers, drawn from the Mersenne Twister ml::mtInit seeds (1.0.0's names; see mm/mtl/MTRand.h)
void mtInit(unsigned int seed);
unsigned int mtRand();
int mtRand(int max);  // a random int below max (0 for 0)
int mtRand(int min, int max);
float mtRandf1();  // in [0, 1) (EyeBlinkPlugin blends its blink interval by it)
float mtRandf1(float max);
float mtRandf1(float min, float max);  // min plus mtRandf1() times (max - min); min when max is not above it
float mtRandf2();
float mtRandf2(float max);
float mtRandf2(float min, float max);

}  // namespace ml

#endif
