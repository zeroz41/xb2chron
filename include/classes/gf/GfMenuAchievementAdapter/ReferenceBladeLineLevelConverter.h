#ifndef CLASSES_GF_GFMENUACHIEVEMENTADAPTER_REFERENCEBLADELINELEVELCONVERTER_H
#define CLASSES_GF_GFMENUACHIEVEMENTADAPTER_REFERENCEBLADELINELEVELCONVERTER_H

#include "classes/gf/GfMenuAchievementAdapter.h"
#include "classes/gf/GfMenuAchievementAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B59C48; the blade GfMenuReference has at a reference index, and the line and level
// GfMenuReference's numbers at indices hold
class GfMenuAchievementAdapter::ReferenceBladeLineLevelConverter : public ::gf::GfMenuAchievementAdapter::IConverter {
public:
    ReferenceBladeLineLevelConverter(unsigned int reference, unsigned int kizunaLine, unsigned int kizunaLevel)
        : m_reference(reference), m_kizunaLine(kizunaLine), m_kizunaLevel(kizunaLevel) {}
    virtual ~ReferenceBladeLineLevelConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getBladeId();  // slot 2
    virtual unsigned int getKizunaLine();  // slot 3
    virtual unsigned int getKizunaLevel();  // slot 4
    // GfMenuReference indices: the blade's, and the numbers'
    unsigned int m_reference;
    unsigned int m_kizunaLine;
    unsigned int m_kizunaLevel;
};
}  // namespace gf

#endif
