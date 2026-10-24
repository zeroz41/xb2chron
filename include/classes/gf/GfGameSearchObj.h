#ifndef CLASSES_GF_GFGAMESEARCHOBJ_H
#define CLASSES_GF_GFGAMESEARCHOBJ_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedList.h"

namespace gf { class GF_SEARCH_OBJ; }
namespace gf { class GfGameSearchObj; }
namespace gf { class GfSearchInfo; }
namespace gf { class GfSearchParam; }

namespace gf {
// table 0x7100B55F30
class GfGameSearchObj : public ::mm::mtl::PtrSingleton< ::gf::GfGameSearchObj> {
public:
    class GFSEARCH_INFO;
    virtual ~GfGameSearchObj();  // slot 0
    // what a search found, by its handle
    static mm::mtl::FixedList<gf::GfSearchInfo*, 256>* getObj(gf::GF_SEARCH_OBJ* obj);
    static gf::GF_SEARCH_OBJ* createObj(const gf::GfSearchParam& param);
    // the search's parameters as createObj copied them, null for no search
    static gf::GfSearchParam* getInfo(gf::GF_SEARCH_OBJ* obj);
    static void destroyObj(gf::GF_SEARCH_OBJ* obj);
    static void setEnable(gf::GF_SEARCH_OBJ* obj, bool enable);
    static bool isEnable(gf::GF_SEARCH_OBJ* obj);
};
}  // namespace gf

#endif
