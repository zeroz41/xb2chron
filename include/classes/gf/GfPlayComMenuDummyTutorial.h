#ifndef CLASSES_GF_GFPLAYCOMMENUDUMMYTUTORIAL_H
#define CLASSES_GF_GFPLAYCOMMENUDUMMYTUTORIAL_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57C90
class GfPlayComMenuDummyTutorial {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComMenuDummyTutorial();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
