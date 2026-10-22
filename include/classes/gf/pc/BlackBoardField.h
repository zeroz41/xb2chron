#ifndef CLASSES_GF_PC_BLACKBOARDFIELD_H
#define CLASSES_GF_PC_BLACKBOARDFIELD_H

#include "mm/mtl/RTTI.h"
#include "classes/ai/BlackBoard.h"
#include "mm/Vec3.h"

namespace gf { class GfComPropertyPc; }
namespace navi { class NvmshAcObj; }

namespace gf { namespace pc {
// table 0x7100B67908
class BlackBoardField : public ::ai::BlackBoard {
public:
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~BlackBoardField();  // slot 1
    static mm::mtl::RTTI m_rtti;

    gf::GfComPropertyPc* m_property;  // the PC's property (TaskFieldIdle::update sets its idle input)
    navi::NvmshAcObj* m_nvmshAcObj;   // the PC's navigation mesh path (TaskFieldRetreat::update routes it)
    unsigned char pad_18[0x1D8];
    mm::Vec3 m_retreatPos;            // TaskFieldRetreat routes the PC to it while farther than 1 from it
    // bits 0-2: TaskFieldSensor::update; bit 3: set by TaskFieldRetreat::update, cleared by TaskFieldIdle::update;
    // bit 4: TaskFieldRetreat::testCondition requires it
    unsigned int m_flags;
};
}}  // namespace gf::pc

#endif
