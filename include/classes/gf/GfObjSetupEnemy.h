#ifndef CLASSES_GF_GFOBJSETUPENEMY_H
#define CLASSES_GF_GFOBJSETUPENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
#include "mm/mtl/FixStr.h"
namespace gf { class SDataEnemy; class SDataBlade; class GfInitParamEnemy; }

namespace gf {
// table 0x7100B6A448; its m_rtti names GfObjSetup's as its base (gf_obj_setup.cpp's static initializer)
class GfObjSetupEnemy : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    GfObjSetupEnemy(const GfInitParamEnemy& param);
    virtual ~GfObjSetupEnemy();  // slot 1
    virtual unsigned int getFootStep() const;  // slot 3
    virtual unsigned int getFootStepEffect() const;  // slot 4
    virtual unsigned int getEnArrangeID() const { return m_enArrangeId; }  // slot 5
    void validateBy_pop_act_type(unsigned char type);
    static mm::mtl::RTTI m_rtti;

    // the init param's arrange row (GfInitParamEnemy::getEnArrangeID's field)
    unsigned int pad_6c;
    // what getEnArrangeID returns (the name is not the original's)
    unsigned int m_enArrangeId;
    // the state the enemy starts in: validateBy_pop_act_type sets it from the pop action type (the name is not the
    // original's)
    mm::mtl::FixStr<32> m_stateName;
    // validateBy_pop_act_type clears it for pop action types 3 to 6
    bool pad_98;
    unsigned char pad_99[0xa0 - 0x99];
    // the enemy's data: DataObjEnemy(GF_OBJ_HANDLE*) reads it (the name is not the original's)
    SDataEnemy* m_sdata;
    // its actMove row (BDAT 0x6e): isFlyInsect/isFlyCircle read its actMove_Atr (the name is not the original's)
    unsigned int m_actMoveId;
    unsigned int pad_ac;
    unsigned short pad_b0;
    unsigned char pad_b2;
    unsigned char pad_b3[0xb4 - 0xb3];
    unsigned int pad_b4;
    // the enemy's blade row: DataObjEnemyBlade reads it (the name is not the original's)
    unsigned int m_bladeId;
    unsigned char pad_bc[0x4];
    // owned: the blade's data, set up by the constructor when the init param names a blade; the destructor deletes it
    SDataBlade* pad_c0;
    unsigned char pad_c8[0xd0 - 0xc8];
};
}  // namespace gf

#endif
