#ifndef CLASSES_ML_DRRESMDOSEAMCOLI_H
#define CLASSES_ML_DRRESMDOSEAMCOLI_H

namespace ml {
// table 0x7100B7DA08
class DrResMdoSeamColi {
public:
    virtual ~DrResMdoSeamColi();  // slot 0

    // 0x48 bytes: the constructor (DrResMdoSeamColi(int)) sets up to 0x40 and DrMdoCtlSeam's collision pool
    // destroys its works at that stride
    unsigned char pad_8[0x40];
};
}  // namespace ml

#endif
