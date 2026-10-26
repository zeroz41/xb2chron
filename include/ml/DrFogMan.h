#ifndef ML_DRFOGMAN_H
#define ML_DRFOGMAN_H

namespace ml { class DrMan; }
namespace ml { class DrFogObjGbl; }

namespace ml {
// Not polymorphic: the constructor stores no table. Only what its functions in DrEnvironmentAnim.cpp read is
// declared; the field names are not the original's.
class DrFogMan {
public:
    DrFogMan(DrMan* drMan);
    ~DrFogMan();
    void releaseAll();
    bool isFogOn() const;

    DrMan* m_drMan;  // 0x0, the constructor stores its argument
    DrFogObjGbl* m_head;  // 0x8, releaseAll deletes the list from here
    DrFogObjGbl* m_tail;  // 0x10
    unsigned char pad_18[0xB8];
    bool m_fogOn;  // 0xD0, isFogOn (the constructor clears it)
};
}  // namespace ml

#endif
