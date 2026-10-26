#ifndef FW_FWDEBUG_H
#define FW_FWDEBUG_H

namespace mm { class Col4; }
namespace mm { class Mat44; }
namespace mm { class Vec3; }
namespace mm { template <typename> class Pnt; }
namespace mm { template <typename> class Rect; }

// the framework's debug drawing (fw::debug; the header's name is not the original's): each call records into
// ml::DebDraw's command cache and returns whether every command fitted
namespace fw { namespace debug {
bool drawFont(int x, int y, const mm::Col4& col, const char* format, ...);
bool drawFont(int x, int y, const char* format, ...);
bool drawFontColor(const mm::Col4& col);
bool drawLine(const mm::Vec3& start, const mm::Vec3& end, const mm::Col4& col);
bool drawLine2D(const mm::Pnt<int>& start, const mm::Pnt<int>& end, const mm::Col4& col);
bool drawSquare2D(const mm::Rect<int>& rect, const mm::Col4& col);
bool drawLineSquare2D(const mm::Rect<int>& rect, const mm::Col4& col);
bool drawBoxLine(const mm::Mat44& mtx, const mm::Vec3& size, const mm::Col4& col);
bool drawSphereLine(const mm::Mat44& mtx, float radius, const mm::Col4& col, unsigned int div);
bool drawConeLine(const mm::Mat44& mtx, float radius, float height, const mm::Col4& col, unsigned int div);
bool drawCylinderLine(const mm::Mat44& mtx, float radius, float height, const mm::Col4& col, unsigned int div);
bool drawCapsuleLine(const mm::Mat44& mtx, float radius, float height, const mm::Col4& col, unsigned int div);
bool drawSquareLine(const mm::Mat44& mtx, float width, float height, const mm::Col4& col);
bool drawCircleLine(const mm::Mat44& mtx, float radius, const mm::Col4& col);
bool drawAxis(const mm::Mat44& mtx, float length);
bool drawArrow(const mm::Vec3& start, const mm::Vec3& end, const mm::Col4& col);
bool drawCompareZ(bool on);  // GfManager::update turns it on each frame
}}  // namespace fw::debug

#endif
