#ifndef CLASSES_EVENT_OUTSIDERMANAGER_H
#define CLASSES_EVENT_OUTSIDERMANAGER_H

namespace event { enum MSG_TYPE : int; }

#include "mm/Vec3.h"

namespace event {
// a base of event::OutsiderManager no evidence names yet
// 1.0.0's OutsiderField (OutsiderManager holds one at 0x20)
class OutsiderField {
public:
    enum TYPE : int;
    inline void clear();  // 1.0.0's OutsiderField::clear (3.0.1 inlines it)
    void update();
    void draw();
    TYPE m_type;  // 0x0 setField's first argument
    unsigned char pad_4[0xC];
    mm::Vec3 m_pos;   // 0x10 setField's position (the name is not the original's)
    float m_size;     // 0x20 setField's float (the name is not the original's)
    unsigned char pad_24[0xC];
    mm::Vec3 m_hitPos;  // 0x30 update stores a position here (the name is not the original's)
    float m_hitRate;    // 0x40 above 0: OutsiderManager::update(true) runs (the name is not the original's)
};

class TUnk_B3D350 {
public:
    virtual ~TUnk_B3D350() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::OutsiderManager no evidence names yet
class TUnk_B3D378 {
public:
    virtual ~TUnk_B3D378() {}
};
// table 0x7100B3D350; base at 0x0 unknown (TUnk_B3D350), base at 0x8 unknown (TUnk_B3D378)
class OutsiderManager : public TUnk_B3D350, public TUnk_B3D378 {
public:
    virtual ~OutsiderManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    enum OBJ_TYPE : int;
    // 1.0.0's clear/update()/render (3.0.1 inlines them; defined inline in CharaObj.cpp)
    void clear();
    void update();
    void render();
    void update(bool);  // out of line
    unsigned int m_dispFlags;  // 0x10 bit 0: render draws the field (the name is not the original's)
    unsigned int m_flags;      // 0x14 bit 0: setActive (the name is not the original's)
    OBJ_TYPE m_tgtType;        // 0x18 defineTgt (the name is not the original's)
    unsigned int pad_1c;
    OutsiderField m_field;     // 0x20 (the name is not the original's)
};
}  // namespace event

#endif
