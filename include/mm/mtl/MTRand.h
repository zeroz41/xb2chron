// Based on MT19937 (mt19937ar-cok.c), Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
// All rights reserved. BSD 3-clause license: see third_party/LICENSES/mt19937.txt.

#ifndef MM_MTL_MTRAND_H
#define MM_MTL_MTRAND_H

namespace mm { namespace mtl {

// mm_lib's Mersenne Twister (MT19937): 624 words of state, then how many are left before the next refill, whether
// it has been seeded, the next word to temper and the seed. nextMt() refills the state, seeding it with 5489
// first when nothing has; ml::mtInit seeds the one behind ml::mtRand*, 0 meaning 19650218.
class MTRand {
public:
    enum { N = 624, M = 397 };

    MTRand(unsigned int seed) {
        init(seed);
    }

    void init(unsigned int seed) {
        if (seed == 0) {
            seed = 19650218;
        }
        m_seed = seed;
        m_state[0] = seed;
        for (int i = 1; i < N; i++) {
            m_state[i] = 1812433253 * (m_state[i - 1] ^ (m_state[i - 1] >> 30)) + i;
        }
        m_left = 1;
        m_initf = 1;
    }
    void nextMt();
    // one twisted word from u's upper bit and v's lower bits (the reference MT19937's TWIST macro; the name is not
    // the original's)
    static unsigned int twist(unsigned int u, unsigned int v) {
        return (((u & 0x80000000) | (v & 0x7fffffff)) >> 1) ^ ((v & 1) ? 0x9908b0df : 0);
    }
    // the next tempered 32-bit word (the reference MT19937's genrand_int32; the name is not the original's):
    // ml::mtRand* inline it
    unsigned int next() {
        if (--m_left <= 0) {
            nextMt();
        }
        unsigned int y = *m_next++;
        y ^= y >> 11;
        y ^= (y << 7) & 0x9d2c5680;
        y ^= (y << 15) & 0xefc60000;
        y ^= y >> 18;
        return y;
    }

    unsigned int m_state[N];
    int m_left;
    int m_initf;
    unsigned int* m_next;
    unsigned int m_seed;
};

}}  // namespace mm::mtl

#endif
