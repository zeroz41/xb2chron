#ifndef CLASSES_FW_UPDATABLEOBJECT_H
#define CLASSES_FW_UPDATABLEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "mm/mtl/IntrusiveList.h"
#include "classes/fw/ComponentObject.h"
namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }
#include "fw/HandlePtr.h"

namespace fw {
// table 0x7100B425F0; it is an element of its parent's list of children (the links at 8: its destructor and
// removeChild unlink a child through the null-checked conversion to them)
class UpdatableObject : public ::mm::mtl::IntrusiveListNodeBase {
public:
    // type is m_type; the handle and the last argument are kept at 0x18-0x2C
    UpdatableObject(unsigned int type, const fw::HandlePtr<fw::UpdatableObject>& handle, unsigned int arg);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~UpdatableObject();  // slot 1
    virtual void initialize();  // slot 3
    virtual void update(fw::UpdateInfo const&) = 0;  // slot 4
    virtual void onEvent(fw::ObjectEvent const&);  // slot 5
    // the component in a slot as a T, none when the slot holds another kind (inline: the name is not the
    // original's)
    template <typename T>
    T* getComponent(unsigned int slot) const {
        fw::ComponentObject* component = m_components[slot];
        if (component == nullptr) {
            return nullptr;
        }
        return component->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(component) : nullptr;
    }

    // the same for a slot known to hold a component (inline: the name is not the original's)
    template <typename T>
    T* findComponent(unsigned int slot) const {
        fw::ComponentObject* component = m_components[slot];
        return component->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(component) : nullptr;
    }

    // set once the object is to be deleted: UpdatableGroup's update and execEvent skip it, its tail deletes it
    bool isTerminate() const;
    void setTerminate();
    // child linked last in this object's children, this object its parent (intrusive_list.h asserts `ptr`)
    void addChild(UpdatableObject* child);
    // child unlinked from this object's children, its parent cleared
    void removeChild(UpdatableObject* child);
    // the component in a slot, its owner this object
    void registComponentLocal(unsigned int slot, fw::ComponentObject* component);
    // the component in a slot deleted, the slot cleared
    void removeComponentLocal(unsigned int slot);
    static mm::mtl::RTTI m_rtti;
    // the constructor's handle: UpdatableGroup hands its index back to its map once it deletes the object (the
    // name is not the original's)
    fw::HandlePtr<fw::UpdatableObject> m_handle;
    // its kind, the constructor's first argument (GfObj::getTypeName names a GfObj's; 5 an enemy's, by
    // GfGameInsideBattleLock::isInsideBattleLock; the name is not the original's)
    unsigned int m_type;
    // the constructor's last argument: a bit UpdatableGroup::update and execEvent test against their mask (the
    // name is not the original's)
    unsigned int m_updateBit;
    // bit 0 is isTerminate's (the name is not the original's)
    unsigned short m_flags;
    unsigned char pad_32[0x6];
    fw::ComponentObject* m_components[16];  // by kind: registComponentLocal sets one, the constructor clears them
    // the objects addChild linked (the name is not the original's)
    mm::mtl::IntrusiveList<fw::UpdatableObject> m_children;
    // the handle of the object whose child it is: addChild copies the parent's, removeChild clears it, the
    // destructor unlinks the object from it (the name is not the original's)
    fw::HandlePtr<fw::UpdatableObject> m_parent;
};
}  // namespace fw

#endif
