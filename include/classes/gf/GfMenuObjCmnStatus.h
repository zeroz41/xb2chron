#ifndef CLASSES_GF_GFMENUOBJCMNSTATUS_H
#define CLASSES_GF_GFMENUOBJCMNSTATUS_H

#include "classes/gf/GfMenuObject.h"

namespace ui { class UISelectObjList; }
namespace ui { class UICtrlRadarGraph; }

namespace gf {
// table 0x7100B612C8; the driver (LAY_status_dr) and blade (LAY_status_bl) status pages, attached under 0x52
class GfMenuObjCmnStatus : public ::gf::GfMenuObject {
public:
    GfMenuObjCmnStatus(unsigned int handle);
    // open (0x21) and close (0x22) the driver's and the blade's pages; open passes its two arguments as the
    // event's first two parameters (the parameter names are not the original's)
    static void openDrStatus(unsigned int param0, int param1);
    static void closeDrStatus();
    static bool swapDrStatus();  // sends 0x102 and returns whether the page is now shown
    static bool isOpenDrStatus();
    static void openBlStatus(unsigned int param0, int param1);
    static void closeBlStatus();
    static bool swapBlStatus();
    static bool isOpenBlStatus();
    static void setInputEnable();
    static void setInputDisable();
    // 2.0.0's symbols name it. What it does: stores its argument there;
    // GfMenuObjLvupSelect::SelectListener::reciveEvent passes true when GfMenuObjUtil::isValidExpansion(3) holds. The
    // driver page then shows TXT_status_dr_index_name_team instead of TXT_status_dr_index_name.
    static void setIraFrontMode(bool disp);
    // the blade page's index and base images: the _sk ones for the ids 2-6, the others otherwise (the parameter
    // name is not the original's; CharStatusListener::reciveEvent passes it for the blade page)
    void updateBladeBase(unsigned int id);
    // the driver page's adapters on the object handle (its parameters, their differences, its blades and its
    // ideas' levels) and m_ideaGraph (the parameter name is not the original's)
    void setDrPageParam(unsigned int handle);
    // 2.0.0's symbols name it. What it does: the Ira driver page's setDrPageParam (TXT_status_dr_index_name_team,
    // GfMenuCharDataAdapter::createFromReferenceDriver; CharStatusListener::reciveEvent)
    void setDrPageParamIra(unsigned int handle);
    // 2.0.0's symbols name them. What they do: the blade page's adapters on the object handle (its parameters and
    // their differences, its weapon, specials, arts, field skills and aux cores); the Ira one is the Ira blade
    // page's version (the parameter name is not the original's)
    void setBlPageParamIra(unsigned int handle);
    void setBlPageParam(unsigned int handle);
    // 2.0.0's symbols name it. What it does: the driver page's version of updateBladeBase: shows LAY_status_dr_index_sk
    // and IMG_status_dr_base_sk for the ids 4 and 5, LAY_status_dr_index and IMG_status_dr_base otherwise; the listener
    // calls it when GfMenuObjUtil::isValidExpansion(3) holds.
    void updateDriverBase(unsigned int id);
    class CharStatusListener;
    class MainListener;
    virtual ~GfMenuObjCmnStatus();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    // whether the driver's [0] and the blade's [1] page is open
    static bool s_DispFlag[2];
    // 2.0.0's symbols name it. Whether the driver page shows the team's name (setIraFrontMode sets it, the constructor
    // and the page's close clear it).
    static bool s_IraFrontMode;
    // the field names are not the original's: the driver's [0] and the blade's [1] parameter lists
    // (CharStatusListener picks LAY_status_dr_param@NN / LAY_status_bl_param@NN into them by its page)
    ui::UISelectObjList* m_paramLists[2];
    ui::UICtrlRadarGraph* m_ideaGraph;  // POL_status_dr_idea_graph's (the name is not the original's)
};
}  // namespace gf

#endif
