#ifndef MM_MTL_MTRAND_H
#define MM_MTL_MTRAND_H

namespace mm { namespace mtl {

// mm_lib's Mersenne Twister (MT19937): 624 words of state, then how many are left before the next refill, whether
// it has been seeded, the next word to temper and the seed. nextMt() refills the state, seeding it with 5489
// first when nothing has; ml::mtInit seeds the one behind ml::mtRand*, 0 meaning 19650218.
class MTRand {
public:
    enum { N = 624 };

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

    unsigned int m_state[N];
    int m_left;
    int m_initf;
    unsigned int* m_next;
    unsigned int m_seed;
};

}}  // namespace mm::mtl

#endif
