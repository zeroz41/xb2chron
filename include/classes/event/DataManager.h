#ifndef CLASSES_EVENT_DATAMANAGER_H
#define CLASSES_EVENT_DATAMANAGER_H

#include "mm/Vec3.h"

namespace event { enum MSG_TYPE : int; }

#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event {
// table 0x7100B3E2B0; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::DataManager>
class DataManager : public IManager, public mm::mtl::Singleton<DataManager> {
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

    // the 0x170-byte scene 1.0.0's createScene news; the name is not the original's
    struct Scene {
        unsigned char pad_0[0x170];
    };
    unsigned int m_flags;  // 0x10; the name is not the original's
    unsigned int pad_14;
    // the scenes 1.0.0's createScene adds; the name is not the original's
    mm::mtl::FixedVector<Scene*, 16> m_scenes;  // 0x18 (size 0x98)
    // the scene updateCurrent makes current ("default" at first, as ObjectManager's); the name is not the original's
    mm::mtl::FixStr<64> m_sceneName;  // 0xa0
    mm::mtl::FixStr<64> m_currentName;  // 0xe4; the name is not the original's
    Scene* m_current;  // 0x128; the name is not the original's
    unsigned char pad_130[0x50];
};
}  // namespace event

#endif
