#ifndef GF_MSGPCGETELVLIFT_H
#define GF_MSGPCGETELVLIFT_H

#include "fw/Message.h"
#include "mm/mtl/FixedVector.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {

// message 0x1000027 (name from 1.0.0's GfComBehaviorGmk::procMsgPcGetElvLift): asks an elevator gimmick for its
// lifts' objects and whether the asking object is on its switch (the field names are not the original's)
class MsgPcGetElvLift : public ::fw::Message {
public:
    mm::mtl::FixedVector<gf::GF_OBJ_HANDLE*, 16> m_lifts;  // the lift objects found
    bool m_isLiftSwitch;
};

}  // namespace gf

#endif
