#ifndef CLASSES_SSD_EXTENDEDFLOAT_H
#define CLASSES_SSD_EXTENDEDFLOAT_H

namespace ssd {
// an 80-bit IEEE 754 extended float stored big-endian, as in an AIFF COMM chunk's sample rate (read by
// AudioFileAiff::PreLoad). No table.
class ExtendedFloat {
public:
    // the value as a double (sign, rebiased exponent and the 52 fraction bits after the explicit integer bit)
    double FP80toFP64();

    // the 10 bytes, most significant first (name inferred)
    unsigned char bytes_[10];
};
}  // namespace ssd

#endif
