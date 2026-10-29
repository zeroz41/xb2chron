#ifndef CLASSES_EVENT_VOLUMEMANAGER_H
#define CLASSES_EVENT_VOLUMEMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D930; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::VolumeManager>
class VolumeManager : public IManager, public mm::mtl::Singleton<VolumeManager> {
public:
    virtual ~VolumeManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // out of line (mm::mtl::Singleton<event::VolumeManager>::getPtr's static calls it)
    VolumeManager();
    // a sound category (the evt_vol plugin passes 0, 3, 4, 5, 6, 9, 7); no enumerator names are known
    enum CATE {};
    void changeCategoryVolume(CATE cate, float volume, float frame);
    void resetCategoryVolume(CATE cate, float frame);
};
}  // namespace event

#endif
