#ifndef GF_GFMENUSEQUENCE_H
#define GF_GFMENUSEQUENCE_H

#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace gf {

// 1.0.0's gf::GfMenuSequence<T, N> (its wait, wait_anim and addAnimJob are out of line there, and
// Delegate<bool ()>::memberFuncInvoker of it): a menu object's queue of up to N jobs, members of the object (or of
// the sequence) its update calls until each returns true. The layout is from those functions and from the
// constructors and destructors of the classes that hold one (GfMenuObjMercenaryRoot: N 4 at 0x28;
// GfMenuObjBladeSwitch: N 8 at 0x28).
template <typename T, int N>
class GfMenuSequence {
public:
    // an animation addAnimJob queues for wait_anim: the object and the animation's name
    struct AnimJob {
        unsigned int m_handle;
        mm::mtl::FixStr<32> m_name;
    };

    GfMenuSequence(T* owner) : m_owner(owner), m_waiting(false), m_animStarted(false) {}

    // the names of addJob, update and clear are not the original's (they are inline in both versions)
    void addJob(bool (T::*job)()) {
        mm::mtl::Delegate<bool()> delegate;
        delegate.set(m_owner, job);
        m_jobs.push_back(delegate);
    }
    // runs the first job, and drops it once it returns true
    void update() {
        if (!m_jobs.empty()) {
            if (m_jobs.begin()[0]()) {
                m_jobs.erase(m_jobs.begin());
            }
        }
    }
    void clear() {
        m_jobs.clear();
        m_waits.clear();
        m_anims.clear();
        m_animStarted = false;
        m_waiting = false;
        m_waitCount = 0;
    }
    // queues a wait of that many frames: the count for wait() and a job of the sequence's own that runs it
    // (GfMenuObjBladeName::seqStart and seqApperWait inline it; the name is not the original's)
    void addWait(int frames) {
        mm::mtl::Delegate<bool()> delegate;
        delegate.set(this, &GfMenuSequence::wait);
        m_waits.push_back(frames);
        m_jobs.push_back(delegate);
    }
    // the job addWait queues: counts the first wait's frames down, then drops it
    bool wait();

    mm::mtl::FixedVector<mm::mtl::Delegate<bool()>, N> m_jobs;
    mm::mtl::FixedVector<int, N> m_waits;  // the frame counts wait() counts down, first to last
    mm::mtl::FixedVector<AnimJob, N> m_anims;
    T* m_owner;           // the jobs' object
    bool m_waiting;       // wait(): counting the first wait down
    int m_waitCount;      // wait(): the frames left of it
    bool m_animStarted;   // wait_anim(): the first animation has started
};

// wait() is out of line in both versions (gf_menu_obj_blade_name emits GfMenuSequence<GfMenuObjBladeName, 8>'s);
// its body is not here yet: no candidate compiles identical (see the report)

}  // namespace gf

#endif
