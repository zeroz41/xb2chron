#ifndef CLASSES_EVENT_SEMANAGER_H
#define CLASSES_EVENT_SEMANAGER_H

#include "event/CvType.h"
#include "classes/event/SeObj.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::SeManager no evidence names yet
class TUnk_B3D428 {
public:
    virtual ~TUnk_B3D428();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::SeManager no evidence names yet
class TUnk_B3D450 {
public:
    virtual ~TUnk_B3D450();
};
// table 0x7100B3D428; base at 0x0 unknown (TUnk_B3D428), base at 0x8 unknown (TUnk_B3D450)
class SeManager : public TUnk_B3D428, public TUnk_B3D450 {
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
    SeObj m_objs[32];  // 0x18
    // more fields follow at 0x5318 (the constructor's); not known yet
};
}  // namespace event

#endif
