#ifndef ML_DRRESMDOLODOBJ_H
#define ML_DRRESMDOLODOBJ_H

namespace ml {
// Only release is declared so far.
class DrResMdoLodObj {
public:
    // builds the object at work (its data follows it); returns setup's result
    static unsigned int create(unsigned char* work, const unsigned char* data);
    unsigned int setup(const unsigned char* data, unsigned char* work);
    static void release(DrResMdoLodObj*& obj);
    unsigned char pad_0[0x30];  // create places the object's data 0x30 bytes after it
};
}  // namespace ml

#endif
