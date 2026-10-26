#ifndef CLASSES_EVENT_SHAKERUPDATER_UPDATE_H
#define CLASSES_EVENT_SHAKERUPDATER_UPDATE_H

#include "classes/event/ICmd.h"

namespace event { namespace ShakerUpdater {
// table 0x7100B3F100
class Update : public ::event::ICmd {
public:
    virtual ~Update();  // slot 0
    virtual bool update(event::ICmd::Param const&);  // slot 3
};
}}  // namespace event::ShakerUpdater

#endif
