#ifndef CLASSES_GF_GFMENUOBJENVIRONMENTINFO_H
#define CLASSES_GF_GFMENUOBJENVIRONMENTINFO_H

#include "classes/gf/GfMenuObject.h"

namespace gf {
// table 0x7100B61D68
class GfMenuObjEnvironmentInfo : public ::gf::GfMenuObject {
public:
    class ListListener;
    GfMenuObjEnvironmentInfo(unsigned int handle);
    virtual ~GfMenuObjEnvironmentInfo();  // slot 0
    virtual void initialize();  // slot 2
    static void setupScreen(unsigned int handle);  // the weather, cloud, location and time adapters
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    static void open();
    static void close();
    static void enable();   // clears GfMenuFlag 30
    static void disable();  // sets GfMenuFlag 30
};
}  // namespace gf

#endif
