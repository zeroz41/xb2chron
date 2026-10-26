#ifndef CLASSES_UI_UIOBJFACTORY_H
#define CLASSES_UI_UIOBJFACTORY_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIGroup; }
namespace ui { class UIObjFactory; }

namespace ui {
// table 0x7100B748B0
class UIObjFactory : public ::mm::mtl::PtrSingleton< ::ui::UIObjFactory> {
public:
    // a root object to build (1.0.0's order takes one; 0x18 bytes). UIManager's layer creation fills it from a
    // layer row's sheet; the field names are not the original's
    struct OrderParam {
        unsigned char m_group;     // the UIManager group the object goes to
        unsigned char m_priority;  // the sheet's "prio%02d" less 1
        unsigned short m_layer;    // the layer id
        unsigned short m_count;    // 1 for a layer's sheet
        UIGroup* m_target;         // the group of m_group
        const char* m_name;        // the sheet's object name
    };

    UIObjFactory();
    virtual ~UIObjFactory();  // slot 0
    void update(const fw::UpdateInfo& info);
    void registPreloadResource(unsigned int type, const char* name);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's registPreloadResource is
    // followed by releasePreloadResource(const char*), which takes a name). A member because `this` is the
    // factory (UIManager::fn_710068F958 passes PtrSingleton<UIObjFactory>'s instance) and its address follows
    // registPreloadResource in ui_obj_factory's unit. What it does: for every preloaded resource entry (0x10
    // bytes from 0x30, count at 0xB0) deletes the object of its first word and drops a reference of the
    // ref-counted resource of its second ("m_RefCount > 0"), then empties the list.
    void fn_71006757FC();
    void order(const OrderParam& param);
    bool isLoading() const;

    unsigned char pad_08[0xB0];  // 0xB8 bytes in all (UIManager's constructor allocates so)
};
}  // namespace ui

#endif
