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
// what openSymbol shows the symbol menu with (the field names are not the original's)
struct GfMenuObjTargetInfo::OpenSymbolParam {
    // inline: openOther's zeroing stores are its (the fields it sets are the ones openOther's code proves)
    OpenSymbolParam() : m_pointBdat(nullptr), m_pointId(0), m_icon(0), m_collect(0) {}
    GF_OBJ_HANDLE* m_obj;
    MenuOffset m_offset;
    unsigned char* m_nameBdat;   // TXT_symbol_name's text, when both are set
    unsigned int m_nameId;
    unsigned char* m_pointBdat;  // TXT_symbol_point_name's text, when both are set and the text is valid
    unsigned int m_pointId;
    unsigned int m_icon;         // IMG_symbol_icon's image; 2 with m_collect on menu layer 3 shows the collect item
    unsigned int m_collect;      // a row of BDAT 0x1E0 (its itm1ID is the item LAY_symbol_collect shows)
};
// what openOther shows the other menu with, or openSymbol when m_symbol is set (the field names are not the
// original's)
struct GfMenuObjTargetInfo::OpenOtherParam {
    GF_OBJ_HANDLE* m_obj;
    MenuOffset m_offset;
    unsigned char* m_nameBdat;  // TXT_other_name's text, when both are set
    unsigned int m_nameId;
    bool m_symbol;
    unsigned int m_shopId;      // the shop TXT_other_shop_name and IMG_other_owner_icon show (OpenSymbolParam::m_icon)
    unsigned char* m_pointBdat;
    unsigned int m_pointId;
    unsigned int m_collect;     // OpenSymbolParam::m_collect on menu layer 3
};
}  // namespace gf

#endif
