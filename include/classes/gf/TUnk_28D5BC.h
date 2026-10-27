#ifndef CLASSES_GF_TUNK_28D5BC_H
#define CLASSES_GF_TUNK_28D5BC_H

namespace fw { class UpdateInfo; }

namespace gf {
// a class with no table (named after its constructor 0x710028D5BC): the 0x20-byte object TUnk_B535D0's setup
// fn_7100291100 makes (gf_game_arena.cpp line 112) and keeps at +0xD0. Its constructor builds a gf::SoundHandle in it;
// layout not recovered.
class TUnk_28D5BC {
public:
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them; their code is in GfAppendWire's unit
    // range. fn_710028D5BC is the constructor; fn_710028D5F0: the arena's setup calls it last on this object; it
    // calls gf::GfSound::createCategoryHandle.
    TUnk_28D5BC();
    void fn_710028D5F0();
    // fn_710028D5EC (placeholder code address; TUnk_B535D0::fn_7100291B64 runs it before freeing the object)
    ~TUnk_28D5BC();
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members: their code is next to the
    // constructor. TUnk_B535D0::fn_7100291B64 calls fn_710028D624 before deleting the object; TUnk_B535D0::fn_7100292060
    // calls fn_710028D644 each frame with the frame's update info.
    void fn_710028D624();
    void fn_710028D644(const ::fw::UpdateInfo& info);

    unsigned char pad_0[0x20];
};
}  // namespace gf

#endif
