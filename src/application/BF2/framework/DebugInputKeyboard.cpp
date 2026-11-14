#include "classes/ml/DebDraw.h"
#include "classes/ml/CacheDraw.h"
#include "fw/FwDebug.h"

#include <stdarg.h>
#include <stdio.h>

#include "classes/fw/ForceCalculator.h"
#include "mm/Col4.h"
#include "mm/Mat44.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"
#include "mm/Vec3.h"
#include "mm/mtl/FixStr.h"

namespace fw { namespace debug {

bool drawFont(int x, int y, const mm::Col4& col, const char* format, ...) {
    char text[0x400];
    va_list args;
    va_start(args, format);
    vsnprintf(text, sizeof(text) - 1, format, args);
    va_end(args);
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->fontShadow(true);
    ok &= cache->fontColor(col);
    ok &= cache->font(x, y, text);
    return ok;
}

bool drawFont(int x, int y, const char* format, ...) {
    char text[0x400];
    va_list args;
    va_start(args, format);
    vsnprintf(text, sizeof(text) - 1, format, args);
    va_end(args);
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->fontShadow(true);
    ok &= cache->font(x, y, text);
    return ok;
}

bool drawFontColor(const mm::Col4& col) {
    return ml::DebDraw::getCacheDraw()->fontColor(col);
}

bool drawLine(const mm::Vec3& start, const mm::Vec3& end, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setMatrix(mm::Mat44::identity);
    ok &= cache->setCol(col);
    ok &= cache->renderLine(start, end);
    return ok;
}

bool drawLine2D(const mm::Pnt<int>& start, const mm::Pnt<int>& end, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setMatrix(mm::Mat44::identity);
    ok &= cache->setCol(col);
    ok &= cache->renderLine(start, end);
    return ok;
}

bool drawSquare2D(const mm::Rect<int>& rect, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setMatrix(mm::Mat44::identity);
    ok &= cache->setCol(col);
    ok &= cache->renderRectFill(rect);
    return ok;
}

bool drawLineSquare2D(const mm::Rect<int>& rect, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setMatrix(mm::Mat44::identity);
    ok &= cache->setCol(col);
    ok &= cache->renderRect(rect);
    return ok;
}

bool drawBoxLine(const mm::Mat44& mtx, const mm::Vec3& size, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setCol(col);
    ok &= cache->setMatrix(mtx);
    mm::Vec3 min = size * -0.5f;
    mm::Vec3 max;
    max.setNeg(min);
    ok &= cache->renderCube(min, max);
    return ok;
}

bool drawSphereLine(const mm::Mat44& mtx, float radius, const mm::Col4& col, unsigned int div) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setMatrix(mtx);
    ok &= cache->setCol(col);
    ok &= cache->renderRealSphere(radius, div);
    return ok;
}

bool drawConeLine(const mm::Mat44& mtx, float radius, float height, const mm::Col4& col, unsigned int div) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setCol(col);
    ok &= cache->setMatrix(mtx);
    ok &= cache->renderCone(radius, height, div);
    return ok;
}

bool drawCylinderLine(const mm::Mat44& mtx, float radius, float height, const mm::Col4& col, unsigned int div) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setCol(col);
    ok &= cache->setMatrix(mtx);
    ok &= cache->renderCylinder(radius, height, div);
    return ok;
}

bool drawCapsuleLine(const mm::Mat44& mtx, float radius, float height, const mm::Col4& col, unsigned int div) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setCol(col);
    ok &= cache->setMatrix(mtx);
    ok &= cache->renderCapsule(radius, height, div);
    return ok;
}

bool drawSquareLine(const mm::Mat44& mtx, float width, float height, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setCol(col);
    ok &= cache->setMatrix(mtx);
    ok &= cache->renderSquare(width, height);
    return ok;
}

bool drawCircleLine(const mm::Mat44& mtx, float radius, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    // setMatrix's result is not kept here, unlike the other draw functions'
    cache->setMatrix(mm::Mat44::identity);
    bool ok = cache->setCol(col);
    ok &= cache->renderCircle(mtx, radius, 16);
    return ok;
}

bool drawAxis(const mm::Mat44& mtx, float length) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setMatrix(mtx);
    ok &= cache->renderAxis(length);
    return ok;
}

bool drawArrow(const mm::Vec3& start, const mm::Vec3& end, const mm::Col4& col) {
    ml::CacheDraw* cache = ml::DebDraw::getCacheDraw();
    bool ok = cache->setCol(col);
    ok &= cache->setMatrix(mm::Mat44::identity);
    ok &= cache->renderArrow(start, end);
    return ok;
}

bool drawCompareZ(bool on) {
    return ml::DebDraw::getCacheDraw()->setZComp(on);
}

}}  // namespace fw::debug

namespace fw {

mm::mtl::RTTI ForceCalculator::m_rtti("ForceCalculator", nullptr, nullptr);

}  // namespace fw

// out of line in the original, this unit's copy kept (ml::DevFileArchiveNx::normalizeFileName calls it)
template mm::mtl::FixStr<256>& mm::mtl::FixStr<256>::insert(int, int, char);
