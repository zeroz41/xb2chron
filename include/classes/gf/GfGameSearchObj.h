#ifndef CLASSES_GF_GFGAMESEARCHOBJ_H
#define CLASSES_GF_GFGAMESEARCHOBJ_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GF_SEARCH_OBJ; }
namespace gf { class GfGameSearchObj; }

namespace gf {
// table 0x7100B55F30
class GfGameSearchObj : public ::mm::mtl::PtrSingleton< ::gf::GfGameSearchObj> {
public:
    class GFSEARCH_INFO;
    virtual ~GfGameSearchObj();  // slot 0
    static void destroyObj(gf::GF_SEARCH_OBJ* obj);
    static void setEnable(gf::GF_SEARCH_OBJ* obj, bool enable);
};
}  // namespace gf

#endif
