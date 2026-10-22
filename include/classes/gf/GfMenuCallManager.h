#ifndef CLASSES_GF_GFMENUCALLMANAGER_H
#define CLASSES_GF_GFMENUCALLMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfMenuStrLinker.h"
#include "mm/mtl/FixedVector.h"
#include "string.h"

namespace fw { class UpdateInfo; }
namespace gf { class GfMenuCallContext; }
namespace gf { class GfMenuCallManager; }
namespace gf { class GfSetupParam; }
namespace ui { struct EventData; }
namespace ui { class UIStr; }

namespace gf {
// table 0x7100B5E418; the UI object handles menus attach under an id, the call contexts running on them, and the
// texts menu events pass by id
class GfMenuCallManager : public ::mm::mtl::PtrSingleton< ::gf::GfMenuCallManager> {
public:
    // a running call context (0x10 bytes); the names are not the original's
    struct CallInfo {
        GfMenuCallContext* m_context;  // startCallContext adds a reference to it, its end releases it
        unsigned int m_eventHandler;  // setCallContextEventHandler's: the handle told of the context's results and end
    };

    // build constructs it (1.0.0 has GfMenuCallManager(const GfSetupParam&) out of line; 3.0.1 has no copy)
    GfMenuCallManager(const GfSetupParam& param) : m_handles(), m_strLinker(getAllocator(ALLOCATOR(0))) {
        reset();
    }
    virtual ~GfMenuCallManager();  // slot 0
    // 1.0.0's symbol; 3.0.1 has no copy
    void reset() {
        memset(m_handles, 0, sizeof(m_handles));
    }
    bool canCall(unsigned int id) const;
    static void build(const GfSetupParam& param);
    static void destroy();
    static bool isInitialized();
    static void postUpdate(const fw::UpdateInfo& info);
    static void reciveUIEvent(const ui::EventData& event, unsigned int handle);
    void attachCall(unsigned int id, unsigned int handle);
    void detachCall(unsigned int id);
    unsigned int getAttachedObject(unsigned int id);
    unsigned short registString(const ui::UIStr& text);
    void releaseString(unsigned short id);
    const ui::UIStr& getString(unsigned short id);
    void startCallContext(GfMenuCallContext* context, unsigned int id, unsigned int handle);
    void nextCallContext(GfMenuCallContext* context, unsigned int id);
    void setCallContextEventHandler(GfMenuCallContext* context, unsigned int handle);

    unsigned int m_handles[0x91];  // attachCall's, by id (0 for none); the name is not the original's
    GfMenuStrLinker m_strLinker;  // registString's texts; the name is not the original's
    mm::mtl::FixedVector<CallInfo, 256> m_calls;  // startCallContext's; the name is not the original's
};
}  // namespace gf

#endif
