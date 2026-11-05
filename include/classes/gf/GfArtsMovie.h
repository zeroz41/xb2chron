#ifndef CLASSES_GF_GFARTSMOVIE_H
#define CLASSES_GF_GFARTSMOVIE_H

#include "classes/gf/IGfEvent.h"
namespace fw { class UpdateInfo; }
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Delegate.h"

namespace gf { class GfArtsMovie; }

namespace gf {
// table 0x7100B54488
class GfArtsMovie : public ::mm::mtl::PtrSingleton< ::gf::GfArtsMovie>, public ::gf::IGfEvent {
public:
    // inline: createSiren builds it in place (1.0.0 had it out of line)
    GfArtsMovie() : m_waitCount(0), m_state(0) {}
    virtual ~GfArtsMovie();  // slot 0
    // makes the arts movie's player (GfPlayFactory::createArtsMovie) and the singleton
    static GfArtsMovie* createSiren();
    static void destroy();
    // what GfPlayComArtsMovie runs: setup with the movie's name when it starts, update until it ends, destroy
    void startSetup(const char* name);
    void update(const fw::UpdateInfo& info);
    // int: SpAttackManager::MovieProc compares it signed (b.ge 2)
    int getState() const;
    virtual void gevPause(unsigned int, unsigned int);  // slot 2

    // the update steps update runs through m_update: wait for the movie to stand by (then play it), wait for it to
    // end, close it
    void updateForSetup(const fw::UpdateInfo& info);
    void updateForPlay(const fw::UpdateInfo& info);
    void updateForMemorySafe(const fw::UpdateInfo& info);

    // the names are not the original's: updateForSetup counts the frames it waits for the movie to stand by
    // (90 at most), m_state is getState's (1 set up, 2 playing, 3 closed)
    unsigned int m_waitCount;
    unsigned int m_state;
    mm::mtl::Delegate<void(const fw::UpdateInfo&)> m_update;  // the update step (the name is not the original's)
};
}  // namespace gf

#endif
