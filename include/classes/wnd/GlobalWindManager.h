#ifndef CLASSES_WND_GLOBALWINDMANAGER_H
#define CLASSES_WND_GLOBALWINDMANAGER_H

#include "classes/wnd/ConpoundWind.h"
#include "classes/wnd/GlobalWind.h"
#include "mm/mtl/Vector.h"
#include "wnd/Array.h"

namespace mm { namespace mtl { class IAllocator; }}
namespace wnd { class ResConpoundWind; }

namespace wnd {
// the global winds: a compound wind per resource, and the blender that goes from one to another (WindWorld keeps
// one at 0x10)
class GlobalWindManager {
public:
    GlobalWindManager();
    void setup(const Array<const ResConpoundWind*>& resWind, mm::mtl::IAllocator* allocator);
    bool setCurrentWind(int index);  // false past the winds; -1 for none

    mm::mtl::Vector<ConpoundWind> m_winds;  // setup's, one per resource; the name is not the original's
    const ResConpoundWind* const* m_ppResWinds;  // setup's resources; the name is not the original's
    unsigned int m_resWindNum;  // and their count; the name is not the original's
    GlobalWind m_globalWind;  // the name is not the original's
    int m_currentIndex;  // setCurrentWind's; the name is not the original's
    // 1.0.0's setDebugWind sets it (-1 when off), and setCurrentWind only blends while it is -1; the name is not
    // the original's
    int m_debugIndex;
};
}  // namespace wnd

#endif
