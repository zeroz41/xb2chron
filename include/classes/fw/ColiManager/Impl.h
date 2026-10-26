#ifndef CLASSES_FW_COLIMANAGER_IMPL_H
#define CLASSES_FW_COLIMANAGER_IMPL_H

#include "classes/fw/ColiManager.h"
#include "classes/fw/ColiObject.h"
#include "classes/fw/PointerMap.h"
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
    // a contact between two objects (addContactList fills it): 0x40 bytes, two Vec3s at 0 and 0x20 (copied
    // component by component), the word at 0x38 its constructor zeroes; the meaning of the fields is not known yet
    class ContactParam {
    public:
        ContactParam() : pad_38(0) {}
        mm::Vec3 pad_0;
        unsigned int pad_10;
        unsigned char pad_14[0xC];
        mm::Vec3 pad_20;
        unsigned int pad_30;
        unsigned int pad_34;
        unsigned int pad_38;
        unsigned char pad_3c[0x4];
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
