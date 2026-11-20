#ifndef CLASSES_EVENT_CHARASETTAR_H
#define CLASSES_EVENT_CHARASETTAR_H

#include "classes/event/ICmd.h"
#include "mm/Vec2.h"
#include "mm/Vec3.h"
#include "classes/event/TarAxis.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3E4F8
class CharaSetTar : public ::event::ICmd {
public:
    CharaSetTar()
        : m_flags(0), m_handle(reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1)), pad_18(), pad_40(0), pad_44(1.0f),
          pad_48(0.0f), pad_50(mm::Vec3::zero), pad_80(mm::Vec3::zero) {}
    virtual ~CharaSetTar() {}  // slot 0
    virtual int update(event::ICmd::Param const&);  // slot 3
    virtual void term();  // slot 4
    void idle();  // out of line (0x71000E5CD8); term calls it while bit 0 is set
    // the lens offset (-1..1 each way) that turns the eye direction from toward to: the yaw difference over
    // LENS_LIMIT.y, the pitch difference over LENS_LIMIT.x (the parameter names are not the original's)
    static mm::Vec2 calcLensUV(const mm::Vec3& from, const mm::Vec3& to);
    static const mm::Vec2 LENS_LIMIT;  // calcLensUV's bounds
    static const mm::Vec2 JOY_LIMIT;
    // bit 0: term calls idle and clears it; the name is not the original's
    unsigned int m_flags;  // 0x8
    unsigned char pad_c[0x4];
    // the constructor stores -1 here, as in the other commands' handles; the name is not the original's
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10
    unsigned long pad_18[5];
    int pad_40;
    float pad_44;
    float pad_48;
    unsigned char pad_4c[0x4];
    mm::Vec3 pad_50;
    TarAxis pad_60;
    mm::Vec3 pad_80;
};
}  // namespace event

#endif
