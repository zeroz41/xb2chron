#ifndef CLASSES_GF_GFARTSMOVIE_H
#define CLASSES_GF_GFARTSMOVIE_H

#include "classes/gf/IGfEvent.h"
namespace fw { class UpdateInfo; }
#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfArtsMovie; }

namespace gf {
// table 0x7100B54488
class GfArtsMovie : public ::mm::mtl::PtrSingleton< ::gf::GfArtsMovie>, public ::gf::IGfEvent {
public:
    virtual ~GfArtsMovie();  // slot 0
    // what GfPlayComArtsMovie runs: setup with the movie's name when it starts, update until it ends, destroy
    void startSetup(const char* name);
    void update(const fw::UpdateInfo& info);
    static void destroy();
    virtual void gevPause(unsigned int, unsigned int);  // slot 2
};
}  // namespace gf

#endif
