#ifndef CLASSES_GF_GFBDATLOOKAT_H
#define CLASSES_GF_GFBDATLOOKAT_H

#include "classes/fw/MessageObject.h"
#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/UniquePtr.h"

namespace gf { class GfBdatLookAt; }

namespace gf {
// table 0x7100B46FA8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list). The look-at tables: per
// character category the characters' look types (by RefID), and per look type and character the look parameters,
// rebuilt into an Impl (defined in gf_bdat_lookat.cpp) whenever the BDAT tables are set up again.
class GfBdatLookAt : public ::mm::mtl::PtrSingleton< ::gf::GfBdatLookAt>, public ::gf::IDataBdat, public ::fw::MessageObject {
public:
    // a character's row of its category's table (Vector<GfBdatLookAt::CharactorInfo> names the type; the field
    // names are the table's columns, not the original's): a row no table has reads as type 0, chara 1
    struct CharactorInfo {
        CharactorInfo() : m_lookType(0), m_charaType(1) {}
        unsigned short m_lookType;   // LookType: the first index of the look parameters
        unsigned short m_charaType;  // Chara: the second index (getCharaType returns it)
    };
    // the look parameters of a look type and character, from the three tables 0x1D8..0x1DA (the type and field names
    // are the columns', not the original's; getLookInfo returns these defaults for a pair no table has)
    struct LookInfo {
        LookInfo()
            : m_radius(50.0f), m_upperHeight(5.0f), m_lowerHeight(5.0f), m_lookTime(3.0f), m_interval(5.0f),
              m_priority(0) {}
        float m_radius;
        float m_upperHeight;
        float m_lowerHeight;
        float m_lookTime;
        float m_interval;
        unsigned char m_priority;
    };
    class Impl;

    GfBdatLookAt();
    virtual ~GfBdatLookAt();  // slot 0
    virtual void bdatRefresh();  // slot 2

    // the row of refId in the table of category, the default row when there is none (the parameter names are not
    // the original's)
    const CharactorInfo* getCharactorInfo(unsigned int category, unsigned int refId) const;
    // the look parameters of the first character's look type for the second's chara type; the defaults when
    // targetCategory is 8 or the pair has none (the parameter names are not the original's)
    const LookInfo* getLookInfo(unsigned int category, unsigned int refId, unsigned int targetCategory,
                                unsigned int targetRefId) const;
    // the largest radius / upper / lower height of every look parameter row (the defaults without tables)
    float getMaxRadius();
    float getMaxUpper();
    float getMaxLower();
    unsigned short getCharaType(unsigned int category, unsigned int refId);

    ::mm::mtl::UniquePtr<Impl> m_impl;  // 0x28
};
}  // namespace gf

#endif
