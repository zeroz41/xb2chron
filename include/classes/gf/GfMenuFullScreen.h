#ifndef CLASSES_GF_GFMENUFULLSCREEN_H
#define CLASSES_GF_GFMENUFULLSCREEN_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfMenuFullScreen; }
namespace gf { namespace GfMenuTypes { struct Param; }}

namespace gf {
// table 0x7100B5E850
class GfMenuFullScreen : public ::mm::mtl::PtrSingleton< ::gf::GfMenuFullScreen> {
public:
    virtual ~GfMenuFullScreen();  // slot 0
    static unsigned int getScreenLayerID(unsigned int screen);  // 0 past the eighth
    static void registLayerParam(unsigned int layer, const GfMenuTypes::Param& param);
};
}  // namespace gf

#endif
