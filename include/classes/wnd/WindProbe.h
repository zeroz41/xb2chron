#ifndef CLASSES_WND_WINDPROBE_H
#define CLASSES_WND_WINDPROBE_H

#include "classes/wnd/WindBlender.h"
#include "classes/wnd/LocalWind.h"
#include "classes/wnd/WindObject.h"
#include "mm/mtl/Vector.h"

namespace mm { namespace mtl { class IAllocator; }}
namespace wnd { class AreaWind; }
namespace wnd { class GlobalWind; }
namespace wnd { class OverlappingCache; }
namespace wnd { class UpdateInfo; }

namespace wnd {
// what wnd::WindProbe's constructor takes
class ProbeCreateInfo : public WindObjectCreateInfo {
public:
    ProbeCreateInfo() : capacity(0) {}

    unsigned int capacity;  // how many 0x20-byte entries the constructor reserves from its allocator
};

// table 0x7100B81880; a wind object that feels the winds about it
class WindProbe : public WindObject {
public:
    WindProbe(const ProbeCreateInfo& info, unsigned int windIndex, mm::mtl::IAllocator* allocator);
    virtual ~WindProbe();  // slot 0
    void bindGlobalWind(const GlobalWind& wind);
    void unbindGlobalWind();
    void calcGlobalWindPower(const UpdateInfo& info);
    void setAreaWind(const AreaWind* pAreaWind);

    unsigned int m_windIndex;  // the constructor's (fw::WindProbe draws it below twelve: one of a node's winds)
    WindBlender m_blender;  // bindGlobalWind and setAreaWind give it its nodes
    const GlobalWind* m_pGlobalWind;  // bindGlobalWind's
    const AreaWind* m_pAreaWind;  // setAreaWind's
    // the constructor reserves its create-info's capacity from its allocator (the name is not the original's)
    mm::mtl::Vector<LocalWindHitCache> m_hitCaches;
    OverlappingCache* m_pOverlappingCache;  // the destructor asserts it is gone
};
}  // namespace wnd

#endif
