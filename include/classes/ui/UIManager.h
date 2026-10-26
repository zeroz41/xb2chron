#ifndef CLASSES_UI_UIMANAGER_H
#define CLASSES_UI_UIMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/ui/UIGroup.h"
#include "mm/mtl/FixedArray.h"
#include "mm/mtl/FixedVector.h"
#include "mtl/AllocHandle.h"

namespace fw { class UpdateInfo; }
namespace ui { class UIManager; }
namespace ui { class UIGameListener; }
namespace ui { class UIPadRead; }
namespace ui { class UIUpdateCallback; }
namespace ui { struct EventData; }

namespace ui {
// table 0x7100B75678; the menu's UI: the UI managers and libraries it creates, its eight object groups and the
// layers created into them. The field names are not the original's.
class UIManager : public ::mm::mtl::PtrSingleton< ::ui::UIManager> {
public:
    // a created layer (createLayer pushes one, update drops it once its group has no object of it left)
    struct LayerInfo {
        unsigned short m_group;  // the layer row's "group": the index of the group its objects went to
        unsigned short m_id;     // the layer id
    };

    UIManager(const UIPadRead* padRead, mtl::ALLOC_HANDLE handle);
    virtual ~UIManager();  // slot 0
    // the menu's BDAT tables opened again, and the colour, motion and UIO libraries filled from them
    void resetData();
    void update(const fw::UpdateInfo& info);
    void terminate();
    // 1.0.0's symbol (same callers): in 3.0.1 (0x710068F188) a layer id of 100 or more is DLC id / 100's
    // (MNU_Layer_Dlc%02d) and goes to fn_710068F208 only while that DLC is enabled
    bool createLayer(unsigned int id);
    // 1.0.0's isLayerCreated (out of line there, inlined by every 3.0.1 caller): m_layers lists the layer id
    bool isLayerCreated(unsigned int id) {
        for (LayerInfo* it = m_layers.begin(); it != m_layers.end(); ++it) {
            if (it->m_id == id) {
                return true;
            }
        }
        return false;
    }
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's createLayer holds this body).
    // A member because createLayer hands it `this` and it reads m_groups and m_layers. What it does: orders the
    // root objects of the layer row `id` of the layer table `bdat` ("sheet%02d" names, "prio%02d" priorities,
    // "group") from UIObjFactory into the row's group, skipping objects the group has that are not terminating,
    // and lists the layer in m_layers if it is not listed yet; with `force` false a listed layer is left alone.
    // True when the table was there and the layer was (re)created.
    bool fn_710068F208(unsigned char* bdat, unsigned int id, bool force);
    unsigned int searchObject(const char* name, unsigned short group);
    void terminateLayer(unsigned int id, bool release);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_groups and
    // m_layers of the `this` it is passed. What it does: for a listed layer `id` of the layer table `bdat`,
    // terminates (UIGroup::terminateObject, `release` passed on) each of the row's "sheet%02d" objects its group
    // has assigned to that layer (UIGroup::isAssignedLayer).
    void fn_710068F58C(unsigned char* bdat, unsigned int id, bool release);
    void releaseLayer(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it reads m_groups and
    // m_layers of the `this` it is passed. What it does: for a listed layer `id` of the layer table `bdat`,
    // releases (UIGroup::releaseObject) each of the row's "sheet%02d" objects in its group.
    void fn_710068F744(unsigned char* bdat, unsigned int id);
    bool preloadLayer(unsigned int id);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0 has nothing between preloadLayer
    // and terminateObject). A member because its address is among UIManager's functions in its unit. What it
    // does: hands on to UIObjFactory::fn_71006757FC (every preloaded resource released). Its caller is
    // GfMenuManager's fn_71003597B0.
    void fn_710068F958();
    void terminateObject(const char* name, unsigned char group, bool release);
    void requestObjectEvent(unsigned int handle, const EventData& event, float delay);
    void requestGameEvent(unsigned int handle, const EventData& event);
    void setGameEventLisenter(UIGameListener* listener);
    void setUpdateCallback(UIUpdateCallback* callback);
    // a timer for the object of that handle (the time in UI time units, UIUtil::timeSecToUITime's)
    void registObjectTimer(unsigned int handle, unsigned short id, unsigned long time, bool loop);
    void releaseObjectTimer(unsigned int handle);
    void setDisp(unsigned short group, bool disp);
    bool isLoading() const;  // 1.0.0's symbol at the same place, same body (UIObjFactory::isLoading)
    void reloadText();
    bool isTerminated() const;

    mm::mtl::FixedArray<UIGroup, 8> m_groups;
    mm::mtl::FixedVector<LayerInfo, 64> m_layers;
    unsigned short m_mode;               // 1 from the constructor; nothing in this unit reads it
    const UIPadRead* m_padRead;          // the constructor's
    UIUpdateCallback* m_updateCallback;  // setUpdateCallback's: told before and after update's and apply's
};
}  // namespace ui

#endif
