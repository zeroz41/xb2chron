#ifndef CLASSES_GF_GFACHIEVMANAGER_H
#define CLASSES_GF_GFACHIEVMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfAchievManager; }

namespace gf {
// table 0x7100B52BF0
class GfAchievManager : public ::mm::mtl::PtrSingleton< ::gf::GfAchievManager> {
public:
    void gevItemAdd(unsigned int, int);
    virtual ~GfAchievManager();  // slot 0
};
}  // namespace gf

#endif
