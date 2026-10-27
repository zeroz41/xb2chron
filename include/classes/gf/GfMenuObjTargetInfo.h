#ifndef CLASSES_GF_GFMENUOBJTARGETINFO_H
#define CLASSES_GF_GFMENUOBJTARGETINFO_H

#include "classes/gf/GfMenuObject.h"

#include "gf/MenuOffset.h"

namespace gf { class GfMenuCallContext; }
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B64BD8
class GfMenuObjTargetInfo : public ::gf::GfMenuObject {
public:
    class EnemyListener;
    class OtherListener;
    class SymbolListener;
    struct OpenEnemyParam;
    struct OpenOtherParam;
    struct OpenSymbolParam;
    GfMenuObjTargetInfo(unsigned int handle);
    virtual ~GfMenuObjTargetInfo();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // closes the menu a context opened
    static void close(GfMenuCallContext* context);
    static void openEnemy(GfMenuCallContext* context, const OpenEnemyParam& param);
    static void openOther(GfMenuCallContext* context, const OpenOtherParam& param);
    static void openSymbol(GfMenuCallContext* context, const OpenSymbolParam& param);
    // show or hide the attached objects 0x11 (the whole menu), 0xD (the other root), 0xE (the symbol root)
    static void disp(bool disp);
    static void dispAllOther(bool disp);
    static void dispAllSymbol(bool disp);
};

// what openEnemy shows the enemy menu at (the field names are not the original's)
struct GfMenuObjTargetInfo::OpenEnemyParam {
    GF_OBJ_HANDLE* m_obj;
    MenuOffset m_offset;
};
}  // namespace gf

#endif
