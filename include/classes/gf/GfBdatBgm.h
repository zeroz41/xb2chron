#ifndef CLASSES_GF_GFBDATBGM_H
#define CLASSES_GF_GFBDATBGM_H

#include "classes/gf/IDataBdat.h"
#include "classes/mm/mtl/PtrSingleton.h"

class CBdatWrapper;
namespace gf { class GfBdatBgm; }

namespace gf {
// table 0x7100B45F90; IDataBdat at 0x8 (GfDataBdat::initialize keeps it in its list)
class GfBdatBgm : public ::mm::mtl::PtrSingleton< ::gf::GfBdatBgm>, public ::gf::IDataBdat {
public:
    GfBdatBgm();
    virtual ~GfBdatBgm();  // slot 0
    virtual void bdatRefresh();  // slot 2
    void destroyFP();
    void createFP();
    unsigned int getBgmListStart() const;
    unsigned int getBgmListEnd() const;
    const char* getBgmListfilename(unsigned int id) const;  // a BGM list row's file name
    unsigned int getBgmConditionStart() const;
    unsigned int getBgmConditionEnd() const;
    unsigned int getBgmConditionConditionA(unsigned int id) const;
    unsigned int getBgmConditionBgmIDA(unsigned int id) const;
    unsigned int getBgmConditionConditionB(unsigned int id) const;
    unsigned int getBgmConditionBgmIDB(unsigned int id) const;
    unsigned int getBgmConditionConditionC(unsigned int id) const;
    unsigned int getBgmConditionBgmIDC(unsigned int id) const;
    unsigned int getBgmConditionConditionD(unsigned int id) const;
    unsigned int getBgmConditionBgmIDD(unsigned int id) const;
    unsigned int getBgmConditionPriority(unsigned int id) const;
    // a condition row's condition and BGM of slot A to D (slot 0 to 3)
    unsigned int getBgmConditionCondition(unsigned int id, unsigned int slot) const;
    unsigned int getBgmConditionBgmID(unsigned int id, unsigned int slot) const;

    // the BGM list and BGM condition tables createFP opens, each held in a block of its own (the names are not the
    // original's)
    CBdatWrapper* m_fpBgmList;
    CBdatWrapper* m_fpBgmCondition;
};
}  // namespace gf

#endif
