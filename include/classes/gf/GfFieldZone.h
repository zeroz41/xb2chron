#ifndef CLASSES_GF_GFFIELDZONE_H
#define CLASSES_GF_GFFIELDZONE_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedQueue.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfFieldZone; }
namespace gf { class GfSetupParam; }
namespace gf { class IEventZone; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum GEV : int; }

namespace gf {
// table 0x7100B527B0
class GfFieldZone : public ::mm::mtl::PtrSingleton< ::gf::GfFieldZone> {
public:
    GfFieldZone(const GfSetupParam& param) : m_initialized(false) {
        initialize(param);
    }
    virtual ~GfFieldZone();  // slot 0
    void initialize(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    void finalize();
    static void update(const fw::UpdateInfo& info);  // static: GfFieldManager::update passes only the info
    static void addEvent(IEventZone* event);
    static void removeEvent(IEventZone* event);
    void gevMapjump(GEV gev, const MapjumpCallbackInfo& info);

    mm::mtl::FixedQueue<IEventZone*, 16> m_events;  // addEvent and removeEvent: the zone event listeners
    bool m_initialized;  // set once the zone's SE and script singletons are built, cleared by finalize
};
}  // namespace gf

#endif
