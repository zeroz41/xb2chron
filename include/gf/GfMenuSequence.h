#ifndef GF_GFMENUSEQUENCE_H
#define GF_GFMENUSEQUENCE_H

#include "mm/mtl/Delegate.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/ui/UIObjectAcc.h"

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
        // addAnimJob builds one from its arguments: the handle is stored before the name is copied
        AnimJob(unsigned int handle, const char* name) : m_handle(handle), m_name(name) {}
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
    // a job that is a member of another class, run on the sequence's object: GfMenuObjPopup's gift sequence is a
    // GfMenuSequence<GfMenuObjShop, 8> (1.0.0's and 3.0.1's symbols of its addAnimJob and wait_anim), yet its jobs
    // are GfMenuObjPopup's members, called on the sequence's object (seqGiftOut builds the delegate from the
    // owner at 0x278 with memberFuncInvoker<GfMenuObjPopup>)
    template <typename U>
    void addJob(bool (U::*job)()) {
        mm::mtl::Delegate<bool()> delegate;
        delegate.set((U*)m_owner, job);
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
    // queues an animation of a UI object: the object and the animation's name for wait_anim, and a job of the
    // sequence's own that runs it
    void addAnimJob(unsigned int handle, const char* name);
    // the job addAnimJob queues: starts the first animation, then drops it once it has stopped playing
    bool wait_anim();

    mm::mtl::FixedVector<mm::mtl::Delegate<bool()>, N> m_jobs;
    mm::mtl::FixedVector<int, N> m_waits;  // the frame counts wait() counts down, first to last
    mm::mtl::FixedVector<AnimJob, N> m_anims;
    T* m_owner;           // the jobs' object
    bool m_waiting;       // wait(): counting the first wait down
    int m_waitCount;      // wait(): the frames left of it
    bool m_animStarted;   // wait_anim(): the first animation has started
};

// wait(), addAnimJob and wait_anim are out of line in both versions (gf_menu_obj_quest_log emits them for
// GfMenuSequence<GfMenuObjQuestLog, 8> and wait for <GfMenuObjQuestLog, 12>). wait clears the count after its
// erase of the first one, then the flag
template <typename T, int N>
bool GfMenuSequence<T, N>::wait() {
    if (m_waits.empty()) {
        return true;
    }
    if (!m_waiting) {
        m_waitCount = *m_waits.begin();
        m_waiting = true;
        return false;
    }
    if (--m_waitCount != 0) {
        return false;
    }
    m_waits.erase(m_waits.begin());
    m_waitCount = 0;
    m_waiting = false;
    return true;
}

template <typename T, int N>
bool GfMenuSequence<T, N>::wait_anim() {
    if (m_anims.empty()) {
        return true;
    }
    ui::UIObjectAcc acc(m_anims.begin()->m_handle);
    if (!m_animStarted) {
        acc.startAnimation(m_anims.begin()->m_name.m_str, false);
        m_animStarted = true;
        return false;
    }
    if (acc.isPlayingAnimation()) {
        return false;
    }
    m_anims.erase(m_anims.begin());
    m_animStarted = false;
    return true;
}

template <typename T, int N>
void GfMenuSequence<T, N>::addAnimJob(unsigned int handle, const char* name) {
    m_anims.push_back(AnimJob(handle, name));
    mm::mtl::Delegate<bool()> delegate;
    delegate.set(this, &GfMenuSequence::wait_anim);
    m_jobs.push_back(delegate);
}

}  // namespace gf

#endif
