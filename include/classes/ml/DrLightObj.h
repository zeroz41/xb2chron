#ifndef CLASSES_ML_DRLIGHTOBJ_H
#define CLASSES_ML_DRLIGHTOBJ_H

namespace ml { class DrLightMan; }
namespace ml { class DrPixlMan; }
namespace ml { class DrPixlShadowObj; }

namespace ml {
// table 0x7100B7B530
// DrLightMan keeps its lights in intrusive lists (releaseAll walks m_next). Field and flag names are not the
// original's; the flag names follow the is*() getters (named by the symbols) that test them.
class DrLightObj {
public:
    // m_type values (isAmb/isDir/isPnt/isSpt in 1.0.0 compare against them; the names are not the original's)
    enum {
        TYPE_AMB = 0,
        TYPE_DIR = 1,
        TYPE_PNT = 2,
        TYPE_SPT = 3,
    };
    // m_flags bits (the names are not the original's)
    enum {
        FLAG_SHADOW = 0x1,  // a shadow object is held (delete*Shadow clears it)
        FLAG_CACHE_SHADOW = 0x4,  // isCacheShadow
        FLAG_TEX = 0x8,  // isTex (1.0.0)
        FLAG_RELEASE = 0x10000,  // shifted by DrMan's double-buffer index (DrLightMan::releaseInstant*Light)
        FLAG_CHAR_SHADOW = 0x40000,  // isCharShadow
        FLAG_BASE_MAP_SHADOW = 0x80000,  // isBaseMapShadow
        FLAG_INST_MAP_SHADOW = 0x100000,  // isInstMapShadow
        FLAG_INST_SEL_MAP_SHADOW = 0x200000,  // isInstSelMapShadow
        FLAG_SUBTRACT = 0x400000,  // setSubtractOn
        FLAG_CULL = 0x40000000,  // isCullON
    };

    DrLightObj();
    virtual ~DrLightObj() {}  // slot 0
    virtual void update(ml::DrLightMan*) {}  // slot 2

    bool isPnt() const;  // a point light (DrResMdoLight::release hands those to releasePntLight)
    bool isCullON() const;
    bool isCharShadow() const;
    bool isBaseMapShadow() const;
    bool isInstMapShadow() const;
    bool isInstSelMapShadow() const;
    bool isCacheShadow() const;
    void setSubtractOn(bool on);

    DrLightObj* m_prev;  // 0x8
    DrLightObj* m_next;  // 0x10
    int m_type;  // 0x18, TYPE_*
    unsigned int m_flags;  // 0x1C, FLAG_*
    DrPixlMan* m_pixlMan;  // 0x20, the (DrPixlMan*) constructor in 1.0.0 stores it
    DrPixlShadowObj* m_shadowObj;  // 0x28
};
}  // namespace ml

#endif
