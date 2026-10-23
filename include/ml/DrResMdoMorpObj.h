#ifndef ML_DRRESMDOMORPOBJ_H
#define ML_DRRESMDOMORPOBJ_H

namespace ml {
// Only release is declared so far.
class DrResMdoMorpObj {
public:
    static void release(DrResMdoMorpObj*& obj);
};
}  // namespace ml

#endif
