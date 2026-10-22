#include "mm/mtl/FixedQueue.h"
#include "classes/ml/WorkControl.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedVector.h"

namespace ml {

namespace _wkcnt {

// a pause request WorkControl::pause(bool, const char*) queues: FixedQueue<PAUSEQ, 16>::pop_front copies the
// flag at 0 and the 16-character name at 4
struct PAUSEQ {
    bool m_pause;
    mm::mtl::FixStr<16> m_name;
};

mm::mtl::FixedQueue<PAUSEQ, 16> s_quePause;
mm::mtl::FixedQueue<PAUSEQ, 16> s_quePauseS;

}  // namespace _wkcnt

namespace _wroot {

mm::mtl::FixedVector<mm::mtl::FixStr<128>, 16> s_aArgParam;

}  // namespace _wroot

void WorkControl::wkTail() {}

}  // namespace ml
