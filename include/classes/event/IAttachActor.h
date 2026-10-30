#ifndef CLASSES_EVENT_IATTACHACTOR_H
#define CLASSES_EVENT_IATTACHACTOR_H

namespace event {
// table none (its derived classes'): AttachActorBase's table holds IAttachActor's destructor in slot 0, and
// ObjectEffect::setMount takes an IAttachActor* that ScriptEffectMount::doit passes a CharaObj's AttachActorBase as
class IAttachActor {
public:
    virtual ~IAttachActor() {}  // slot 0
};
}  // namespace event

#endif
