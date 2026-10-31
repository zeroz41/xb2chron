#ifndef CLASSES_UI_UIOBJFACTORY_H
#define CLASSES_UI_UIOBJFACTORY_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "mm/mtl/Vector.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIBuildInfo; }
namespace ui { class UIGroup; }
namespace ui { class UIResource; }
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
        unsigned short m_count;    // the build information's kind: 0 a BDAT table (UIBuildInfoBdat), 1 a UIO file
                                   // (UIBuildInfoUIO), as registPreloadResource's type; 1 for a layer's sheet
        UIGroup* m_target;         // the group of m_group
        const char* m_name;        // the sheet's object name
    };

    // a root object order waits in m_orders (1.0.0's createRootObject takes one; 0x30 bytes, the field names are not
    // the original's): order fills it from an OrderParam, update loads its resource and builds it
    struct OrderInfo {
        unsigned char m_group;     // OrderParam's
        unsigned char m_priority;  // OrderParam's
        unsigned short m_layer;    // OrderParam's
        UIGroup* m_target;         // OrderParam's; createRootObject registers the object there
        const char* m_name;        // OrderParam's, or the preloaded resource's name
        UIBuildInfo* m_info;       // the order's own (new'd), or a preloaded entry's
        UIResource* m_resource;    // update's (referenced), or a preloaded entry's
        bool m_preloaded;          // m_info and m_resource are a preloaded entry's: update leaves them alone
    };
    // a resource registPreloadResource asked for (0x10 bytes; the names are not the original's)
    struct PreloadInfo {
        UIBuildInfo* m_info;     // new'd by registPreloadResource
        UIResource* m_resource;  // made and referenced by update once m_info is ready
    };

    UIObjFactory();
    virtual ~UIObjFactory();  // slot 0
    void update(const fw::UpdateInfo& info);
    void createRootObject(OrderInfo& info);
    void registPreloadResource(unsigned int type, const char* name);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's registPreloadResource is
    // followed by releasePreloadResource(const char*), which takes a name). A member because `this` is the
    // factory (UIManager::fn_710068F958 passes PtrSingleton<UIObjFactory>'s instance) and its address follows
    // registPreloadResource in ui_obj_factory's unit. What it does: for every preloaded resource entry (0x10
    // bytes from 0x30, count at 0xB0) deletes the object of its first word and drops a reference of the
    // ref-counted resource of its second ("m_RefCount > 0"), then empties the list.
    void fn_71006757FC();
    void order(const OrderParam& param);
    // the factory's `this` is not used: createRootObject leaves x0 unset before the calls
    void setupChildObject(unsigned int handle, const OrderInfo& info);
    void setupObjectInput(unsigned int handle, const OrderInfo& info);
    bool isLoading() const;

    // 0xB8 bytes in all (UIManager's constructor allocates so); the names are not the original's
    mm::mtl::Vector<OrderInfo> m_orders;              // order's, in order; the program allocator's
    mm::mtl::FixedVector<PreloadInfo, 8> m_preloads;  // registPreloadResource's
};
}  // namespace ui

#endif
