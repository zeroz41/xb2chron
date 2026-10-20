#ifndef CLASSES_GF_GFQUESTMANAGER_H
#define CLASSES_GF_GFQUESTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfQuestManager; }

namespace gf {
// table 0x7100B56DB0
class GfQuestManager : public ::mm::mtl::PtrSingleton< ::gf::GfQuestManager> {
public:
    virtual ~GfQuestManager();  // slot 0
};
}  // namespace gf

#endif
