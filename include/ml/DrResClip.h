#ifndef ML_DRRESCLIP_H
#define ML_DRRESCLIP_H

namespace mm { class Vec3; }

namespace ml {
class DrCalcViewWork;
class DrResQueryObj;

// A model's per-frame visibility: clipChk tests the bounding box against the view (inside the box near the camera,
// then the frustum) and then against the occlusion query m_query's last result, holding a result for a few frames.
// clipChk returns true when the model is culled. Field names are not the original's: they say what clipChk does.
class DrResClip {
public:
    DrResClip();
    ~DrResClip();
    bool clipChk(DrCalcViewWork* view, const mm::Vec3& pos, const mm::Vec3& size, float radius, bool noOcc);
    bool clipChkOccOff(DrCalcViewWork* view, const mm::Vec3& pos, float radius);

    enum {
        FLAG_IN_FRUSTUM = 1 << 0,
        FLAG_SKIP0 = 1 << 1,      // FLAG_SKIP0..2: the frames after entering the view skip the query
        FLAG_SKIP1 = 1 << 2,
        FLAG_SKIP2 = 1 << 3,
        FLAG_VISIBLE = 1 << 4,    // the query saw pixels
        FLAG_INIT0 = 1 << 5,      // FLAG_INIT0/1: set by the constructor
        FLAG_INIT1 = 1 << 6,
        FLAG_OUT_FRUSTUM = 1 << 7,
        FLAG_FULL_PIXEL = 1 << 8, // m_pixel is forced to the full count
    };

    DrResQueryObj* m_query;               // 0x00
    unsigned int m_flags;                 // 0x08
    int m_holdCnt;                        // 0x0C: frames FLAG_VISIBLE is kept without pixels
    unsigned int m_pixel;                 // 0x10: the query's pixel count
};
}  // namespace ml

#endif
