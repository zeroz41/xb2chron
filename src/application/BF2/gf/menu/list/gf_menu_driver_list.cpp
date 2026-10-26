#include "mm/mtl/Vector.h"
#include "classes/ui/UIListInfoBase.h"
#include "classes/ui/UIListInfo.h"
#include "classes/gf/GfMenuDriverList.h"
#include "classes/gf/GfAllocator.h"
#include "gf/GfDataDriver.h"
#include "gf/GfDataParty.h"

namespace gf {

GfMenuDriverList::~GfMenuDriverList() {
    ;  // the original stores the table: its body had a statement the build compiles away
}

GfMenuDriverList* GfMenuDriverList::create() {
#line 44
    GfMenuDriverList* list = new (getAllocator(ALLOCATOR(0)), __FILE__, __LINE__, 8) GfMenuDriverList();
    list->addRef();
    return list;
}

void GfMenuDriverList::fn_7100370618(const IndexSetup& setup) {
    ::ui::UIListInfoBase::SetupParam param = setup.m_param;
    int index = setup.m_index;
    if (index != -1) {
        ::ui::UIListInfo<MenuDriverInfo>::setup(getAllocator(ALLOCATOR(0)), param);
        if (isValid()) {
            MenuDriverInfo info;
            info.m_driver = 0;
            for (unsigned int party = 0; party < 3; party++) {
                unsigned int driver = GfDataParty::getDriver(index, party);
                if (driver != 0 && !GfDataDriver::isActivateUnuse(driver)) {
                    info.m_driver = driver;
                    addContents(info);
                }
            }
        }
    }
}

}  // namespace gf
