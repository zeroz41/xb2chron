#include "classes/idcoli/IDColiManager.h"
#include "classes/fw/ManagerObject.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiManager.h"
#include "classes/fw/ColiManager/Impl.h"

#include "classes/fw/ColiManager/Impl.h"

namespace fw {

inline void ColiManager::Impl::initialize() {
    if (m_coli == nullptr) {
        m_coli = new (Framework::getAllocator(), 16, __FILE__, 248)
            idcoli::IDColiManager(mm::mtl::PtrSingleton<Framework>::get()->m_scn, FrameworkMemory::getMem(5), 0x80000);
    }
}

inline void ColiManager::Impl::finalize() {
    destroyContactTable();
    for (mm::mtl::IntrusiveList<ColiObject>::iterator it = m_objects.begin(); it != m_objects.end();) {
        ColiObject* object = it.m_node;
        ++it;
        if (object != nullptr && object->m_RefCount == 1) {
            object->release();
        }
    }
    m_grand = nullptr;
    if (m_coli != nullptr) {
        delete m_coli;
        m_coli = nullptr;
    }
}

inline void ColiManager::Impl::update() {
    if (m_coli != nullptr) {
        m_coli->update();
        ++m_frame;
        updateContact();
        sendContactEvent();
    }
    for (mm::mtl::IntrusiveList<ColiObject>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
        (*it).update();
    }
}

inline void ColiManager::Impl::tail() {
    if (m_coli != nullptr) {
        m_coli->tail();
    }
}

ColiManager::Impl::Impl(mm::mtl::IAllocator* allocator, unsigned int count)
    : m_grand(nullptr), m_coli(nullptr), m_frame(1), m_allocator(allocator) {
    m_handles.reserve(allocator, count);
    m_handles.setRange(1, 0x7FFFFFFF, 0x7FFFFFFF);
    m_contactTable.clear();
}

void ColiManager::Impl::removeObject(ColiObject* object) {
    for (mm::mtl::FixedList<ListParam, 512>::iterator it = m_contactTable.begin(); it != m_contactTable.end(); ++it) {
        if (it->m_handle == object->m_objUserData.m_handle) {
            mm::mtl::List<ContactParam>* contacts = it->m_contacts;
            m_contactTable.erase(it);
            contacts->clear();
            delete contacts;
            break;
        }
    }
    if (object->m_objUserData.m_handle != 0) {
        m_handles.remove(object->m_objUserData.m_handle);
    }
    m_objects.remove(object);
    if (m_grand == object) {
        m_grand = nullptr;
    }
}

ColiManager::ColiManager(mm::mtl::IAllocator* allocator, unsigned int count)
    : m_impl(new (allocator, 8, __FILE__, 884) Impl(allocator, count)) {}

ColiManager::~ColiManager() {}

bool ColiManager::initialize() {
    m_impl->initialize();
    return true;
}

bool ColiManager::finalize() {
    m_impl->finalize();
    return true;
}

void ColiManager::update() {
    if (isFinalized()) {
        return;
    }
    m_impl->update();
}

void ColiManager::postUpdate() {
    if (isFinalized()) {
        return;
    }
    m_impl->postUpdate();
}

void ColiManager::tail() {
    if (isFinalized()) {
        return;
    }
    m_impl->tail();
}

void ColiManager::registObject(ColiObject* object) {
    m_impl->registObject(object);
}

void ColiManager::removeObject(ColiObject* object) {
    m_impl->removeObject(object);
}

idcoli::IDColiManager* ColiManager::getInterface() {
    return m_impl->m_coli;
}

ColiObject* ColiManager::getObject(unsigned int handle) const {
    const PointerMap& handles = m_impl->m_handles;
    if (handles.isValid(handle)) {
        return static_cast<ColiObject*>(handles.getPtr(handle));
    }
    return nullptr;
}

bool ColiManager::isGblId(unsigned int id) {
    idcoli::IDColiManager* coli = m_impl->m_coli;
    if (coli != nullptr) {
        return coli->isGblId(id) == 0;
    }
    return false;
}

void ColiManager::setGblId(unsigned int id, bool clear) {
    idcoli::IDColiManager* coli = m_impl->m_coli;
    if (coli != nullptr) {
        coli->setGblId(id, clear);
    }
}

ColiManager::Impl::~Impl() {
    finalize();
}

}  // namespace fw
