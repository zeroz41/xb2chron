#ifndef GF_GFBIGOBJUNIQUE_H
#define GF_GFBIGOBJUNIQUE_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// no table: per-frame handling of one big gimmick object (GfComBehaviorGmk holds one, created when the
// gimmick's BDAT row flags it); the field names are not the original's
class GfBigObjUnique {
public:
    struct CreateInfo {
        gf::GF_OBJ_HANDLE* m_handle;  // the object's
    };
    explicit GfBigObjUnique(const CreateInfo* info);
    ~GfBigObjUnique() { dispose(); }
    void create(const CreateInfo& info);
    void dispose();
    void update(float deltaTime);

    gf::GF_OBJ_HANDLE* m_handle;  // create's, -1 without one
    unsigned char pad_8[0x8];
};
}  // namespace gf

#endif
