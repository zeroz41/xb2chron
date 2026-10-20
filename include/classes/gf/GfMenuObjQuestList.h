#ifndef CLASSES_GF_GFMENUOBJQUESTLIST_H
#define CLASSES_GF_GFMENUOBJQUESTLIST_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B64318
class GfMenuObjQuestList : public ::gf::GfMenuObject {
public:
    class DetailListener;
    class ListListener;
    class MainListener;
    class TabListener;
    class TabOpenListener;
    class TabSelectListener;
    class TaskListener;
    class ThumbListener;
    virtual ~GfMenuObjQuestList();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
