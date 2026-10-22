#ifndef CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUSKILLADAPTER_REFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuSkillAdapter.h"
#include "classes/gf/GfMenuSkillAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5DBC0; the driver GfMenuReference has at a reference index, a fixed line and level, and the round
// GfMenuReference's number at an index holds
class GfMenuSkillAdapter::ReferenceDriverConverter : public ::gf::GfMenuSkillAdapter::IConverter {
public:
    ReferenceDriverConverter(unsigned int reference, unsigned short kizunaLine, unsigned short kizunaLevel,
                             unsigned short round)
        : m_reference(reference), m_kizunaLine(kizunaLine), m_kizunaLevel(kizunaLevel), m_round(round) {}
    virtual ~ReferenceDriverConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getDriverId() { return GfMenuReference::getReferenceDriverID(m_reference); }  // slot 2
    virtual unsigned int getKizunaLine() { return m_kizunaLine; }  // slot 3
    virtual unsigned int getKizunaLevel() { return m_kizunaLevel; }  // slot 4
    virtual unsigned int getRound() { return GfMenuReference::getReferenceNumber(m_round); }  // slot 5
    unsigned int m_reference;  // GfMenuReference::getReferenceDriverID's index
    unsigned int m_kizunaLine;
    unsigned int m_kizunaLevel;
    unsigned int m_round;  // GfMenuReference::getReferenceNumber's index
};
}  // namespace gf

#endif
