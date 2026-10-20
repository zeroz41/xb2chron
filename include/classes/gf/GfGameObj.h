#ifndef CLASSES_GF_GFGAMEOBJ_H
#define CLASSES_GF_GFGAMEOBJ_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace gf {
// a base of gf::GfGameObj no evidence names yet
class TUnk_B550B8 {
public:
    virtual ~TUnk_B550B8();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// a base of gf::GfGameObj no evidence names yet
class TUnk_B550E0 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B550B8; base at 0x0 unknown (TUnk_B550B8), base at 0x8 unknown (TUnk_B550E0)
class GfGameObj : public TUnk_B550B8, public TUnk_B550E0 {
public:
    virtual ~GfGameObj();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
};
}  // namespace gf

#endif
