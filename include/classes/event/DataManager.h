#ifndef CLASSES_EVENT_DATAMANAGER_H
#define CLASSES_EVENT_DATAMANAGER_H

#include "mm/Vec3.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::DataManager no evidence names yet
class TUnk_B3E2B0 {
public:
    virtual ~TUnk_B3E2B0();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::DataManager no evidence names yet
class TUnk_B3E2D8 {
public:
    virtual ~TUnk_B3E2D8();
};
// table 0x7100B3E2B0; base at 0x0 unknown (TUnk_B3E2B0), base at 0x8 unknown (TUnk_B3E2D8)
class DataManager : public TUnk_B3E2B0, public TUnk_B3E2D8 {
public:
    virtual ~DataManager();  // slot 0
    DataManager();  // out of line (Singleton<DataManager>::getPtr calls it)
    // named by 1.0.0's symbols (_ZN5event11DataManager12setOffsetSrcERKN2mm4Vec3Efb / setOffsetDes, the evt_setup
    // plugin's offsetSrc/offsetDes call them at the same sites)
    void setOffsetSrc(const mm::Vec3& offset, float angle, bool flag);
    void setOffsetDes(const mm::Vec3& offset, float angle, bool flag);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // whether the target id's values are angles (evt_chara's setTar then converts degrees to radians)
    bool checkRadianTar(unsigned int id);
};
}  // namespace event

#endif
