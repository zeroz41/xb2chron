#ifndef CLASSES_GF_GFBDATBTL_H
#define CLASSES_GF_GFBDATBTL_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatBtl; }

namespace gf {
// table 0x7100B462F8; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatBtl : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBtl>, public ::gf::IDataBdat {
public:
    GfBdatBtl();
    virtual ~GfBdatBtl();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    unsigned int getArtsDrStart() const;
    unsigned int getArtsDrEnd() const;
    unsigned int getArtsBlStart() const;
    unsigned int getArtsBlEnd() const;
    unsigned int getArtsBlSpStart() const;
    unsigned int getArtsBlSpEnd() const;
    unsigned int getGrowStart() const;
    unsigned int getGrowEnd() const;
    unsigned int getBTL_ClassStart() const;
    unsigned int getBTL_ClassEnd() const;
    unsigned int getBTL_Skill_BlStart() const;
    unsigned int getBTL_Skill_BlEnd() const;
    unsigned int getBTL_Bl_PersonalityStart() const;
    unsigned int getBTL_Bl_PersonalityEnd() const;
    unsigned int getVo_Field_FilterStart() const;
    unsigned int getVo_Field_FilterEnd() const;
    // Table wrappers exposed by the range queries; names follow their accessors.
    CBdatWrapper* m_fpArtsDr;  // 0x10
    CBdatWrapper* m_fpArtsBl;  // 0x18
    CBdatWrapper* m_fpArtsBlSp;  // 0x20
    CBdatWrapper* m_fpGrow;  // 0x28
    unsigned char pad_30[0x10];
    CBdatWrapper* m_fpBTL_Class;  // 0x40
    unsigned char pad_48[0x10];
    CBdatWrapper* m_fpBTL_Skill_Bl;  // 0x58
    unsigned char pad_60[0x10];
    CBdatWrapper* m_fpBTL_Bl_Personality;  // 0x70
    unsigned char pad_78[0x38];
    CBdatWrapper* m_fpVo_Field_Filter;  // 0xB0
    unsigned char pad_b8[0x30];
};
}  // namespace gf

#endif
