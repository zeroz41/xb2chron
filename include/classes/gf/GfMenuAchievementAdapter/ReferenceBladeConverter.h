#ifndef CLASSES_GF_GFMENUACHIEVEMENTADAPTER_REFERENCEBLADECONVERTER_H
#define CLASSES_GF_GFMENUACHIEVEMENTADAPTER_REFERENCEBLADECONVERTER_H

#include "classes/gf/GfMenuAchievementAdapter.h"
#include "classes/gf/GfMenuAchievementAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B59C10; the blade GfMenuReference has at a reference index, a fixed line and level
class GfMenuAchievementAdapter::ReferenceBladeConverter : public ::gf::GfMenuAchievementAdapter::IConverter {
public:
    ReferenceBladeConverter(unsigned int reference, unsigned int kizunaLine, unsigned int kizunaLevel)
        : m_reference(reference), m_kizunaLine(kizunaLine), m_kizunaLevel(kizunaLevel) {}
    virtual ~ReferenceBladeConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getBladeId();  // slot 2
    virtual unsigned int getKizunaLine();  // slot 3
    virtual unsigned int getKizunaLevel();  // slot 4
    unsigned int m_reference;  // GfMenuReference::getReferenceBladeID's index
    unsigned int m_kizunaLine;
    unsigned int m_kizunaLevel;
};
}  // namespace gf

#endif
