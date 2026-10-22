#ifndef CLASSES_GF_GFMENUSOUNDMANAGER_H
#define CLASSES_GF_GFMENUSOUNDMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuSoundManager; }

namespace gf {
// table 0x7100B5F070
class GfMenuSoundManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuSoundManager> {
public:
    virtual ~GfMenuSoundManager();  // slot 0
    static void fadeOutFieldBgm(float time);
    static void fadeFieldBgm(float volume, float time);
};
}  // namespace gf

#endif
