#ifndef CLASSES_GF_LOCATORGIMMICK_H
#define CLASSES_GF_LOCATORGIMMICK_H

#include "classes/gf/AFieldLocator.h"

namespace gf {
// table 0x7100B51D98
class LocatorGimmick : public ::gf::AFieldLocator {
public:
    virtual ~LocatorGimmick() {  // slot 0
        reset();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_posNum;
    }
    virtual const mm::Vec3* getPos(unsigned int) const {  // slot 4
        return &m_pos;
    }
    virtual void update();  // slot 6
    // the name is not the original's
    void reset() {
        m_posNum = 0;
        m_gmkId = 0;
        m_gmkType = 0x41;
    }

    int m_gmkType;  // a gmk::GmkType; 0x41 when cleared
    unsigned short m_gmkId;
    unsigned char m_posNum;
    mm::Vec3 m_pos;
};
}  // namespace gf

#endif
