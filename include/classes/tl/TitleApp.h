#ifndef CLASSES_TL_TITLEAPP_H
#define CLASSES_TL_TITLEAPP_H

#include "classes/apps/LauncherApp.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace layer { class LayerBase; }

namespace tl {
// table 0x7100B3FE90; base at 0x760 mm::mtl::PtrSingleton<tl::TitleApp> (WorkUtil::createWork<TitleApp> stores its
// table there and asserts get()==0)
class TitleApp : public ::apps::LauncherApp, public ::mm::mtl::PtrSingleton<TitleApp> {
public:
    TitleApp(const char* name, ml::WorkObj* parent)
        : LauncherApp(name, parent, 10), m_language(0), m_loadLayer(nullptr), m_loadBuffer(nullptr) {}
    virtual ~TitleApp();  // slot 0
    virtual bool wkStandbyLogin();  // slot 14
    virtual bool wkStandbyLogout();  // slot 15
    void now_loading(bool);
    // makes the title application under the desktop unless one exists
    static void execute();

    static const char* m_szTitle;  // "Title": the work's name
    int m_language;  // 0x768 the regional execute()s set it (EN 12, CN 6, TW 11, Korean 7); wkStandbyLogin passes it to the applet (the name is not the original's)
    unsigned char pad_76C[0x4];
    layer::LayerBase* m_loadLayer;  // 0x770 now_loading's memory layer, 1280x720 (the name is not the original's)
    void* m_loadBuffer;  // 0x778 now_loading's buffer from allocator 5 (the name is not the original's)
};

// the regional title entries of main's icon table (_main::s_aIconDef): each makes the title application under its
// own work name like TitleApp::execute. 2.0.0's symbols name the classes and their members; no table or object of
// them exists (the work they make is a TitleApp).
// "Title" again; also sets TitleApplet::s_bGameTypeIra
class TitleAppIra {
public:
    static void execute();
};
// "Title_english", language 12
class TitleAppEN {
public:
    static void execute();
    static const char* m_szTitle;
};
// "Title_cn_simple", language 6
class TitleAppCN {
public:
    static void execute();
    static const char* m_szTitle;
};
// "Title_cn_original", language 11
class TitleAppTW {
public:
    static void execute();
    static const char* m_szTitle;
};
}  // namespace tl

// the Korean title entry of main's icon table ("Title_korean", language 7), new in 3.0.1: nothing names it or its
// class
void fn_710014E2B0();

#endif
