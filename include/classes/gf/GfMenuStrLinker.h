#ifndef CLASSES_GF_GFMENUSTRLINKER_H
#define CLASSES_GF_GFMENUSTRLINKER_H

#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "ui/UIStr.h"

namespace mm { namespace mtl { class IAllocator; }}

namespace gf {
// table 0x7100B5F0F0; 128 texts handed out by index, and up to 8 texts to choose from
class GfMenuStrLinker {
public:
    GfMenuStrLinker(mm::mtl::IAllocator* allocator);
    virtual ~GfMenuStrLinker();  // slot 0
    unsigned short addString(const ui::UIStr& str);
    void delString(unsigned short index);
    ui::UIStr& getString(unsigned short index);
    void addSelectString(const ui::UIStr& str);
    void clearSelectString();

    mm::mtl::IAllocator* m_allocator;  // the constructor's; the name is not the original's
    mm::mtl::FixedArray<ui::UIStr, 128> m_strings;  // addString copies into one; the name is not the original's
    mm::mtl::FixedVector<unsigned int, 128> m_freeIndices;  // what addString takes; the name is not the original's
    mm::mtl::FixedVector<ui::UIStr, 8> m_selectStrings;  // addSelectString's; the name is not the original's
};
}  // namespace gf

#endif
