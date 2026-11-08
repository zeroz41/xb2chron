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
        // a message of kind with no argument (WinView::attachWorkEvent and wkStandbyLogin push one, clearing the
        // argument's first byte and its type, then set the argument of the last one queued)
        Msg(int kind) : m_kind(kind) {
            m_param[0] = 0;
            m_paramType = 0;
        }
        int m_kind;
        // 0x04 the argument's bytes (WinView::attachWorkEvent stores its IWorkEvent pointer at the start; the name is
        // not the original's)
        unsigned char m_param[0x10];
        // 0x14 what the argument holds: 0 none, 4 a pointer (WinView::attachWorkEvent; the name is not the original's)
        unsigned char m_paramType;
    };
    mm::mtl::FixedQueue<Msg, T0> m_queue;
};
}  // namespace ml

#endif
