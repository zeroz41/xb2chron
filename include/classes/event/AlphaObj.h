#ifndef CLASSES_EVENT_ALPHAOBJ_H
#define CLASSES_EVENT_ALPHAOBJ_H

#include "classes/event/AlphaManager.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace event {
// table 0x7100B3C100; one object's alphas, made by AlphaManager::setAlpha (0x48 bytes)
class AlphaObj {
public:
    // inline: AlphaManager::setAlpha builds it
    AlphaObj(gf::GF_OBJ_HANDLE* handle)
        : m_flags(1), m_handle(handle), m_alpha(1.0f), m_alpha2(1.0f), m_count(0) {
        for (int i = 0; i < 4; i++) {
            m_alphas[i] = 1.0f;
            m_alphas2[i] = 1.0f;
        }
    }
    virtual ~AlphaObj() {}  // slot 0
    // the debug line render draws for it
    void draw(int x, int y);
    // stores the attribute's two values and, when either product changes, applies them to the object
    void setAlpha(ALPHA_ATTR attr, float alpha, float time);

    // the names are not the original's
    unsigned int m_flags;  // 0x8 bit 0: still applied (AlphaManager::update clears it once the object is gone or opaque)
    gf::GF_OBJ_HANDLE* m_handle;  // 0x10
    float m_alphas[4];  // 0x18: per attribute
    float m_alphas2[4];  // 0x28: the second value per attribute
    float m_alpha;  // 0x38: the product of m_alphas
    float m_alpha2;  // 0x3c: the product of m_alphas2
    int m_count;  // 0x40: updates it has stayed opaque
};
}  // namespace event

#endif
