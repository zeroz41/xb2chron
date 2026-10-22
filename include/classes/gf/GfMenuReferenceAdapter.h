#ifndef CLASSES_GF_GFMENUREFERENCEADAPTER_H
#define CLASSES_GF_GFMENUREFERENCEADAPTER_H

#include "classes/gf/GfMenuAdapter.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "mm/mtl/IntrusivePtr.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIObjectPlugin; }

namespace gf {
// table 0x7100B5D8F8; shows a GfMenuReferenceNumber's value in its range
class GfMenuReferenceAdapter : public ::gf::GfMenuAdapter {
public:
    // inline: 1.0.0 has it out of line, 3.0.1 none
    GfMenuReferenceAdapter(ui::UIObjectPlugin* plugin, bool changed)
        : GfMenuAdapter(plugin, false, changed), m_reference(), m_number(0), m_max(0), m_min(0), m_offset(0) {}
    virtual ~GfMenuReferenceAdapter();  // slot 0
    virtual void update(fw::UpdateInfo const&);  // slot 2
    static GfMenuReferenceAdapter* create(unsigned int handle, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> reference,
                                          bool changed);
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> m_reference;
    // what update last showed, and the range it last saw; the names are not the original's
    int m_number;
    int m_max;
    int m_min;
    int m_offset;  // added to the reference's value; the name is not the original's
};
}  // namespace gf

#endif
