#ifndef CLASSES_GF_GFMENUFIELDSKILLADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUFIELDSKILLADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuFieldSkillAdapter.h"
#include "classes/gf/GfMenuFieldSkillAdapter/IConverter.h"
#include "classes/gf/GfMenuFieldSkillList.h"

namespace gf {
// table 0x7100B5BDC0; the skill a GfMenuFieldSkillList has at an index of the page shown
class GfMenuFieldSkillAdapter::ListConverter : public ::gf::GfMenuFieldSkillAdapter::IConverter {
public:
    ListConverter(GfMenuFieldSkillList* list, int index) : m_list(list), m_index(index) {
        m_list->addRef();
    }
    virtual ~ListConverter();  // slot 0
    virtual void getFieldSkill(MenuFieldSkill& skill);  // slot 2
    GfMenuFieldSkillList* m_list;  // referenced
    int m_index;  // -1 gives nothing
};
}  // namespace gf

#endif
