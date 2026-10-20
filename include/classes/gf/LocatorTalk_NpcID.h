#ifndef CLASSES_GF_LOCATORTALK_NPCID_H
#define CLASSES_GF_LOCATORTALK_NPCID_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51B80
class LocatorTalk_NpcID : public ::gf::AFieldLocator {
public:
    virtual ~LocatorTalk_NpcID();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
};
}  // namespace gf

#endif
