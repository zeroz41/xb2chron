#ifndef CLASSES_GF_MENUCOMMONWINDOWPARAM_H
#define CLASSES_GF_MENUCOMMONWINDOWPARAM_H

namespace gf {
// the parameters of a common (message) window, GfMenuManager::openCommonWindow's; 0x50 bytes
// (GfPlayComMenuCommonFromParam::create copies them whole). Its fields are not known yet.
class MenuCommonWindowParam {
public:
    // zeroes every field (GfFieldMapGimmick::create builds one so; the names below are not the original's)
    MenuCommonWindowParam()
        : pad_0(0), pad_8(0), m_bdat(nullptr), m_msgId(0), pad_20(0), pad_28(0), pad_30(0), pad_38(0), pad_40(0),
          pad_48(0) {}
    unsigned long pad_0;
    unsigned int pad_8;
    unsigned char* m_bdat;  // the message table (GfFieldMapGimmick::create: GfDataBdat::getFP(0x1B1))
    unsigned int m_msgId;   // its row (GfFieldMapGimmick::create: the gimmick row's missMSG_ID)
    unsigned long pad_20;
    unsigned int pad_28;
    unsigned long pad_30;
    unsigned long pad_38;
    unsigned long pad_40;
    unsigned int pad_48;
};
}  // namespace gf

#endif
