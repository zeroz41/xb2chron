#ifndef CLASSES_GF_TFIELDEXECCMDTURN_H
#define CLASSES_GF_TFIELDEXECCMDTURN_H

#include "classes/gf/TFieldExecCmd.h"

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class GfComTransform; }

namespace gf {
// table none; a field turn: turns an object toward a target through a field command its animation component
// (T: GfComEvtAnim) executes (GfComBehaviorEvent holds one at 0xa0). 0x70 bytes. The field names are not the
// original's.
template <typename T>
class TFieldExecCmdTurn {
public:
    // what create takes (the destructor resets it to these values)
    struct CreateInfo {
        CreateInfo()
            : handle(reinterpret_cast<GF_OBJ_HANDLE*>(-1)), pad_8(0.0f), pad_c(0.785398185f), pad_10(1.57079637f),
              pad_14(1.0f), pad_18(0) {}
        // a turn of the object by angle (GfComBehaviorMob::execTurnCmdToPos)
        CreateInfo(GF_OBJ_HANDLE* handle_, float angle)
            : handle(handle_), pad_8(angle), pad_c(0.785398185f), pad_10(1.57079637f), pad_14(1.0f), pad_18(0) {}
        GF_OBJ_HANDLE* handle;
        float pad_8;
        float pad_c;
        float pad_10;
        float pad_14;
        int pad_18;
    };

    TFieldExecCmdTurn() : pad_58(0.0f), pad_5c(1.0f), pad_60(false), pad_64(0), pad_68(0), pad_6c(false) {}
    ~TFieldExecCmdTurn() { clear(); }
    // forgets the turn (inline: the destructor inlines it)
    void clear() {
        pad_6c = false;
        pad_60 = false;
        pad_64 = 0;
        m_cmd.m_executed = false;
        m_cmd.clear();
        m_info = CreateInfo();
    }
    void create(const CreateInfo& info);
    void update(float dt);
    void applyDeltaRotY(GfComTransform& transform, float delta);

    CreateInfo m_info;
    TFieldExecCmd<T> m_cmd;
    float pad_58;
    float pad_5c;
    bool pad_60;
    int pad_64;
    int pad_68;
    bool pad_6c;
};
}  // namespace gf

#endif
