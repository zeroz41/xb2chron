#ifndef GF_GFFIELDMOVESPEED_H
#define GF_GFFIELDMOVESPEED_H

#include "classes/gf/TGfTween.h"
#include "classes/gf/GfSpeedTween.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// no table: drives an object's asm "V_speed" variable and play speed towards a speed in km/h, eased over a
// time; the field names are not the original's
class GfFieldMoveSpeed {
public:
    struct CreateInfo {
        gf::GF_OBJ_HANDLE* m_handle;
    };
    explicit GfFieldMoveSpeed(const CreateInfo* info);
    void create(const CreateInfo& info);
    void dispose();
    void setSpeedKmph(float speed, float duration);
    void update(float deltaTime);

    static const char* s_S_move;
    static const char* s_V_speed;

    gf::GF_OBJ_HANDLE* m_handle;  // create's, -1 without one
    float m_speedMin;  // the S_move state's V_speed range (at least 1e-6)
    float m_speedMax;
    float m_speed;     // the speed now
    TGfTween<float> m_tween;
};

// the same for enemies: the speed moves towards its target at a rate per second
class GfEnemyFieldMoveSpeed {
public:
    struct CreateInfo {
        gf::GF_OBJ_HANDLE* m_handle;
    };
    explicit GfEnemyFieldMoveSpeed(const CreateInfo* info);
    void create(const CreateInfo& info);
    void setSpeedKmph(float speed, float rate);
    void update(float deltaTime);

    static const char* s_S_move;
    static const char* s_V_speed;

    gf::GF_OBJ_HANDLE* m_handle;  // create's, -1 without one
    float m_speedMin;
    float m_speedMax;
    float m_speed;
    GfSpeedTween m_tween;
};
}  // namespace gf

#endif
