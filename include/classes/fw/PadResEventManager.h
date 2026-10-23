#ifndef CLASSES_FW_PADRESEVENTMANAGER_H
#define CLASSES_FW_PADRESEVENTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/Vector.h"
#include "classes/fw/PadResEvent.h"

namespace fw { class PadResEventManager; }

namespace fw {
// table 0x7100B42900; the pad event resources by index (fw::PadRelay::bind's second argument picks one)
class PadResEventManager : public ::mm::mtl::PtrSingleton< ::fw::PadResEventManager> {
public:
    PadResEventManager();
    virtual ~PadResEventManager();  // slot 0

    void setup(unsigned int count, mm::mtl::IAllocator* allocator);
    void cleanup();
    static void setResource(unsigned int index, const PadResEvent* resource);
    // the resource at index (the name is not the original's)
    const PadResEvent* getResource(unsigned int index) const { return m_resources[index].get(); }

    mm::mtl::Vector<mm::mtl::IntrusivePtr<const PadResEvent> > m_resources;  // the name is not the original's
};
}  // namespace fw

#endif
