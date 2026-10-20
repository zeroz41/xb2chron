#ifndef CLASSES_GF_GFPLAYCOMMAPJUMP_H
#define CLASSES_GF_GFPLAYCOMMAPJUMP_H

namespace gf {
// table 0x7100B58480
class GfPlayComMapjump {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComMapjump();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual void vf6();  // slot 6
};
}  // namespace gf

#endif
