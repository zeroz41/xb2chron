#ifndef CLASSES_FW_UPDATABLEOBJECT_H
#define CLASSES_FW_UPDATABLEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ComponentObject.h"
namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }
#include "fw/HandlePtr.h"

namespace fw {
// table 0x7100B425F0
class UpdatableObject {
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

    static mm::mtl::RTTI m_rtti;
    unsigned char pad_8[0x20];
    // its kind, the constructor's first argument (GfObj::getTypeName names a GfObj's; 5 an enemy's, by
    // GfGameInsideBattleLock::isInsideBattleLock; the name is not the original's)
    unsigned int m_type;
    unsigned char pad_2c[0xc];
    fw::ComponentObject* m_components[16];  // by kind: registComponentLocal sets one, the constructor clears them
    unsigned char pad_b8[0x28];  // fields: size from its derived classes
};
}  // namespace fw

#endif
