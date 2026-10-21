#ifndef CLASSES_GF_GFPLAYCOMGIMMICKTASKCOMPLETE_H
#define CLASSES_GF_GFPLAYCOMGIMMICKTASKCOMPLETE_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B580B8
class GfPlayComGimmickTaskComplete {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComGimmickTaskComplete();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start() {}  // slot 4
    virtual void end() {}  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
