#ifndef CLASSES_SSD_XORSHIFT128RANDOM_H
#define CLASSES_SSD_XORSHIFT128RANDOM_H

namespace ssd {
// table 0x7100B81E58
class XorShift128Random {
public:
    virtual void SetSeed(unsigned int);  // slot 0
    virtual void GetRandom();  // slot 1
    virtual void GetF32Random();  // slot 2
    virtual void GetF64Random();  // slot 3
    virtual void GetAfter() const;  // slot 4
};
}  // namespace ssd

#endif
