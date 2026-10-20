#ifndef CLASSES_GF_GFPLAYCOMEVENTPLAYERSTOP_H
#define CLASSES_GF_GFPLAYCOMEVENTPLAYERSTOP_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B577F8
class GfPlayComEventPlayerStop {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComEventPlayerStop();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void vf4();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
