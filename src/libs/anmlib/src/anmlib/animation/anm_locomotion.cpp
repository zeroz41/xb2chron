#include "math.h"
#include "anm/Array.h"
#include "mm/Vec4.h"
#include "classes/anm/Animation.h"
#include "classes/anm/EmptyAnimation.h"
#include "anm/SerialiseArg.h"
#include "anm/Locomotion.h"
#include "anm/TransformUtil.h"
#include "anm/QsTransform.h"
#include "mm/Math.h"
#include "mm/MMStdBase.h"

namespace anm {

EmptyAnimation::EmptyAnimation(const SerialiseArg&) {}

int EmptyAnimation::getImplType() const {
    return 2;
}

void EmptyAnimation::sampleTrucks(float, const anm::Binding&, anm::QsTransform*) const {}

// the locals' names are not the original's
void Locomotion::getReference(float time, QsTransform* pDst) const {
#line 24
    MM_ASSERT(pDst);
    int lastKey = m_keys.size() - 1;
    mm::Vec4 key;
    if (m_interval * lastKey <= time) {
        key = m_keys[lastKey];
    } else if (time <= 0.0f) {
        key = m_keys[0];
    } else {
        float whole;
        float blend = modff(time / m_interval, &whole);
        unsigned int key0 = static_cast<unsigned int>(whole);
        unsigned int key1 = key0 + 1 >= lastKey ? lastKey : key0 + 1;
        const mm::Vec4& from = m_keys[key0];
        const mm::Vec4& to = m_keys[key1];
        float rest = 1.0f - blend;
        key = mm::Vec4(rest * from.x + blend * to.x, rest * from.y + blend * to.y, rest * from.z + blend * to.z,
                       rest * from.w + blend * to.w);
    }
    pDst->m_translation = mm::Vec4(key.x, key.y, key.z, 0.0f);
    float angle = key.w;
    mm::Vec3 axis;
    float length = m_axis.length();
    if (length <= 1e-6f) {
        axis = mm::Vec3::zero;
    } else {
        float scale = 1.0f / length;
        axis.x = scale * m_axis.x;
        axis.y = scale * m_axis.y;
        axis.z = scale * m_axis.z;
    }
    float half = angle * 0.5f;
    float s = sinf(half);
    float c = cosf(half);
    pDst->m_rotation.w = c;
    pDst->m_rotation.x = axis.x * s;
    pDst->m_rotation.y = axis.y * s;
    pDst->m_rotation.z = axis.z * s;
    pDst->m_scale = mm::Vec4::unit;
}

void Locomotion::getDeltaReference(float time, float delta, float start, float end, bool loop,
                                   QsTransform* pDst) const {
    float from = mm::clamp(time, start, end);
    float to = from + delta;
    unsigned int laps;
    if (loop) {
        float length = end - start;
        laps = static_cast<unsigned int>(to / length);
        to = to - length * laps;
    } else {
        to = to < end ? to : end;
        laps = 0;
    }
    QsTransform inverse;
    QsTransform fromRef;
    QsTransform toRef;
    getReference(from, &fromRef);
    getReference(to, &toRef);
    if (laps != 0) {
        QsTransform endRef;
        QsTransform lap;
        QsTransform last;
        getReference(end, &endRef);
        TransformUtil::invert(fromRef, &inverse);
        TransformUtil::mul(inverse, endRef, &lap);
        for (unsigned int i = 1; i < laps; i++) {
            TransformUtil::mul(lap, endRef, &lap);
        }
        getReference(start, &fromRef);
        TransformUtil::invert(fromRef, &inverse);
        TransformUtil::mul(inverse, toRef, &last);
        TransformUtil::mul(lap, last, pDst);
    } else {
        TransformUtil::invert(fromRef, &inverse);
        TransformUtil::mul(inverse, toRef, pDst);
    }
    pDst->m_scale = mm::Vec4::unit;
}

}  // namespace anm
