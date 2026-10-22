#ifndef CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERLINELEVELCONVERTER_H
#define CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERLINELEVELCONVERTER_H

#include "classes/gf/GfMenuSkillAdapter.h"
#include "classes/gf/GfMenuSkillAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5DC00; the driver GfMenuReference has at a reference index, and the line, level and round
// GfMenuReference's numbers at indices hold
class GfMenuSkillAdapter::ReferenceDriverLineLevelConverter : public ::gf::GfMenuSkillAdapter::IConverter {
public:
    ReferenceDriverLineLevelConverter(unsigned int reference, unsigned short kizunaLine, unsigned short kizunaLevel,
                                      unsigned short round)
        : m_reference(reference), m_kizunaLine(kizunaLine), m_kizunaLevel(kizunaLevel), m_round(round) {}
    virtual ~ReferenceDriverLineLevelConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getDriverId() { return GfMenuReference::getReferenceDriverID(m_reference); }  // slot 2
    virtual unsigned int getKizunaLine() { return GfMenuReference::getReferenceNumber(m_kizunaLine); }  // slot 3
    virtual unsigned int getKizunaLevel() { return GfMenuReference::getReferenceNumber(m_kizunaLevel); }  // slot 4
    virtual unsigned int getRound() { return GfMenuReference::getReferenceNumber(m_round); }  // slot 5
    // GfMenuReference indices: the driver's, and the numbers'
    unsigned int m_reference;
    unsigned int m_kizunaLine;
    unsigned int m_kizunaLevel;
    unsigned int m_round;
};
}  // namespace gf

#endif
