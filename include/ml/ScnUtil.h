#ifndef ML_SCNUTIL_H
#define ML_SCNUTIL_H

#include "mm/Vec3.h"
#include "mm/Pnt.h"
#include "mm/Rect.h"

namespace ml { class Scn; }
namespace ml { class DebDraw; }
namespace ml { class WinView; }

namespace ml {
// a scene's screen-space helpers
class ScnUtil {
public:
    // the debug drawer's projection from the camera of view (or the default view) and the thread's information
    static bool setPerspective(const Scn* scn, DebDraw* draw, const WinView* view);
    // whether the screen line from start to end (their x and y truncated) touches the rectangle: an end inside it
    // or a crossing with one of its four edges
    static bool checkLineRect(const mm::Vec3& start, const mm::Vec3& end, const mm::Rect<int>& rect);
    // whether the segments a0-a1 and b0-b1 cross
    static bool isCrossLine(const mm::Pnt<int>& a0, const mm::Pnt<int>& a1, const mm::Pnt<int>& b0,
                            const mm::Pnt<int>& b1);
};
}  // namespace ml

#endif
