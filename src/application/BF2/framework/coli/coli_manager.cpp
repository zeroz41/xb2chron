#include "classes/idcoli/IDColiManager.h"
#include "classes/fw/ManagerObject.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/ColiManager.h"
#include "classes/fw/ColiManager/Impl.h"

#include "classes/fw/ColiManager/Impl.h"
#include "classes/mm/mtl/List.h"
#include "fw/ColiCheck.h"

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

void ColiManager::Impl::updateContact() {
    TColiCheckResult<256> result;
    for (mm::mtl::IntrusiveList<ColiObject>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
        ColiObject* object = it.m_node;
        if (!object->isChar()) {
            continue;
        }
        mm::mtl::List<ContactParam>* contacts = nullptr;
        unsigned int handle = object->m_objUserData.m_handle;
        for (mm::mtl::FixedList<ListParam, 512>::iterator param = m_contactTable.begin();
             param != m_contactTable.end(); ++param) {
            if (param->m_handle == handle) {
                contacts = param->m_contacts;
                break;
            }
        }
        if (object->m_RefCount == 1) {
            if (contacts != nullptr) {
                for (mm::mtl::List<ContactParam>::iterator contact = contacts->begin(); contact != contacts->end();
                     ++contact) {
                    if (contact->m_flags & 8) {
                        contact->m_flags |= 4;
                    }
                    contact->m_flags &= ~0xA;
                }
            }
        } else {
            ColiCheckConfig config;
            config.m_mode = 2;
            config.m_flags = 2;
            config.m_mask = 0xFFEFFFFF;
            config.pad_c = 0.1f;
            result.clear();
            if (ColiCheck::testObjectChara(result, object, config)) {
                makeContactList(object, result, contacts);
            }
            result.clear();
            if (ColiCheck::testObjectPhantom(result, object, config)) {
                makeContactList(object, result, contacts);
            }
        }
    }
}

void ColiManager::Impl::sendContactEvent() {
    for (mm::mtl::FixedList<ListParam, 512>::iterator param = m_contactTable.begin(); param != m_contactTable.end();
         ++param) {
        mm::mtl::List<ContactParam>* contacts = param->m_contacts;
        ColiObject* self = static_cast<ColiObject*>(m_handles.getPtr(param->m_handle));
        for (mm::mtl::List<ContactParam>::iterator it = contacts->begin(); it != contacts->end();) {
            ContactParam& contact = *it;
            ColiObject* other = static_cast<ColiObject*>(m_handles.getPtr(contact.m_other));
            if (other == nullptr) {
                it = contacts->erase(it);
                continue;
            }
            IColiEventListener::EnterInfo enter;
            enter.m_self = self;
            enter.m_other = other;
            enter.m_pos = contact.m_pos;
            enter.m_normal = contact.m_normal;
            IColiEventListener::EnterInfo otherEnter;
            otherEnter.m_self = other;
            otherEnter.m_other = self;
            otherEnter.m_pos = contact.m_pos;
            otherEnter.m_normal = contact.m_normal;
            IColiEventListener::LeaveInfo leave;
            leave.m_self = self;
            leave.m_other = other;
            IColiEventListener::LeaveInfo otherLeave;
            otherLeave.m_self = other;
            otherLeave.m_other = self;
            if ((contact.m_flags & 5) == 1) {
                contact.m_flags |= 0x10;
            }
            if ((contact.m_flags & 0x1A) == 0x18) {
                contact.m_flags |= 4;
            }
            if (contact.m_flags & 1) {
                self->enter(enter);
                if (!other->isChar()) {
                    other->enter(otherEnter);
                }
            }
            if (contact.m_flags & 2) {
                self->contact(enter);
                if (!other->isChar()) {
                    other->contact(otherEnter);
                }
            }
            if (contact.m_flags & 4) {
                self->leave(leave);
                if (!other->isChar()) {
                    other->leave(otherLeave);
                }
            }
            if (contact.m_flags & 2) {
                contact.m_flags |= 8;
            } else {
                contact.m_flags &= ~8;
            }
            contact.m_flags &= ~1;
            if (contact.m_flags & 4) {
                it = contacts->erase(it);
            } else {
                ++it;
            }
            contact.m_flags &= ~7;
        }
    }
}

void ColiManager::Impl::postUpdate() {
    for (mm::mtl::IntrusiveList<ColiObject>::iterator it = m_objects.begin(); it != m_objects.end();) {
        ColiObject* object = it.m_node;
        ++it;
        if (object != nullptr && object->m_RefCount == 1) {
            object->release();
        }
    }
    for (mm::mtl::IntrusiveList<ColiObject>::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
        (*it).postUpdate();
    }
    if (m_coli != nullptr) {
        m_coli->consistentUpdate();
    }
}

void ColiManager::Impl::destroyContactTable() {
    for (mm::mtl::FixedList<ListParam, 512>::iterator it = m_contactTable.begin(); it != m_contactTable.end(); ++it) {
        mm::mtl::List<ContactParam>* contacts = it->m_contacts;
        contacts->clear();
        delete contacts;
    }
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
}  // namespace fw

template mm::mtl::List<fw::ColiManager::Impl::ContactParam>::~List();

template mm::mtl::_ReslistBase<fw::ColiManager::Impl::ContactParam>::~_ReslistBase();

namespace fw {

ColiManager::Impl::~Impl() {
    finalize();
}

}  // namespace fw
