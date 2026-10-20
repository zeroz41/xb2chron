#ifndef CLASSES_GF_LOCATORTALK_DUMMYGROUP_H
#define CLASSES_GF_LOCATORTALK_DUMMYGROUP_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51BC8
class LocatorTalk_DummyGroup : public ::gf::AFieldLocator {
public:
    virtual ~LocatorTalk_DummyGroup();  // slot 0
    virtual void getPosNum() const;  // slot 3
    virtual void getPos(unsigned int) const;  // slot 4
    virtual void update();  // slot 6
};
}  // namespace gf

#endif
