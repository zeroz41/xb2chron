#ifndef CLASSES_GF_SCOM_RANDOM_INN_H
#define CLASSES_GF_SCOM_RANDOM_INN_H

namespace gf {
// no table in 3.0.1: a static forward to GfDataUtil::setRandomInn
class SCOM_RANDOM_INN {
public:
    static void setRandom();
};
}  // namespace gf

#endif
