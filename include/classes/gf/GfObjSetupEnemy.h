#ifndef CLASSES_GF_GFOBJSETUPENEMY_H
#define CLASSES_GF_GFOBJSETUPENEMY_H

namespace gf {
// table 0x7100B6A448
class GfObjSetupEnemy {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfObjSetupEnemy();  // slot 1
    virtual void getFootStep() const;  // slot 3
    virtual void getFootStepEffect() const;  // slot 4
    virtual void getEnArrangeID() const;  // slot 5
};
}  // namespace gf

#endif
