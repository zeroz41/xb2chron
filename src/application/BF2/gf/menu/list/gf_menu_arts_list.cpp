#include "mm/mtl/FixedVector.h"
#include "ui/UIStr.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuStrLinker.h"
#include "classes/gf/GfMenuArtsList.h"
#include "mm/mtl/Vector.h"
#include "classes/gf/GfAllocator.h"

namespace gf {

GfMenuStrLinker::GfMenuStrLinker(mm::mtl::IAllocator* allocator)
    : m_allocator(allocator), m_strings(), m_freeIndices(), m_selectStrings() {
    for (unsigned int i = 0; i < 128; ++i) {
        m_freeIndices.push_back(i);
    }
}

GfMenuStrLinker::~GfMenuStrLinker() {}

void GfMenuStrLinker::delString(unsigned short index) {
    if (index < 128) {
        m_strings[index].release();
        m_freeIndices.push_back(index);
    }
}

void GfMenuStrLinker::addSelectString(const ui::UIStr& str) {
    if (m_selectStrings.size() != m_selectStrings.capacity()) {
        m_selectStrings.push_back(str);
    }
}

void GfMenuStrLinker::clearSelectString() {
    m_selectStrings.clear();
}

GfMenuArtsList::~GfMenuArtsList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuArtsList* GfMenuArtsList::create() {
#line 35
    GfMenuArtsList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuArtsList;
    list->addRef();
    return list;
}

}  // namespace gf
