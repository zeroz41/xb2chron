#ifndef CLASSES_GF_GFPLAYCOMAFTEREVENTSCRIPT_H
#define CLASSES_GF_GFPLAYCOMAFTEREVENTSCRIPT_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57888
class GfPlayComAfterEventScript {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComAfterEventScript();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void vf4();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
