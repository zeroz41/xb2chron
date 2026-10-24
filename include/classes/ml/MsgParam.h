#ifndef CLASSES_ML_MSGPARAM_H
#define CLASSES_ML_MSGPARAM_H

#include "mm/mtl/FixedQueue.h"

namespace ml {
// a template: 2 instances in the module. A queue of up to T0 messages (ml::WorkObj keeps a MsgParam<8> of its
// events at 0xA8, the queue at 0xB0 and its count at 0x170)
template <int T0>
class MsgParam {
public:
    virtual ~MsgParam() {}  // slot 0

    // one queued message: its kind first (WorkObj's EVT), then its argument (the names are not the original's)
    struct Msg {
        int m_kind;
        unsigned char pad_4[0x14];
    };
    mm::mtl::FixedQueue<Msg, T0> m_queue;
};
}  // namespace ml

#endif
