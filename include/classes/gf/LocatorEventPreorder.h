#ifndef CLASSES_GF_LOCATOREVENTPREORDER_H
#define CLASSES_GF_LOCATOREVENTPREORDER_H

#include "classes/gf/AFieldLocator.h"
#include "classes/gmk/GmkAcc.h"

namespace gf {
// table 0x7100B51D08
class LocatorEventPreorder : public ::gf::AFieldLocator {
public:
    virtual ~LocatorEventPreorder() {  // slot 0
        reset();
    }
    virtual unsigned int getPosNum() const {  // slot 3
        return m_acc.isValid() ? m_posNum : 0;
    }
    virtual const mm::Vec3* getPos(unsigned int) const {  // slot 4
        return &m_pos;
    }
    virtual void update();  // slot 6
    // the name is not the original's
    void reset() {
        m_posNum = 0;
        m_eventId = 0;
    }

    unsigned short m_eventId;  // the event gimmick's id; the name is not the original's
    gmk::GmkAcc m_acc;
    unsigned char m_posNum;
    mm::Vec3 m_pos;
};
}  // namespace gf

#endif
