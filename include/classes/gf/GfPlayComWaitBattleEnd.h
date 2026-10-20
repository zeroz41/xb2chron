#ifndef CLASSES_GF_GFPLAYCOMWAITBATTLEEND_H
#define CLASSES_GF_GFPLAYCOMWAITBATTLEEND_H

namespace gf {
// table 0x7100B584C8
class GfPlayComWaitBattleEnd {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComWaitBattleEnd();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void vf4();  // slot 4
    virtual void end();  // slot 5
    virtual void vf6();  // slot 6
};
}  // namespace gf

#endif
