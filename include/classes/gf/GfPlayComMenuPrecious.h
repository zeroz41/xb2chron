#ifndef CLASSES_GF_GFPLAYCOMMENUPRECIOUS_H
#define CLASSES_GF_GFPLAYCOMMENUPRECIOUS_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57CD8
class GfPlayComMenuPrecious {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComMenuPrecious();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void vf4();  // slot 4
    virtual void vf5();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
