#ifndef CLASSES_GF_GFMENUMANYOBJECTS_H
#define CLASSES_GF_GFMENUMANYOBJECTS_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/Queue.h"
#include "fw/Allocator.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfSetupParam; }

// gf_menu_many_objects.h as the object folder's files include it: the queues' allocations cite it
#define GF_MENU_MANY_OBJECTS_PATH \
    "D:/Monolithsoft/BF2/prog/application/BF2/gf/menu/object/../gf_menu_many_objects.h"

namespace gf {
// table 0x7100B5ED80; its destructor is its singleton's
class GfMenuManyObjects : public ::mm::mtl::PtrSingleton<GfMenuManyObjects> {
public:
    class InfoType;
    GfMenuManyObjects(const GfSetupParam& param);
    virtual ~GfMenuManyObjects();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static bool isInitialized();
    void postUpdate(const fw::UpdateInfo& info);
    // the queue of a kind's open objects (its info T), none past the eighth or before createQueue
    template <typename T>
    static mm::mtl::Queue<T>* getQueue(unsigned int index) {
        return static_cast<mm::mtl::Queue<T>*>(get()->m_queues[index]);
    }
    // a kind's queue with room for capacity (its menu object's initialize makes it; the name is not the original's)
    template <typename T>
    static void createQueue(unsigned int index, unsigned long capacity) {
        GfMenuManyObjects* objects = get();
        mm::mtl::IAllocator* allocator;
        if (objects->m_queues[index] == nullptr && (allocator = fw::Allocator::getProcAllocator()) != nullptr) {
#line 105 GF_MENU_MANY_OBJECTS_PATH
            mm::mtl::Queue<T>* queue = new (allocator, 16, __FILE__, __LINE__) mm::mtl::Queue<T>(allocator);
            if (queue != nullptr) {
                queue->reserve(capacity);
                objects->m_queues[index] = queue;
            }
        }
    }
    // closes a kind's objects and drops its queue (its menu object's destructor; the name is not the original's)
    template <typename T>
    static void destroyQueue(unsigned int index) {
        GfMenuManyObjects* objects = get();
        mm::mtl::Queue<T>* queue = static_cast<mm::mtl::Queue<T>*>(objects->m_queues[index]);
        if (queue != nullptr) {
            closeAll<T>(index, nullptr);
            delete queue;
            objects->m_queues[index] = nullptr;
        }
    }
    // the object of that handle off its kind's queue (disposed)
    template <typename T>
    static void remove(unsigned int index, unsigned int handle);
    // every object off its kind's queue, each handed to close first (when there is one) and disposed
    template <typename T>
    static void closeAll(unsigned int index, void (*close)(unsigned int));
    bool m_initialized;  // set by initialize, cleared by finalize
    // remove and closeAll (templates on the kind of object) index the first eight: each a queue of that kind's
    // open objects, or none
    void* m_queues[9];
};

template <typename T>
void GfMenuManyObjects::remove(unsigned int index, unsigned int handle) {
    if (index < 8) {
        mm::mtl::Queue<T>* queue = getQueue<T>(index);
        if (queue != nullptr) {
            for (typename mm::mtl::Queue<T>::iterator it = queue->begin(); it != queue->end(); ++it) {
                if ((*it).m_handle == handle) {
                    (*it).dispose();
                    it = queue->erase(it);
                    return;
                }
            }
        }
    }
}

template <typename T>
void GfMenuManyObjects::closeAll(unsigned int index, void (*close)(unsigned int)) {
    if (index < 8) {
        mm::mtl::Queue<T>* queue = getQueue<T>(index);
        if (queue != nullptr) {
            typename mm::mtl::Queue<T>::iterator it = queue->begin();
            while (it != queue->end()) {
                if (close != nullptr) {
                    close((*it).m_handle);
                }
                (*it).dispose();
                it = queue->erase(it);
            }
        }
    }
}
}  // namespace gf

#endif
