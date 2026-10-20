#ifndef CLASSES_GF_GFPLAYCOMGMKCAMERASEQ_H
#define CLASSES_GF_GFPLAYCOMGMKCAMERASEQ_H

namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B57F78
class GfPlayComGmkCameraSeq {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComGmkCameraSeq();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
