#ifndef CLASSES_EVENT_ENVTRANSFEREVENT_H
#define CLASSES_EVENT_ENVTRANSFEREVENT_H

#include "classes/event/EnvTransfer.h"

namespace event {
// table 0x7100B3C6F0 (weak: EnvManager's constructor emits it)
class EnvTransferEvent : public EnvTransfer {
public:
    EnvTransferEvent() : pad_18(0), pad_1c(0) {}
    virtual ~EnvTransferEvent() {}  // slot 0
    unsigned int pad_18;
    unsigned int pad_1c;
};
}  // namespace event

#endif
