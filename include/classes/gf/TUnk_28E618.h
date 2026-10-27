#ifndef CLASSES_GF_TUNK_28E618_H
#define CLASSES_GF_TUNK_28E618_H

namespace gf { class TUnk_B535D0; }

namespace gf {
// a class with no table (named after its constructor 0x710028E618): the 0x58-byte object TUnk_B535D0's setup
// fn_7100291100 makes (gf_game_arena.cpp line 111) and keeps at +0xC8. Its constructor keeps the arena at +0 and
// zeroes +8 and +0x50; layout not recovered.
class TUnk_28E618 {
public:
    // Placeholder name (constructor): new in 3.0.1, nothing in 1.0.0's place names it; its code (fn_710028E618) is in
    // unit_710028E5BC's range.
    explicit TUnk_28E618(TUnk_B535D0* owner);
    // fn_710028E624 (placeholder code address; TUnk_B535D0::fn_7100291B64 runs it before freeing the object)
    ~TUnk_28E618();

    TUnk_B535D0* m_owner;  // (the name is not the original's)
    unsigned char pad_8[0x50];
};
}  // namespace gf

#endif
