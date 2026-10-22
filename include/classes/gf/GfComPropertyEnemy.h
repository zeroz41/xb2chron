#ifndef CLASSES_GF_GFCOMPROPERTYENEMY_H
#define CLASSES_GF_GFCOMPROPERTYENEMY_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComProperty.h"
#include "fw/Transform.h"
#include "gf/GfEnemyBattleProperty.h"

namespace gf {
// table 0x7100B660D0
class GfComPropertyEnemy : public ::gf::GfComProperty {
public:
    struct SetupInfo {};
    GfComPropertyEnemy();
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComPropertyEnemy();  // slot 1
    void setup(const SetupInfo& info);
    void cleanup();
    void flush();
    void writeBack();
    bool getWaterHeight(float& height) const;
    float getChestHeight() const;
    bool isFieldDeadCondMatched() const;
    static mm::mtl::RTTI m_rtti;

    gf::enemy::GfEnemyBattleProperty m_battleProperty;  // (the name is not the original's)
    // the object's world transform as writeBack last kept it (setup: the one it starts with); the name is not
    // the original's
    fw::Transform m_prevTransform;
    // the object's world transform as flush last read it (the name is not the original's)
    fw::Transform m_transform;
};
}  // namespace gf

#endif
