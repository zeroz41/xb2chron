#ifndef CLASSES_GF_GFMENUTAGTOWNFLAG_H
#define CLASSES_GF_GFMENUTAGTOWNFLAG_H

#include "classes/ui/UITagConv.h"

namespace mm { namespace mtl { template <typename, typename> class MapPair; }}
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {
// table 0x7100B65438
class GfMenuTagTownFlag : public ::ui::UITagConv {
public:
    virtual ~GfMenuTagTownFlag();  // slot 0
    virtual void getTagName();  // slot 2
    virtual void convBegin(mm::mtl::FixedVector<mm::mtl::MapPair<char const*, char const*>, 8ul> const&, unsigned short);  // slot 3
};
}  // namespace gf

#endif
