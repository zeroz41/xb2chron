#include "classes/ui/UIParticleData.h"
#include "classes/ui/UIParticleEmitter.h"
#include "classes/mm/mtl/IAllocator.h"
#include "fw/UpdateInfo.h"
#include "ml/MTRand.h"
#include "mm/Mat33.h"
#include "mm/Math.h"
#include "ui/UIUtil.h"

namespace ui {

UIParticleData::UIParticleData() {}

UIParticleData::~UIParticleData() {
    ;  // a statement, so the table store stays
}

namespace {
// the "UIP " block deserialize reads: its header, then at m_offset the item count and the items (the names are not
// the original's)
struct UIPHeader {
    unsigned int m_magic;    // "UIP "
    unsigned int m_version;  // 0x10000
    unsigned int m_offset;
};
struct UIPItem {
    unsigned int m_id;
    union {
        float f;
        UIParticleData::Range range;
    } value;
};
}  // namespace

void UIParticleData::deserialize(const void* data, unsigned int) {
    if (data == nullptr) {
        return;
    }
    const UIPHeader* header = static_cast<const UIPHeader*>(data);
    if (header->m_magic != 0x20504955 || header->m_version != 0x10000) {
        return;
    }
    const char* list = static_cast<const char*>(data) + header->m_offset;
    const UIPItem* item = reinterpret_cast<const UIPItem*>(list + sizeof(unsigned int));
    for (unsigned int i = 0; i < *reinterpret_cast<const unsigned int*>(list); ++i, ++item) {
        switch (item->m_id) {
        case 1:
            m_item1 = item->value.range;
            break;
        case 2:
            m_item2 = item->value.range;
            break;
        case 3:
            m_item3 = item->value.range;
            break;
        case 4:
            m_item4 = item->value.range;
            break;
        case 5:
            m_colorStart.r = item->value.range;
            break;
        case 6:
            m_colorStart.g = item->value.range;
            break;
        case 7:
            m_colorStart.b = item->value.range;
            break;
        case 8:
            m_colorStart.a = item->value.range;
            break;
        case 9:
            m_colorEnd.r = item->value.range;
            break;
        case 10:
            m_colorEnd.g = item->value.range;
            break;
        case 11:
            m_colorEnd.b = item->value.range;
            break;
        case 12:
            m_colorEnd.a = item->value.range;
            break;
        case 13:
            m_duration = item->value.f;
            break;
        case 14:
            m_life = item->value.range;
            break;
        case 15:
            m_rate = item->value.f;
            break;
        case 16:
            m_angle = item->value.range;
            break;
        case 17:
            m_speed = item->value.range;
            break;
        case 18:
            m_spreadX = item->value.f;
            break;
        case 19:
            m_spreadY = item->value.f;
            break;
        case 20:
            m_gravityX = item->value.f;
            break;
        case 21:
            m_gravityY = item->value.f;
            break;
        case 22:
            m_radialAccel = item->value.range;
            break;
        case 23:
            m_tangentialAccel = item->value.range;
            break;
        }
    }
}

inline UIParticleEmitter::UIParticleEmitter()
    : m_rate(1.0f), m_x(0.0f), m_y(0.0f), m_rot(0.0f), m_time(0.0f), m_duration(0.0f), m_interval(0.0f), m_count(0),
      m_param(), m_enable(false) {
    m_particles.setAllocator(UIUtil::getProgAllocator());
}

UIParticleEmitter::~UIParticleEmitter() {
    if (m_particles.capacity() != 0) {
        m_particles.destroy();
    }
}

UIParticleEmitter* UIParticleEmitter::create(const UIParticleData& data) {
#line 58
    UIParticleEmitter* emitter = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIParticleEmitter();
    emitter->m_duration = data.m_duration;
    emitter->m_interval = 1.0f / data.m_rate;
    emitter->m_gravity.x = data.m_gravityX * (1.0f / 900.0f);
    emitter->m_gravity.y = data.m_gravityY * (-1.0f / 900.0f);
    emitter->m_count = 0;
    emitter->m_param.m_item1 = data.m_item1;
    emitter->m_param.m_item2 = data.m_item2;
    emitter->m_param.m_item3 = data.m_item3;
    emitter->m_param.m_item4 = data.m_item4;
    emitter->m_param.m_colorStart = data.m_colorStart;
    emitter->m_param.m_colorEnd = data.m_colorEnd;
    emitter->m_param.m_life = data.m_life;
    emitter->m_param.m_spreadX = data.m_spreadX;
    emitter->m_param.m_spreadY = data.m_spreadY;
    emitter->m_param.m_angle = data.m_angle;
    emitter->m_param.m_speed = data.m_speed;
    emitter->m_param.m_radialAccel = data.m_radialAccel;
    emitter->m_param.m_tangentialAccel = data.m_tangentialAccel;
    emitter->m_particles.reserve(static_cast<unsigned int>((data.m_life.value + data.m_life.range) * data.m_rate));
    return emitter;
}

namespace {
// a random draw of range either way of 0: range * [-1, 1) in steps of 1/50 (the name is not the original's)
inline float randRange(float range) {
    return (range + range) * (static_cast<float>(static_cast<int>(ml::mtRand()) % 100) / 100.0f) - range;
}
inline float randValue(const UIParticleData::Range& range) {
    return range.value + randRange(range.range);
}
// each component held to [0, 1] (the name is not the original's)
inline void clampColor(mm::Col4& c) {
    if (c.r < 0.0f) c.r = 0.0f;
    if (c.g < 0.0f) c.g = 0.0f;
    if (c.b < 0.0f) c.b = 0.0f;
    if (c.a < 0.0f) c.a = 0.0f;
    if (c.r > 1.0f) c.r = 1.0f;
    if (c.g > 1.0f) c.g = 1.0f;
    if (c.b > 1.0f) c.b = 1.0f;
    if (c.a > 1.0f) c.a = 1.0f;
}
}  // namespace

void UIParticleEmitter::update(const fw::UpdateInfo& info) {
    float dt = info.m_deltaTime;
    float frames = dt / info.m_frameTime;
    for (Particle* it = m_particles.begin(); it != m_particles.end();) {
        Particle& p = *it;
        p.m_age += dt;
        if (!(p.m_age < p.m_life)) {
            it = m_particles.erase(it);
            continue;
        }
        p.m_velocity.x += frames * m_gravity.x;
        p.m_velocity.y += frames * m_gravity.y;
        float dx = p.m_pos.x - m_x;
        float dy = p.m_pos.y - m_y;
        if (!(mm::fabs(dx) <= 1e-06f && mm::fabs(dy) <= 1e-06f)) {
            float inv = 1.0f / ::sqrtf(dx * dx + dy * dy);
            float dirX = dx * inv;
            float dirY = dy * inv;
            p.m_velocity.x += frames * (p.m_radialAccel * dirX);
            p.m_velocity.y += frames * (p.m_radialAccel * dirY);
            mm::Mat33 mtx = mm::Mat33::identity;
            mtx.rotateZ(-1.57079637f);
            mtx.transform(dirX, dirY);
            p.m_velocity.x += frames * (dirX * p.m_tangentialAccel);
            p.m_velocity.y += frames * (dirY * p.m_tangentialAccel);
        }
        p.m_pos.x += frames * p.m_velocity.x;
        p.m_pos.y += frames * p.m_velocity.y;
        ++it;
    }
    if (!m_enable) {
        return;
    }
    float interval = m_interval * m_rate;
    float emitted = interval * m_count;
    m_time += dt;
    if (m_duration != -1.0f) {
        if (m_time > m_duration) {
            m_time = m_duration;
        }
    } else if (m_count > 10000 && m_time > interval * 10000.0f) {
        m_time -= interval * 10000.0f;
        m_count = 0;
        emitted = 0.0f;
    }
    unsigned int count = (m_time - emitted) / interval;
    if (count == 0) {
        return;
    }
    for (unsigned int i = 0; i < count; ++i) {
        if (m_particles.size() == m_particles.capacity()) {
            break;
        }
        Particle p;
        p.m_age = 0.0f;
        p.m_life = randValue(m_param.m_life);
        float x = randRange(m_param.m_spreadX);
        float y = randRange(m_param.m_spreadY);
        if (m_rot != 0.0f) {
            mm::Mat33 mtx = mm::Mat33::identity;
            mtx.rotateZ(-m_rot);
            mtx.transform(x, y);
        }
        p.m_pos = mm::Vec2(x + m_x, y + m_y);
        float angle = randValue(m_param.m_angle);
        float speed = randValue(m_param.m_speed) / 30.0f;
        angle *= 0.0174532924f;  // degrees to radians
        p.m_velocity.x = ::cosf(angle) * speed;
        p.m_velocity.y = -(::sinf(angle) * speed);
        p.m_radialAccel = randValue(m_param.m_radialAccel) * (1.0f / 900.0f);
        p.m_tangentialAccel = randValue(m_param.m_tangentialAccel) * (1.0f / 900.0f);
        p.m_item3 = randValue(m_param.m_item3);
        p.m_item4 = randValue(m_param.m_item4);
        p.m_item1 = randValue(m_param.m_item1);
        p.m_item2 = randValue(m_param.m_item2);
        float rStart = randValue(m_param.m_colorStart.r);
        float gStart = randValue(m_param.m_colorStart.g);
        float bStart = randValue(m_param.m_colorStart.b);
        float aStart = randValue(m_param.m_colorStart.a);
        p.m_colorStart = mm::Col4(rStart, gStart, bStart, aStart);
        clampColor(p.m_colorStart);
        float rEnd = randValue(m_param.m_colorEnd.r);
        float gEnd = randValue(m_param.m_colorEnd.g);
        float bEnd = randValue(m_param.m_colorEnd.b);
        float aEnd = randValue(m_param.m_colorEnd.a);
        p.m_colorEnd = mm::Col4(rEnd, gEnd, bEnd, aEnd);
        clampColor(p.m_colorEnd);
        m_particles.push_back(p);
    }
    m_count += count;
}


}  // namespace ui
