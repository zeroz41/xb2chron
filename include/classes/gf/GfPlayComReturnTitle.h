#ifndef CLASSES_GF_GFPLAYCOMRETURNTITLE_H
#define CLASSES_GF_GFPLAYCOMRETURNTITLE_H

namespace fw { class UpdateInfo; }

namespace gf {
// a base of gf::GfPlayComReturnTitle no evidence names yet
class TUnk_B589A0 {
public:
    virtual void getRTTI() const = 0;
    virtual ~TUnk_B589A0();
    virtual void getFuncName() const = 0;
    virtual void start() = 0;
    virtual void end() = 0;
    virtual void update(fw::UpdateInfo const&, bool) = 0;
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of gf::GfPlayComReturnTitle no evidence names yet
class TUnk_B589E8 {
public:
    virtual ~TUnk_B589E8();
};
// table 0x7100B589A0; base at 0x0 unknown (TUnk_B589A0), base at 0x10 unknown (TUnk_B589E8)
class GfPlayComReturnTitle : public TUnk_B589A0, public TUnk_B589E8 {
public:
    virtual void getRTTI() const;  // slot 0
    virtual ~GfPlayComReturnTitle();  // slot 1
    virtual void getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void end() {}  // slot 5
    virtual void update(fw::UpdateInfo const&, bool);  // slot 6
};
}  // namespace gf

#endif
