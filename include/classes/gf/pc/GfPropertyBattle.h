#ifndef CLASSES_GF_PC_GFPROPERTYBATTLE_H
#define CLASSES_GF_PC_GFPROPERTYBATTLE_H

#include "classes/gf/pc/GfPropertyPcInterface.h"

namespace gf { class GfComPropertyPc; }
namespace gf { class MsgPcBattleStart; }

namespace gf { namespace pc {
// table 0x7100B66B50
class GfPropertyBattle : public ::gf::pc::GfPropertyPcInterface {
public:
    GfPropertyBattle();
    virtual void setup(gf::GfComPropertyPc const&);  // slot 0
    virtual void cleanup(gf::GfComPropertyPc const&);  // slot 1
    virtual void flush(gf::GfComPropertyPc const&);  // slot 2
    // keeps the message's three values as bytes (0x14-0x16)
    void SetStartCondition(gf::MsgPcBattleStart& msg);

    // (the names below are not the original's)
    // setup's CharacterManager::Register id for the owner's handle, -1 while none (cleanup releases it)
    int m_registerId;
    int pad_c;  // the constructor zeroes it
    float pad_10;  // the constructor sets 1.0
    // SetStartCondition's: the message's m_value, m_param0, m_param1 (the constructor zeroes the first only)
    unsigned char m_startValue;
    unsigned char m_startParam0;
    unsigned char m_startParam1;
    unsigned char pad_17;  // the constructor zeroes it
    unsigned char pad_18;  // the constructor zeroes it
};
}}  // namespace gf::pc

#endif
