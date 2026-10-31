#ifndef CLASSES_NAVI_NVMSHACOBJBASEDEF_H
#define CLASSES_NAVI_NVMSHACOBJBASEDEF_H

#include "classes/navi/NvmshAcObjBase.h"

namespace navi { class NvmshResMan; }

namespace navi {
// table 0x7100B7F6C0
class NvmshAcObjBaseDef : public ::navi::NvmshAcObjBase {
public:
    virtual ~NvmshAcObjBaseDef();  // slot 0
    virtual void release();  // slot 14
    // returns whether the object asked for its release (NvmshAcMan::objectUpdate then unlinks and resets it); the
    // first parameter is set when it searched this frame (objectUpdate counts those)
    virtual bool update(bool&, navi::NvmshResMan*, bool);  // slot 15

    // NvmshAcObjBaseDef::update's status step: the mesh number and the flags (bits 3, 2, 5, 6) mirrored into the
    // status bits 0x8000, 0x10000, 0x20000 and 0x40000 (each change clears the state bits 0xB01C1F); with status bit
    // 2 set, bits 0x901C00 and m_flag5F are cleared once m_vec130 is 4 or more from m_vec110
    void stateUpdate();
};
}  // namespace navi

#endif
