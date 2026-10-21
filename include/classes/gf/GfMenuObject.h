#ifndef CLASSES_GF_GFMENUOBJECT_H
#define CLASSES_GF_GFMENUOBJECT_H

namespace gf { class GfMenuCallContext; }
namespace gf { namespace GfMenuTypes { struct Param; }}
namespace ui { struct EventData; }

namespace gf {
// table 0x7100B5EE40
class GfMenuObject {
public:
    GfMenuObject(unsigned int handle);
    virtual ~GfMenuObject();  // slot 0
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    virtual void reloadParam();  // slot 5
    virtual void eventHudSceneChange(unsigned int) {}  // slot 6
    // GfMenuCallManager's: attach a UI object handle under an id, the handle attached under one, a call context
    // started on one
    static void attachExternalCall(unsigned int id, unsigned int handle);
    static unsigned int getAttachedObject(unsigned int id);
    static void startCallContext(GfMenuCallContext* context, unsigned int id, unsigned int handle);
    static void disableInput(unsigned int handle);
    // UIManager::requestObjectEvent for a handle that is not 0
    static void sendEvent(unsigned int handle, const ui::EventData& event, float delay);
    static void closeFSLayer(unsigned int handle, bool, bool);
    static unsigned short getMenuLayerID(unsigned int menuId);  // the menu's layer (1 for none)
    static void changeFSSubLayer(unsigned int handle, unsigned short, unsigned short layer, bool);
    // GfMenuFullScreen's, for a full-screen layer
    static void setFSShadowLayer(unsigned int layer, bool shadow);
    static bool getFSLayerParam(unsigned int layer, GfMenuTypes::Param& param);
    unsigned char pad_8[0x10];
    unsigned int m_handle;  // its UI object's: the constructor's, cleared by finalize
    unsigned char pad_1C[4];
    unsigned int m_fsLayer;  // the full-screen layer it shows in (getFSLayerParam, setFSShadowLayer)
    unsigned char pad_24[4];  // fields: size from its derived classes
};
}  // namespace gf

#endif
