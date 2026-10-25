#ifndef CLASSES_EVENT_VOLUMEMANAGER_H
#define CLASSES_EVENT_VOLUMEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::VolumeManager no evidence names yet
class TUnk_B3D930 {
public:
    virtual ~TUnk_B3D930();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::VolumeManager no evidence names yet
class TUnk_B3D958 {
public:
    virtual ~TUnk_B3D958();
};
// table 0x7100B3D930; base at 0x0 unknown (TUnk_B3D930), base at 0x8 unknown (TUnk_B3D958)
class VolumeManager : public TUnk_B3D930, public TUnk_B3D958 {
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
