#ifndef CLASSES_EVENT_SEAMLESSMANAGER_H
#define CLASSES_EVENT_SEAMLESSMANAGER_H

#include "classes/event/PosAxis.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::SeamlessManager no evidence names yet
class TUnk_B3D470 {
public:
    virtual ~TUnk_B3D470();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::SeamlessManager no evidence names yet
class TUnk_B3D498 {
public:
    virtual ~TUnk_B3D498();
};
// table 0x7100B3D470; base at 0x0 unknown (TUnk_B3D470), base at 0x8 unknown (TUnk_B3D498)
class SeamlessManager : public TUnk_B3D470, public TUnk_B3D498 {
public:
    virtual ~SeamlessManager();  // slot 0
    SeamlessManager();  // out of line (Singleton<SeamlessManager>::getPtr calls it)
    void addFirstSeamPoint(const char* name, const PosAxis& pos);
    void addSeamPoint(float frame, const PosAxis& pos);  // the parameter name is not the original's
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
