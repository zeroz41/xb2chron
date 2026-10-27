#ifndef MICROUPDATER_H
#define MICROUPDATER_H

#include "classes/ml/MicroThread.h"
#include "mm/mtl/Delegate.h"

namespace nn { namespace os { class FiberType; }}

// runs a function of T on a micro thread of its own group (1.0.0's symbol MicroUpdater<tl::TitleMain>::fnMicroUpdate
// names the class and its thread function; tl::TitleMain::initialize makes one and starts it, 0x38 bytes)
template <typename T>
class MicroUpdater {
public:
    MicroUpdater()
        : m_group(reinterpret_cast<ml::MLTHG*>(-1)), m_thread(reinterpret_cast<ml::MLTH*>(-1)), m_object(nullptr) {}

    // starts func(object) on a new thread of a new group, once (the name is not the original's)
    void start(T* object, void (*func)(T*)) {
        if (m_group == reinterpret_cast<ml::MLTHG*>(-1)) {
            m_group = ml::MicroThread::sys()->createGroup();
            m_thread = ml::MicroThread::sys()->createThread(m_group, &fnMicroUpdate, this);
            m_delegate.set(func);
            m_object = object;
        }
    }

    // (the original releases the thread only when it has ended: m_thread is -1 then)
    ~MicroUpdater() {
        if (m_thread == reinterpret_cast<ml::MLTH*>(-1)) {
            ml::MicroThread::sys()->releaseThread(m_thread);
        }
        if (m_group != reinterpret_cast<ml::MLTHG*>(-1)) {
            ml::MicroThread::sys()->releaseGroup(m_group);
        }
    }

    // runs the group a frame; once the thread has ended, releases the group (the name is not the original's)
    void update() {
        if (m_group != reinterpret_cast<ml::MLTHG*>(-1)) {
            ml::MicroThread::sys()->update(m_group);
            if (m_thread == reinterpret_cast<ml::MLTH*>(-1)) {
                ml::MicroThread::sys()->releaseGroup(m_group);
                m_group = reinterpret_cast<ml::MLTHG*>(-1);
            }
        }
    }

    // the thread's function: runs the delegate on the object, then ends the thread
    static nn::os::FiberType* fnMicroUpdate(void*) {
        MicroUpdater* self = static_cast<MicroUpdater*>(ml::MicroThread::sys()->getCurrentUserData());
        self->m_delegate(self->m_object);
        self->m_thread = reinterpret_cast<ml::MLTH*>(-1);
        ml::MicroThread::sys()->exit();
        return nullptr;
    }

    // (the field names are not the original's)
    ml::MLTHG* m_group;   // -1 until started
    ml::MLTH* m_thread;   // -1 when none runs
    T* m_object;
    mm::mtl::Delegate<void(T*)> m_delegate;
};

#endif
