#ifndef CLASSES_GF_GFBDATMSG_H
#define CLASSES_GF_GFBDATMSG_H

namespace gf {
// a base of gf::GfBdatMsg no evidence names yet
class TUnk_B471A8 {
public:
    virtual ~TUnk_B471A8();
    virtual void bdatRefresh() = 0;
};
// a base of gf::GfBdatMsg no evidence names yet
class TUnk_B471D0 {
public:
    virtual ~TUnk_B471D0();
    virtual void bdatRefresh() = 0;
};
// table 0x7100B471A8; base at 0x0 unknown (TUnk_B471A8), base at 0x8 unknown (TUnk_B471D0)
class GfBdatMsg : public TUnk_B471A8, public TUnk_B471D0 {
public:
    virtual ~GfBdatMsg();  // slot 0
    virtual void bdatRefresh();  // slot 2
};
}  // namespace gf

#endif
