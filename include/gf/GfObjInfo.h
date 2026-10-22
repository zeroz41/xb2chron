#ifndef GF_GFOBJINFO_H
#define GF_GFOBJINFO_H

namespace gf { class GfObjSetup; }

namespace gf {
// no table: what GfObjManager keeps for one object (getObjInfo looks it up by the object's handle)
class GFOBJ_INFO {
public:
    unsigned char pad_0[0x30];
    // the object's setup; the destructor deletes it (the name is not the original's)
    GfObjSetup* m_setup;
};
}  // namespace gf

#endif
