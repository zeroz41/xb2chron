#ifndef CLASSES_UI_UIOBJECTBASE_H
#define CLASSES_UI_UIOBJECTBASE_H

#include "classes/ui/UIDisplayInfo.h"
#include "classes/ui/UITransform.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/IntrusiveList.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/Bitflag.h"

namespace ui {
// table 0x7100B75738; a reference object (UIPolygonObject::duplicateImpl holds a reference to its copy while its
// parent adds it) and an element of its layout's UIObjectList (the node at 0x10: the constructor links it to itself,
// UIObjectList::regist links it in)
class UIObjectBase : public ::mm::mtl::ReferenceObject, public ::mm::mtl::IntrusiveListNodeBase {
public:
    UIObjectBase(const mm::mtl::FixStr<32>& name);
    virtual ~UIObjectBase();  // slot 0
    virtual void update();  // slot 2
    virtual void setInitialize();  // slot 3
    virtual void setTerm();  // slot 4
    void setSuspend(bool suspend);
    UITransform m_transform;  // the constructor builds it; UIObject::importTransform fills it from the layer
                              // (0x30 bytes: 16-aligned for its scale)
    UIDisplayInfo m_displayInfo;  // what UIObject::importDisplayInfo fills from the object's layer
    // bit 3: terminated (UIObjectAcc::isTerm reads it). A Bitflag: searchDuplicate loads it apart from
    // m_duplicateIndex (a raw int load is widened over both by GVN)
    ::mm::mtl::Bitflag<32> m_flags;
    unsigned short m_duplicateIndex;  // UIObjectAcc::getDuplicateIndex
    unsigned char pad_9E[0x2];
    mm::mtl::FixStr<32> m_name;  // UILayoutObject::addChild registers the child under it
    unsigned char pad_C4[0x4];
};
}  // namespace ui

#endif
