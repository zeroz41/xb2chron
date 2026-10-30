#ifndef CLASSES_EVENT_VOLUMEMANAGER_H
#define CLASSES_EVENT_VOLUMEMANAGER_H
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "classes/event/VolumeSeamless.h"
#include "classes/event/VolumeSkip.h"

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
    void init();    // out of line
    void clear();   // out of line
    void render();  // out of line
    void update();  // OnEventProc's update (inlined; the name is not the original's)
    unsigned int pad_10;  // the constructor zeroes it
    unsigned int pad_14;  // the constructor zeroes it
    unsigned char pad_18[0x38];
    VolumeSeamless m_seamless;  // 0x50 (the name is not the original's)
    VolumeSkip m_skip;          // 0xa0 (the name is not the original's)
    unsigned char pad_e8[0x8];  // sizeof 0xF0 (s_instance)
};
}  // namespace event

#endif
