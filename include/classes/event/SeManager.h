#ifndef CLASSES_EVENT_SEMANAGER_H
#define CLASSES_EVENT_SEMANAGER_H

#include "event/CvType.h"
#include "classes/event/SeObj.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D428; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::SeManager>
class SeManager : public IManager, public mm::mtl::Singleton<SeManager> {
public:
    virtual ~SeManager();  // slot 0
    SeManager();  // out of line (Singleton<SeManager>::getPtr calls it)
    // called by the evt_setup script plugin (application/BF2/ScriptPlayText); a result its callers ignore is declared void
    void load(const char* name);
    void play(int id, const char* name, float p0, float p1, float p2, float volume);
    void changeVolume(int id, float volume, float frame);
    void pan(int id, float pan, float frame, CV_TYPE type);
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2

    unsigned char pad_10[0x4];
    // load counts the sounds it asked GfGameEvent to create; the name is not the original's
    int m_loadCount;  // 0x14
    // the sound slots play/changeVolume/pan address by id; the name is not the original's
    // (the destructor calls FixedArray<SeObj, 32>'s out-of-line destructor)
    mm::mtl::FixedArray<SeObj, 32> m_objs;  // 0x18
    // play appends the slot it started unless it is already here; the name is not the original's
    mm::mtl::FixedVector<SeObj*, 32> m_playObjs;  // 0x5318 (count at 0x5418)
};
}  // namespace event

#endif
