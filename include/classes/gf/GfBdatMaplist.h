#ifndef CLASSES_GF_GFBDATMAPLIST_H
#define CLASSES_GF_GFBDATMAPLIST_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatMaplist; }

namespace gf {
// table 0x7100B47070; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatMaplist : public ::mm::mtl::PtrSingleton< ::gf::GfBdatMaplist>, public ::gf::IDataBdat {
public:
    GfBdatMaplist();
    virtual ~GfBdatMaplist();  // slot 0
    virtual void bdatRefresh();  // slot 2
    unsigned int getMaplistStart() const;
    unsigned int getMaplistEnd() const;
    const char* getMaplistresource(unsigned int map) const;
    // a map's weather of a type (its w_type columns)
    int getMaplistw_type(unsigned int mapId, unsigned int type) const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    CBdatWrapper* m_fpMaplist;  // 0x10
    unsigned char pad_18[0x10];
};
}  // namespace gf

#endif
