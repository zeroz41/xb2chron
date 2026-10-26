#ifndef CLASSES_GF_MENUCOMMONWINDOWPARAM_H
#define CLASSES_GF_MENUCOMMONWINDOWPARAM_H

namespace gf {
// the parameters of a common (message) window, GfMenuManager::openCommonWindow's; 0x50 bytes
// (GfPlayComMenuCommonFromParam::create copies them whole). GfMenuObjCommonText::open(context, param) sends its four
// texts (each a message table and a row, skipped without a table), m_type, m_select (1 when m_type is 0), pad_44 and
// pad_48 as its open event; open(context, text, value) fills them from a row of table 0xF6 (columns "title",
// "text", "select_ok_txt", "select_cancel_txt", "type", "select"). The names are not the original's.
class MenuCommonWindowParam {
public:
    // zeroes every field (GfFieldMapGimmick::create builds one so)
    MenuCommonWindowParam()
        : m_titleBdat(nullptr), m_titleId(0), m_bdat(nullptr), m_msgId(0), m_okBdat(nullptr), m_okId(0),
          m_cancelBdat(nullptr), m_cancelId(0), m_type(0), m_select(0), pad_44(0), pad_48(0) {}
    unsigned char* m_titleBdat;  // the title's message table
    unsigned int m_titleId;      // its row
    unsigned char* m_bdat;  // the text's message table (GfFieldMapGimmick::create: GfDataBdat::getFP(0x1B1))
    unsigned int m_msgId;   // its row (GfFieldMapGimmick::create: the gimmick row's missMSG_ID)
    unsigned char* m_okBdat;      // the confirm choice's message table
    unsigned int m_okId;          // its row
    unsigned char* m_cancelBdat;  // the cancel choice's message table
    unsigned int m_cancelId;      // its row
    unsigned int m_type;    // column "type" of table 0xF6
    unsigned int m_select;  // column "select" of table 0xF6
    unsigned int pad_44;    // open(context, text, value)'s value; openError's second argument
    unsigned int pad_48;    // openError sets 1
};
}  // namespace gf

#endif
