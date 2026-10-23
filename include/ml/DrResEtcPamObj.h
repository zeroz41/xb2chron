#ifndef ML_DRRESETCPAMOBJ_H
#define ML_DRRESETCPAMOBJ_H

namespace ml {
// Only release is declared so far.
class DrResEtcPamObj {
public:
    static void release(DrResEtcPamObj*& obj);
};
}  // namespace ml

#endif
