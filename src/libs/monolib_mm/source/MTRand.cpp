// Based on MT19937 (mt19937ar-cok.c), Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
// All rights reserved. BSD 3-clause license: see third_party/LICENSES/mt19937.txt.

#include "nn/os.h"
#include "mm/mtl/MTRand.h"
#include "ml/MTRand.h"

namespace ml {

// the generator ml::mtInit seeds and ml::mtRand* draw from, seeded with the system tick at startup (proposed name,
// not the original's: the symbols leave it unnamed, lbl_7100ECE430)
static mm::mtl::MTRand s_rand(nn::os::GetSystemTick().GetInt64Value());

}  // namespace ml

namespace ml {

void mtInit(unsigned int seed) {
    s_rand.init(seed);
}

unsigned int mtRand() {
    return s_rand.next() >> 1;
}

int mtRand(int max) {
    if (max == 0) {
        return 0;
    }
    return static_cast<int>(mtRand()) % max;
}

int mtRand(int min, int max) {
    int range = max - min;
    if (range > 0) {
        min += static_cast<int>(mtRand()) % range;
    }
    return min;
}

float mtRandf1() {
    return s_rand.next() * (1.0 / 4294967295.0);
}

float mtRandf1(float max) {
    if (max > 0.0f) {
        return mtRandf1() * max;
    }
    return 0.0f;
}

float mtRandf1(float min, float max) {
    float range = max - min;
    if (range > 0.0f) {
        min += range * mtRandf1();
    }
    return min;
}

float mtRandf2() {
    return s_rand.next() * 2.3283041087743603e-10;
}

float mtRandf2(float min, float max) {
    float range = max - min;
    if (range > 0.0f) {
        min += range * mtRandf2();
    }
    return min;
}

}  // namespace ml

namespace mm { namespace mtl {

void MTRand::nextMt() {
    unsigned int* p = m_state;
    if (m_initf == 0) {
        init(5489);
    }
    m_left = N;
    m_next = m_state;
    for (int j = N - M + 1; --j; p++) {
        *p = p[M] ^ twist(p[0], p[1]);
    }
    for (int j = M; --j; p++) {
        *p = p[M - N] ^ twist(p[0], p[1]);
    }
    *p = p[M - N] ^ twist(p[0], m_state[0]);
}

}}  // namespace mm::mtl
