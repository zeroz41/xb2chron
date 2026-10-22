#ifndef CLASSES_GF_GFMENUOBJMOVIELAYER_H
#define CLASSES_GF_GFMENUOBJMOVIELAYER_H

#include "classes/gf/GfMenuObject.h"
#include "classes/ui/UIScreenObject.h"

namespace gf {
// table 0x7100B63818
class GfMenuObjMovieLayer : public ::gf::GfMenuObject {
public:
    GfMenuObjMovieLayer(unsigned int handle);
    virtual ~GfMenuObjMovieLayer();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // a screen object for a movie of that size under the attached movie layer (0x7E); its handle, or 0
    static unsigned int createMovieLayer(unsigned int width, unsigned int height,
                                         const ui::UIScreenObject::OnMemoryInfo& info);
    static unsigned int m_CreatedCount;  // numbers the screen objects it names
};
}  // namespace gf

#endif
