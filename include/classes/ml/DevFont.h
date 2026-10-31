#ifndef CLASSES_ML_DEVFONT_H
#define CLASSES_ML_DEVFONT_H

#include "classes/ml/DevBase.h"
#include "classes/ml/FontLayer.h"
#include "classes/ml/IDevFontInfo.h"
#include "classes/ml/reslist.h"
#include "classes/mm/mtl/PtrSingleton.h"

namespace mm { class Col4; }
namespace ml { class DevFontLayer; }

namespace ml {
// table 0x7100B75AA0; the destructor (inline: 0x71006BD8A8) installs PtrSingleton<DevFont>'s table at 0x1C0 and
// WorkUtil::createWork<DevFontNx> DevBase's at 0x10
class DevFont : public ::ml::FontLayer, public ::ml::DevBase, public ::mm::mtl::PtrSingleton<DevFont> {
public:
    // room for 0x200 children, its DevFontLayers (inline: WorkUtil::createWork<DevFontNx> inlines it)
    DevFont(const char* name, WorkObj* parent) : DevBase(name, parent, 0x200) {}
    virtual ~DevFont() {}  // slot 0
    // WorkObj's overrides: new entries of this (FontLayer's) table in declaration order
    virtual bool wkStandbyLogin();  // slot 2
    virtual bool wkStandbyLogout();  // slot 3
    virtual void wkUpdate();  // slot 4
    virtual void wkTail();  // slot 5
    virtual bool createFont() = 0;  // slot 6
    virtual bool releaseFont() = 0;  // slot 7 (DevFontNx's returns true)

    // the DevFontLayer serving layer: the font's child made for it, else the layer's own (inline; the name is not
    // the original's)
    static DevFontLayer* findFontLayer(const FontLayer* layer);
    // a DevFontLayer serving layer under the font, when the font exists (FontLayer's constructor keeps it,
    // wkStandbyLogin makes one for the font's own layer; inline, the name is not the original's)
    static DevFontLayer* createFontLayer(const FontLayer* layer);
    // marks the DevFontLayer serving layer done (FontLayer's destructor, wkStandbyLogout; inline, the name is not
    // the original's)
    static void doneFontLayer(const FontLayer* layer);
    static void fontLayerStyle(const FontLayer* layer, FONT_STYLE style);
    static void fontLayer(const FontLayer* layer, int x, int y, const char* text);
    static void fontLayerColor(const FontLayer* layer, const mm::Col4& col);
    static void fontLayerShadow(const FontLayer* layer, bool on);
    static void fontLayerFlush(const FontLayer* layer, bool on);
    static void fontLayerScale(const FontLayer* layer, float x, float y);

    // 0x1C8 its entries: wkUpdate calls slot 7 of each, wkStandbyLogout deletes them (the name is not the original's)
    reslist<IDevFontInfo*> m_infos;
};
}  // namespace ml

#endif
