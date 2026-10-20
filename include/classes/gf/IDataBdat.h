#ifndef CLASSES_GF_IDATABDAT_H
#define CLASSES_GF_IDATABDAT_H

namespace gf {
// table 0x7100B47028
class IDataBdat {
public:
    virtual ~IDataBdat();  // slot 0
    virtual void vf2() = 0;  // slot 2
};
}  // namespace gf

#endif
