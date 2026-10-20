#ifndef CLASSES_GF_GFPLAYCOMEVENTFADE_H
#define CLASSES_GF_GFPLAYCOMEVENTFADE_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58318
class GfPlayComEventFade {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComEventFade();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void vf4();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
