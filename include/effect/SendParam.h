#ifndef EFFECT_SENDPARAM_H
#define EFFECT_SENDPARAM_H

#include "mm/Mat44.h"
#include "mm/Vec3.h"
#include "string.h"

namespace effect {

// what an effect is created or updated with (fw::EffectManager::create and setParam hand one to the
// SystemManager; es_set_param_pos_only copies its first 0x58 bytes and the fields up to 0xA9). The names are
// not the original's.
// The defaults are what WeatherEff::create and GfComEffectCaster::createFromFileName store; 1.0.0's
// SystemManager::es_conv_param reads the fields with the sizes typed here.
class SendParam {
public:
    // assigned in this order: the order the original's stores (and their merging) need
    SendParam() : m_mtx(mm::Mat44::identity) {
        m_color[0] = 1.0f;
        m_color[1] = 1.0f;
        m_color[2] = 1.0f;
        m_color[3] = 1.0f;
        m_colorExt[0] = 0.0f;
        m_colorExt[1] = 0.0f;
        m_scale.y = 1.0f;
        m_scale.z = 1.0f;
        m_scale.x = 1.0f;
        m_rotate.x = 0.0f;
        m_rotate.y = 0.0f;
        m_rotate.z = 0.0f;
        m_flagA = false;
        m_flagB = true;
        m_option = 0;
        m_flagF = 0;
        m_rangeA = -1.0f;
        m_valueA = 0.0f;
        m_id = 0xFFFF;
        m_flagC = false;
        m_flagD = false;
        m_rangeB[2] = -1.0f;
        m_rangeB[3] = -1.0f;
        m_rangeB[0] = -1.0f;
        m_rangeB[1] = -1.0f;
        m_rangeC = -1.0f;
        m_category = 0;
        m_flagE = false;
    }
    // copied whole, checked against itself first: the SystemManager's command queue copies it so (es_pause); an
    // assignment copies it member by member (es_set_param)
    SendParam(const SendParam& other) {
        if (this != &other) {
            memcpy(this, &other, sizeof(SendParam));
        }
    }
    SendParam& operator=(const SendParam& other) = default;

    mm::Mat44 m_mtx;  // where the effect sits (GfEffectGround::calcSwimEffectParam sets its height)
    float m_color[4];  // 1 each by default (es_conv_param copies it whole)
    float m_colorExt[2];  // 0 each by default (es_conv_param copies it as one 8-byte value)
    mm::Vec3 m_scale;  // 1 each by default (es_conv_param reads x only)
    mm::Vec3 m_rotate;  // 0 each by default
    float m_rangeA;  // -1 by default
    float m_valueA;
    float m_rangeB[4];  // -1 each by default
    float m_rangeC;  // -1 by default
    unsigned int m_category;  // es_set_category stores the category here (the name is not the original's)
    unsigned short m_id;  // 0xFFFF by default
    bool m_flagA;
    // true by default; es_set_viewnum stores its view number here (a byte, not a bool)
    unsigned char m_flagB;
    unsigned char m_option;
    // EffectManager::setParam(handle, mtx, scale, value) sets it (the name is not the original's)
    unsigned char m_flagF;
    bool m_flagC;
    bool m_flagD;  // WeatherEff::create sets it
    bool m_flagE;
};

}  // namespace effect

#endif
