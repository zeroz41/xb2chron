#ifndef CLASSES_GF_IDATABDAT_H
#define CLASSES_GF_IDATABDAT_H

namespace gf {
// table 0x7100B47028; the BDAT table classes' base
class IDataBdat {
public:
    virtual ~IDataBdat() {}  // slot 0
    // what GfDataBdat calls on every table class it keeps when the tables are set up again (every class overrides it
    // with its bdatRefresh; the name is not the original's)
    virtual void bdatRefresh() = 0;  // slot 2
};
}  // namespace gf

#endif
