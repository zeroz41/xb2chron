#ifndef CLASSES_FW_COLIMANAGER_IMPL_H
#define CLASSES_FW_COLIMANAGER_IMPL_H

#include "classes/fw/ColiManager.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/PointerMap.h"
#include "fw/ColiCheck.h"
#include "classes/fw/Framework.h"
#include "classes/fw/FrameworkMemory.h"
#include "classes/idcoli/IDColiManager.h"
#include "classes/mm/mtl/IAllocator.h"
#include "mm/Vec3.h"
#include "classes/mm/mtl/List.h"
#include "mm/mtl/FixedList.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw {
// a class with no table, 0x3498 bytes (ColiManager's constructor allocates it). The field names are not the
// original's.
class ColiManager::Impl {
public:
    // a contact between two objects (makeContactList and addContactList fill it, sendContactEvent hands it to
    // both objects as an EnterInfo): 0x40 bytes. m_flags: bit 0 entered, bit 1 touching this frame, bit 2 left,
    // bit 3 touching the last frame (sendContactEvent's), bit 4 set with an enter while not leaving. The field
    // names are not the original's.
    class ContactParam {
    public:
        ContactParam() : m_flags(0) {}
        mm::Vec3 m_pos;        // the hit's position
        unsigned int m_frame;  // the update (m_frame) that saw it
        mm::Vec3 m_normal;     // the hit's normal
        unsigned int m_self;   // the list owner's handle
        unsigned int m_other;  // the other object's handle
        unsigned int m_flags;
    };
    // a character's contacts, by its handle (registObject adds one per character, removeObject erases it)
    struct ListParam {
        unsigned int m_handle;
        mm::mtl::List<ContactParam>* m_contacts;
    };

    Impl(mm::mtl::IAllocator* allocator, unsigned int count);
    ~Impl();
    void updateContact();
    void sendContactEvent();
    void postUpdate();
    void destroyContactTable();
    void makeContactList(ColiObject* object, TColiCheckResult<256>& result, mm::mtl::List<ContactParam>* contacts);
    void addContactList(ColiObject* object, ColiObject* other, const ContactParam& param);
    void registObject(ColiObject* object);
    void removeObject(ColiObject* object);
    // ColiManager's initialize, finalize, update and tail (the destructor finalizes too): the collision system
    // made once; the objects released and the collision system destroyed; the collision system's update, the
    // contacts and every object's; the collision system's tail. Inline in coli_manager.cpp (the names are not the
    // original's)
    inline void initialize();
    inline void finalize();
    inline void update();
    inline void tail();

    mm::mtl::IntrusiveList<ColiObject> m_objects;  // registObject's
    ColiObject* m_grand;                           // the last ground object registered
    idcoli::IDColiManager* m_coli;                 // ColiManager::initialize's
    unsigned int m_frame;                          // the updates run (1 first)
    mm::mtl::IAllocator* m_allocator;              // the constructor's: the contact lists come from it
    PointerMap m_handles;                          // the objects' handles
    mm::mtl::FixedList<ListParam, 512> m_contactTable;
};
}  // namespace fw

#endif
