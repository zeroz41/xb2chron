#ifndef CLASSES_EVENT_SHAKERUPDATER_H
#define CLASSES_EVENT_SHAKERUPDATER_H

#include "classes/event/ICmd.h"

namespace event {
// known only as the scope of its Update command (3.0.1 symbols event::ShakerUpdater::Update::~Update and update);
// whether it is a class or a namespace is not known
class ShakerUpdater {
public:
    // table 0x7100B3F100 (slot 0 is ICmd's destructor: Update's own folds to it); Shaker holds one
    class Update : public ::event::ICmd {
    public:
        virtual ~Update() {}  // slot 1 (D0 0x710014B40C)
        virtual int update(event::ICmd::Param const&);  // slot 3 (0x71000FFAE0)
    };
};
}  // namespace event

#endif
