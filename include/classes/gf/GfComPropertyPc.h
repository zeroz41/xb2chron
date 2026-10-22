#ifndef CLASSES_GF_GFCOMPROPERTYPC_H
#define CLASSES_GF_GFCOMPROPERTYPC_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/ParamList.h"
#include "classes/gf/GfComProperty.h"
#include "mm/Vec3.h"
#include "mm/mtl/IntrusivePtr.h"
#include "classes/gf/pc/GfPropertyField.h"

namespace fw { class Message; }
namespace fw { class MessageObject; }
namespace gf { class EnviromentSensor; }

namespace gf {
// table 0x7100B69448
class GfComPropertyPc : public ::gf::GfComProperty {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComPropertyPc();  // slot 1
    virtual void recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    const gf::EnviromentSensor* getEnvSensor() const;
    void setInputDirPow(const mm::Vec3& dir, float pow);

    static mm::mtl::RTTI m_rtti;

    // setup copies it from its SetupInfo's first word (0 and nonzero pick different state flags); the constructor
    // and cleanup set -1, and AIAgent runs its field AI only while it is not -1
    int m_setupKind;
    unsigned char pad_3c[0x2C];
    unsigned int m_inputFlags;  // after setInputDirPow's input; bit 2: TaskFieldJump::update sets it
    unsigned char pad_6c[0x14];
    mm::Vec3 m_velocity;        // TaskFieldJump::update keeps its speed, turned along m_moveDir
    unsigned char pad_90[0x70];
    mm::Vec3 m_colVel;          // ColVelCalculatorPlugin::update's: the ground's movement it carries the PC with
    // bit 4: ColVelCalculatorPlugin::update takes the ground's movement; bit 10: DeadColCheckPlugin::testDead asks
    // the first collision object instead of the dead plane
    unsigned int m_stateFlags;
    unsigned char pad_114[0x4C];
    mm::Vec3 m_pos;             // TaskFieldRetreat::update routes the PC from it
    unsigned char pad_170[0x10];
    mm::Vec3 m_prevPos;         // DeadColCheckPlugin::testDead: falling from above a dead plane's height to it
    unsigned char pad_190[0x50];
    mm::Vec3 m_moveDir;         // TaskFieldJump::update sets m_velocity along it
    unsigned char pad_1f0[0x110];
    mm::mtl::IntrusivePtr<fw::ParamList> m_paramList;  // the PC's parameters
    unsigned char pad_308[0x8];
    pc::GfPropertyField m_field;  // setup, cleanup and flush pass it this property
};
}  // namespace gf

#endif
