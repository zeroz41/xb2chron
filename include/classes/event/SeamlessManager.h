#ifndef CLASSES_EVENT_SEAMLESSMANAGER_H
#define CLASSES_EVENT_SEAMLESSMANAGER_H

#include "classes/event/PosAxis.h"
#include "classes/event/IManager.h"
#include "classes/mm/mtl/Singleton.h"

namespace event { enum MSG_TYPE : int; }

namespace event {
// table 0x7100B3D470; base at 0x0 event::IManager, base at 0x8 mm::mtl::Singleton<event::SeamlessManager>
class SeamlessManager : public IManager, public mm::mtl::Singleton<SeamlessManager> {
public:
    virtual ~SeamlessManager();  // slot 0
    SeamlessManager();  // out of line (Singleton<SeamlessManager>::getPtr calls it)
    void addFirstSeamPoint(const char* name, const PosAxis& pos);
    void addSeamPoint(float frame, const PosAxis& pos);  // the parameter name is not the original's
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    // fields the constructor initializes; what they hold is not known yet
    long pad_10;
    unsigned char pad_18[0x508];
    long pad_520;
    unsigned char pad_528[0x2018];
    long pad_2540;
    unsigned char pad_2548[0x18];
};
}  // namespace event

#endif
