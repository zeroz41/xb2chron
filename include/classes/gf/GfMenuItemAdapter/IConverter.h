#ifndef CLASSES_GF_GFMENUITEMADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table none (its derived classes')
class GfMenuItemAdapter::IConverter {
public:
    // defined in the adapter's file (3.0.1 emits it after PouchReferenceDriverConverter, 1.0.0 in the same place)
    virtual ~IConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&) = 0;  // slot 2
    // the converter as that kind, or null (the kinds override theirs to return themselves)
    virtual ListConverter* fromList();  // slot 3
    virtual PouchConverter* fromPouch();  // slot 4
    virtual MissionConverter* fromMission();  // slot 5
};
}  // namespace gf

#endif
