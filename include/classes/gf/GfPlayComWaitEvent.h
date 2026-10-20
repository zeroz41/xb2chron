#ifndef CLASSES_GF_GFPLAYCOMWAITEVENT_H
#define CLASSES_GF_GFPLAYCOMWAITEVENT_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B577B0
class GfPlayComWaitEvent {
public:
    virtual void getRTTI() const;  // slot 0
    virtual void vf1();  // slot 1
    virtual void vf2();  // slot 2
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
