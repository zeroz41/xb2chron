#ifndef CLASSES_FW_UPDATABLEOBJECT_H
#define CLASSES_FW_UPDATABLEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ComponentObject.h"
namespace fw { class ObjectEvent; }
namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B425F0
class UpdatableObject {
public:
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
        T* result = static_cast<T*>(component);
        if (component != nullptr && !component->getRTTI()->isKindOf(&T::m_rtti)) {
            result = nullptr;
        }
        return result;
    }

    // the same for a slot known to hold a component (inline: the name is not the original's)
    template <typename T>
    T* findComponent(unsigned int slot) const {
        fw::ComponentObject* component = m_components[slot];
        return component->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T*>(component) : nullptr;
    }

    static mm::mtl::RTTI m_rtti;
    unsigned char pad_8[0x30];
    fw::ComponentObject* m_components[16];  // by kind: registComponentLocal sets one, the constructor clears them
    unsigned char pad_b8[0x28];  // fields: size from its derived classes
};
}  // namespace fw

#endif
