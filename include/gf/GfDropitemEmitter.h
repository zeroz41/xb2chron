#ifndef GF_GFDROPITEMEMITTER_H
#define GF_GFDROPITEMEMITTER_H

namespace gf {
// drops a treasure's items (GfFieldTbox and GfFieldCollect hold one; GfFobjDropitem's unit defines it)
class GfDropitemEmitter {
public:
    struct CreateInfo;
    GfDropitemEmitter(const CreateInfo* info);
    ~GfDropitemEmitter() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float dt);

    unsigned char pad_0[0x40];
    // whether the items have been dropped (GfFieldTbox::isDropitemsEmitted reads it; the name is not the original's)
    bool m_isEmitted;
    unsigned char pad_41[0x1f];
} __attribute__((aligned(16)));  // its constructor starts it with a Vec3 (Vec3::zero's copy)
}  // namespace gf

#endif
