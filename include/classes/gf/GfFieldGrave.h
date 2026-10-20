#ifndef CLASSES_GF_GFFIELDGRAVE_H
#define CLASSES_GF_GFFIELDGRAVE_H

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// a base of gf::GfFieldGrave no evidence names yet
class TUnk_B52318 {
public:
    virtual void getIdStr() const = 0;
    virtual void create(gf::GF_OBJ_HANDLE*) = 0;
    virtual void dispose() = 0;
    virtual void isEnd() const = 0;
    virtual void cancel() = 0;
    virtual ~TUnk_B52318();
};
// a base of gf::GfFieldGrave no evidence names yet
class TUnk_B52360 {
public:
    virtual ~TUnk_B52360();
};
// table 0x7100B52318; base at 0x0 unknown (TUnk_B52318), base at 0x8 unknown (TUnk_B52360)
class GfFieldGrave : public TUnk_B52318, public TUnk_B52360 {
public:
    virtual void getIdStr() const;  // slot 0
    virtual void create(gf::GF_OBJ_HANDLE*);  // slot 1
    virtual void dispose();  // slot 2
    virtual void isEnd() const;  // slot 3
    virtual void cancel();  // slot 4
    virtual ~GfFieldGrave();  // slot 5
};
}  // namespace gf

#endif
