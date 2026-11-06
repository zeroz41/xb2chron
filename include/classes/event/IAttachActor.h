#ifndef CLASSES_EVENT_IATTACHACTOR_H
#define CLASSES_EVENT_IATTACHACTOR_H

namespace mm { class Vec3; }
enum EVT_attachtype : int;

namespace event {
// table none (its derived classes'): AttachActorBase's table holds IAttachActor's destructor in slot 0, and
// ObjectEffect::setMount takes an IAttachActor* that ScriptEffectMount::doit passes a CharaObj's AttachActorBase as
class IAttachActor {
public:
    virtual ~IAttachActor() {}  // slot 0
    // slots 2..4 as AttachActorBase declares them (EffectCtrl::kill, setCaster and setMount call slots 3 and 4
    // through an IAttachActor*)
    virtual const char* getName() const = 0;  // slot 2
    virtual void setEffectCaster(bool, unsigned int) = 0;  // slot 3
    virtual void setEffectMount(bool, unsigned int, char const*, mm::Vec3 const&, bool, EVT_attachtype) = 0;  // slot 4
};
}  // namespace event

#endif
