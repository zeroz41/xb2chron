#ifndef CLASSES_GF_GFOBJSETUPENEMY_H
#define CLASSES_GF_GFOBJSETUPENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfObjSetup.h"
namespace gf { class SDataEnemy; }

namespace gf {
// table 0x7100B6A448; its m_rtti names GfObjSetup's as its base (gf_obj_setup.cpp's static initializer)
class GfObjSetupEnemy : public ::gf::GfObjSetup {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfObjSetupEnemy();  // slot 1
    virtual void getFootStep() const;  // slot 3
    virtual void getFootStepEffect() const;  // slot 4
    virtual unsigned int getEnArrangeID() const;  // slot 5
    static mm::mtl::RTTI m_rtti;

    unsigned char pad_50[0x50];
    // the enemy's data: DataObjEnemy(GF_OBJ_HANDLE*) reads it (the name is not the original's)
    SDataEnemy* m_sdata;
    unsigned char pad_a8[0x10];
    // the enemy's blade row: DataObjEnemyBlade reads it (the name is not the original's)
    unsigned int m_bladeId;
};
}  // namespace gf

#endif
