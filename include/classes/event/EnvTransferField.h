#ifndef CLASSES_EVENT_ENVTRANSFERFIELD_H
#define CLASSES_EVENT_ENVTRANSFERFIELD_H

#include "classes/event/EnvTransfer.h"

namespace event {
// table 0x7100B3C710 (weak: EnvManager's constructor emits it)
class EnvTransferField : public EnvTransfer {
public:
    virtual ~EnvTransferField() {}  // slot 0
};
}  // namespace event

#endif
