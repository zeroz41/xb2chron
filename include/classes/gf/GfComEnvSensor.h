#ifndef CLASSES_GF_GFCOMENVSENSOR_H
#define CLASSES_GF_GFCOMENVSENSOR_H

#include "mm/mtl/RTTI.h"
#include "classes/gf/GfComponent.h"
#include "gf/EnviromentSensor.h"
#include "fw/ParamAdapter.h"
namespace fw { class Message; }
namespace fw { class MessageObject; }

namespace gf {
// table 0x7100B66108; its m_rtti names GfComponent's as its base
class GfComEnvSensor : public ::gf::GfComponent {
public:
    class EnvListener;
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfComEnvSensor();  // slot 1
    virtual void changeLayer(unsigned int, unsigned int);  // slot 3
    virtual bool recieveMessage(fw::MessageObject*, fw::Message&);  // slot 4
    // m_sensor (inline: the name is not the original's)
    const gf::EnviromentSensor& getSensor() const { return m_sensor; }
    static mm::mtl::RTTI m_rtti;

    gf::EnviromentSensor m_sensor;  // the constructor builds it, flushEnv checks around the object with it
    unsigned char pad_2b0[0x30];
    // its parameter entry (1.0.0's setup takes it from a parameter list by its setup info's index); its first two
    // values reach below and above (TaskFieldCheckWarpBattleWaterDead::update searches that far for water)
    fw::ParamAdapter m_param;
};
}  // namespace gf

#endif
