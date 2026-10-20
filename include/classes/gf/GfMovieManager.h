#ifndef CLASSES_GF_GFMOVIEMANAGER_H
#define CLASSES_GF_GFMOVIEMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMovieManager; }

namespace gf {
// table 0x7100B654C8
class GfMovieManager : public ::mm::mtl::PtrSingleton< ::gf::GfMovieManager> {
public:
    virtual ~GfMovieManager();  // slot 0
};
}  // namespace gf

#endif
