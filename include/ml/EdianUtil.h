#ifndef ML_EDIANUTIL_H
#define ML_EDIANUTIL_H

namespace ml {

// monolib's byte-order helpers (ml/Scn.cpp's range): a big-endian value read from memory
class EdianUtil {
public:
    static unsigned int read(const unsigned int& value);
    static short read(const short& value);
};

}  // namespace ml

#endif
