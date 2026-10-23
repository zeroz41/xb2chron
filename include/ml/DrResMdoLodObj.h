#ifndef ML_DRRESMDOLODOBJ_H
#define ML_DRRESMDOLODOBJ_H

namespace ml {
// Only release is declared so far.
class DrResMdoLodObj {
public:
    static void release(DrResMdoLodObj*& obj);
};
}  // namespace ml

#endif
