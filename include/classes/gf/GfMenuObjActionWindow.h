#ifndef CLASSES_GF_GFMENUOBJACTIONWINDOW_H
#define CLASSES_GF_GFMENUOBJACTIONWINDOW_H

#include "classes/gf/GfMenuObject.h"

namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B5F978
class GfMenuObjActionWindow : public ::gf::GfMenuObject {
public:
    class MainListener;
    struct OpenParam {
        GF_OBJ_HANDLE* m_obj;    // whose action text open shows (-1 for none)
        unsigned int m_button;   // the button whose icon it shows
    };
    GfMenuObjActionWindow(unsigned int handle);
    virtual ~GfMenuObjActionWindow();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    virtual void eventHudSceneChange(unsigned int);  // slot 6
    static void open(const OpenParam& param);
    static void close();
    static void disp(bool disp);
    static void openBattle(const OpenParam& param);
    static void closeBattle();
};
}  // namespace gf

#endif
