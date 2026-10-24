#ifndef CLASSES_SSD_XORSHIFT128RANDOM_H
#define CLASSES_SSD_XORSHIFT128RANDOM_H

namespace ssd {
// table 0x7100B81E58: Marsaglia's xorshift128 (the state's name is not the original's); SystemCore holds one
// at 0x9A0. Every member is inline: the module keeps them after the SystemCore code that first uses them.
class XorShift128Random {
public:
    // fills the state as the Mersenne Twister's initialization does (1812433253)
    virtual void SetSeed(unsigned int seed) {  // slot 0
        unsigned int s = seed;
        for (int i = 0; i < 4; i++) {
            s = 1812433253u * (s ^ (s >> 30)) + (i + 1);
            state_[i] = s;
        }
    }
    virtual unsigned int GetRandom() {  // slot 1
        unsigned int t = state_[0] ^ (state_[0] << 11);
        state_[0] = state_[1];
        state_[1] = state_[2];
        state_[2] = state_[3];
        state_[3] = (state_[3] ^ (state_[3] >> 19)) ^ (t ^ (t >> 8));
        return state_[3];
    }
    // [0, 1)
    virtual float GetF32Random() {  // slot 2
        return (GetRandom() & 0x7FFFFFFF) * (1.0f / 2147483648.0f);
    }
    // [0, 1]
    virtual double GetF64Random() {  // slot 3
        return (GetRandom() & 0x7FFFFFFF) / 2147483647.0;
    }
    // the last value, as GetF32Random gave it
    virtual double GetAfter() const {  // slot 4
        return (state_[3] & 0x7FFFFFFF) * (1.0f / 2147483648.0f);
    }

    unsigned int state_[4];
};
}  // namespace ssd

#endif
