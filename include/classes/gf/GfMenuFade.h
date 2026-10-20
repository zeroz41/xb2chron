#ifndef CLASSES_GF_GFMENUFADE_H
#define CLASSES_GF_GFMENUFADE_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace mm { struct Col4; }
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5E548; its destructor is its singleton's
class GfMenuFade : public ::mm::mtl::PtrSingleton<GfMenuFade> {
public:
    virtual ~GfMenuFade();  // slot 0
    static void destroy();
    void finalize();
    static bool isInitialized();
    static void setFade(unsigned int channel, unsigned int time, const mm::Col4& color);
    static void getFadeColor(unsigned int channel, mm::Col4& color);
    static void setLoading(unsigned int id, bool disp);
    static bool isFading(unsigned int channel);
    static void reciveEvent(const ui::EventData& event, unsigned int handle);
    bool m_initialized;  // set once its UI layer reports ready (event 5), cleared by finalize
    bool m_fading[3];    // per channel: set by setFade and a fade's start, cleared by its end
};
}  // namespace gf

#endif
