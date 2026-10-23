#ifndef ML_DRRESMDOMESHOBJ_H
#define ML_DRRESMDOMESHOBJ_H

namespace ml {
// Only release is declared so far.
class DrResMdoMeshObj {
public:
    static void release(DrResMdoMeshObj*& obj);
};
}  // namespace ml

#endif
