#ifndef CLASSES_FW_MODELMANAGER_H
#define CLASSES_FW_MODELMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/mm/mtl/ReferenceObject.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; }

namespace fw {
// table 0x7100B421F8; the base at 0x10 is mm::mtl::PtrSingleton<fw::ModelManager> (the destructor stores its table
// there and clears its instance)
class ModelManager : public ::fw::ManagerObject, public ::mm::mtl::PtrSingleton< ::fw::ModelManager> {
public:
    // what a group lists: ModelObject and VisibleObject, counted, linked at 0x10, updated through slot 2 (its table
    // is not in the module; the name is not the original's)
    class Element : public ::mm::mtl::ReferenceObject, public ::mm::mtl::IntrusiveListNodeBase {
    public:
        virtual void update() = 0;  // slot 2
    };
    // the objects of one layer (1.0.0 names mm::mtl::FixedArray<fw::ModelManager::Group, 32>)
    class Group : public ::mm::mtl::IntrusiveList<Element> {
    public:
        // obj linked last unless it is listed already (ModelObject's and VisibleObject's create and changeLayer
        // inline it; the name is not the original's). Linked by reference: the original has no `ptr` assertion and
        // no null-checked node cast there
        void add(Element* obj) {
            iterator it = find(begin(), end(), obj);
            if (end() == it) {
                push_back(*obj);
            }
        }
        // first's element obj, last when it is not between them (add inlines it: the search's own returns and the
        // `end() == it` test keep the original's loop exits; the name is not the original's)
        static iterator find(iterator first, iterator last, Element* obj) {
            for (; first != last; ++first) {
                if (first.m_node == obj) {
                    return first;
                }
            }
            return last;
        }
    };
    virtual ~ModelManager();  // slot 0
    virtual void update(fw::UpdateInfo const&, unsigned int);  // slot 8
    mm::mtl::FixedArray<Group, 32> m_groups;  // by layer; update updates the layers whose bits it is given
};
}  // namespace fw

#endif
