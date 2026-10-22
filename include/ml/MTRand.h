#ifndef ML_MTRAND_H
#define ML_MTRAND_H

namespace ml {

// monolib's random numbers, drawn from the Mersenne Twister ml::mtInit seeds (1.0.0's names; see mm/mtl/MTRand.h)
void mtInit(unsigned int seed);
unsigned int mtRand();
int mtRand(int max);
int mtRand(int min, int max);
float mtRandf1();  // in [0, 1) (EyeBlinkPlugin blends its blink interval by it)
float mtRandf1(float max);
float mtRandf1(float min, float max);
float mtRandf2();
float mtRandf2(float max);
float mtRandf2(float min, float max);

}  // namespace ml

#endif
