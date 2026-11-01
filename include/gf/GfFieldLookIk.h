#ifndef GF_GFFIELDLOOKIK_H
#define GF_GFFIELDLOOKIK_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// no table: an object's look-at ik (gf_game_stuck_meter's unit); GfComBehaviorMob keeps one at 0x210, its
// TFieldExecCmdTurn next at 0x250 (0x40 bytes). Its fields are not known yet
class GfFieldLookIk {
public:
    explicit GfFieldLookIk(GF_OBJ_HANDLE* handle);
    ~GfFieldLookIk() { dispose(); }
    void dispose();
    void update(float deltaTime);  // 0x71002D2964

    unsigned char pad_0[0x40];
};
}  // namespace gf

#endif
