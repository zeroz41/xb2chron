#ifndef CLASSES_GF_GFMENUSCRIPTMANAGER_H
#define CLASSES_GF_GFMENUSCRIPTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuScriptManager; }

namespace gf {
// table 0x7100B5EFC8
class GfMenuScriptManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuScriptManager> {
public:
    class ScriptListener;
    virtual ~GfMenuScriptManager();  // slot 0
};
}  // namespace gf

#endif
