#ifndef CLASSES_GF_GFMENUADAPTERMANAGER_H
#define CLASSES_GF_GFMENUADAPTERMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuAdapterManager; }

namespace gf {
// table 0x7100B59CA8
class GfMenuAdapterManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuAdapterManager> {
public:
    virtual ~GfMenuAdapterManager();  // slot 0
    // the category adapters made from now on belong to (0 after endCategory), and the categories that update
    static void beginCategory(unsigned int category);
    static void endCategory();
    static void addActiveCategory(unsigned int category);
};
}  // namespace gf

#endif
