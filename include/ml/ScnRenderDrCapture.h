#ifndef ML_SCNRENDERDRCAPTURE_H
#define ML_SCNRENDERDRCAPTURE_H

namespace grlib { class CGLibTextureBuffer; }

namespace ml {
// a capture of a scene renderer into a texture (1.0.0's UIPolygonObject::create draws it; the field's name is not
// the original's)
class ScnRenderDrCapture {
public:
    grlib::CGLibTextureBuffer* m_texture;  // what a UIPolygonObject drawing the capture takes as its texture
};
}  // namespace ml

#endif
