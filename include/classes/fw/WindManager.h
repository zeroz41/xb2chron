#ifndef CLASSES_FW_WINDMANAGER_H
#define CLASSES_FW_WINDMANAGER_H

#include "classes/fw/ManagerObject.h"
#include "classes/fw/CommonResource.h"
#include "classes/fw/ParamList.h"
#include "classes/fw/WindProbe.h"
#include "classes/fw/WindImpluse.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/wnd/WindWorld.h"
#include "mm/mtl/IntrusivePtr.h"
#include "mm/mtl/IntrusiveList.h"

namespace fw { class UpdateInfo; }
namespace wnd { class ResWind; }

namespace fw {
// table 0x7100B434A0; the constructor installs PtrSingleton's base at 0x10.
class WindManager : public ManagerObject, public mm::mtl::PtrSingleton<WindManager> {
public:
    WindManager();
    virtual ~WindManager();  // slot 0
    virtual bool initialize();  // slot 2
    virtual const char* getName() const;  // slot 5
    virtual void update(const UpdateInfo& info);  // slot 8
    bool setGlobalWind(int index);
    void buildWorld(const wnd::ResWind* resource);
    void destroyWorld();
    static const mm::Vec3& getGlobalWindPower();
    void addProbe(WindProbe* probe);
    void removeProbe(WindProbe* probe);

    // Field names describe their uses; they are not known to be the original's.
    wnd::WindWorld* m_world;  // buildWorld's; destroyWorld releases it
    mm::mtl::IntrusiveList<WindProbe> m_probes;
    mm::mtl::IntrusiveListBase m_auxiliaryList;  // constructed at 0x38; element type not yet known
    mm::mtl::IntrusiveList<WindImpluse> m_impulses;
    CommonResource* m_resource;  // initialize loads /param/wind.prm
    mm::mtl::IntrusivePtr<ParamList> m_params;
    // The destructor proves a counted object at 0x78, but not its derived type.
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_auxiliaryResource;
    unsigned char pad_80[8];
    mm::mtl::IntrusivePtr<WindProbe> m_defaultProbe;
    mm::mtl::IntrusivePtr<WindProbe> m_mainProbe;
};
}  // namespace fw

#endif
