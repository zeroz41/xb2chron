#ifndef CLASSES_GF_GFDATABDAT_H
#define CLASSES_GF_GFDATABDAT_H

namespace gf {
// its table has no name yet, so its virtuals are not declared here
class GfDataBdat {
public:
    static unsigned char* getFP(unsigned int id);  // the loaded BDAT file of that id
};
}  // namespace gf

#endif
