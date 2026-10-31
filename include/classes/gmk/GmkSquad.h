#ifndef CLASSES_GMK_GMKSQUAD_H
#define CLASSES_GMK_GMKSQUAD_H

namespace gmk {
// table 0x7100B6CD10
class GmkSquad {
public:
    virtual ~GmkSquad();  // slot 0
    unsigned char pad_8[0x60];
    void* pad_68;
    unsigned int pad_70;  // how many members it has (GmkSquadNavi::getMemberDefType, GfComBehaviorMob::isSquadMember)
};
}  // namespace gmk

#endif
