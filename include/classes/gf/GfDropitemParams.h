#ifndef CLASSES_GF_GFDROPITEMPARAMS_H
#define CLASSES_GF_GFDROPITEMPARAMS_H

#include "mm/mtl/Vector.h"

namespace gf {
// a row of RSC_dropitemParam (Vector<GfDropitemParam>::resize, by its symbols, steps 0x5C bytes)
struct GfDropitemParam {
    void loadFromBdat(int& id);

    unsigned char pad_0x0[0x5c];
};

// table 0x7100B528F0
class GfDropitemParams {
public:
    GfDropitemParams();
    virtual ~GfDropitemParams();  // slot 0
    void update();

    mm::mtl::Vector<GfDropitemParam> m_params;  // RSC_dropitemParam's rows (the name is not the original's)
    int m_idTop;  // RSC_dropitemParam's first id (Bdat::getIdTop's; the name is not the original's)
};
}  // namespace gf

#endif
