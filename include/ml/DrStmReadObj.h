#ifndef ML_DRSTMREADOBJ_H
#define ML_DRSTMREADOBJ_H

namespace ml {
// a stream reader; only the field ScnObjAccStmReadObj::readType writes is known (the name is not the original's)
class DrStmReadObj {
public:
    unsigned char pad_0[0x18];
    int m_readType;  // 0x18, 0..2
};
}  // namespace ml

#endif
