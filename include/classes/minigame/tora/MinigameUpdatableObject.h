#ifndef CLASSES_MINIGAME_TORA_MINIGAMEUPDATABLEOBJECT_H
#define CLASSES_MINIGAME_TORA_MINIGAMEUPDATABLEOBJECT_H

#include "mm/mtl/RTTI.h"
#include "classes/fw/UpdatableObject.h"
#include "classes/minigame/tora/minigame.h"

namespace fw { class UpdateInfo; }
namespace fw { class CommonResource; }
namespace gf { class GfMenuCallContext; }
namespace layer { class LayerBase; }
namespace ui { class UIObjectAcc; }

namespace minigame { namespace tora {
// table 0x7100B72040
class MinigameUpdatableObject : public ::fw::UpdatableObject {
public:
    // inline: 3.0.1 has no out-of-line copy (factory::create holds its stores)
    MinigameUpdatableObject(unsigned int type, const fw::HandlePtr<fw::UpdatableObject>& handle)
        : UpdatableObject(type, handle, 10), m_screen(nullptr), m_layer(nullptr), m_resource(nullptr),
          m_sound(nullptr), m_minigame(nullptr), m_context(nullptr), m_results(nullptr) {}
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~MinigameUpdatableObject();  // slot 1
    virtual void update(fw::UpdateInfo const&);  // slot 4
    // makes the minigame, loads its resources and draws it into the screen's memory layer
    void myinit(ui::UIObjectAcc* acc);
    // opens the next (up to 5) won items' get-item window; false when there are none left
    bool disp_result();
    static mm::mtl::RTTI m_rtti;

    // the field names are not the original's
    ui::UIObjectAcc* m_screen;        // 0xE0: myinit's; the destructor deletes it
    layer::LayerBase* m_layer;        // 0xE8: myinit's memory layer (320x240), the models' textures 0 and 1
    fw::CommonResource* m_resource;   // 0xF0: "minigame/tora.bin"
    fw::SoundResource* m_sound;       // 0xF8: "sound/se/minigame.xsp"
    minigame* m_minigame;             // 0x100
    gf::GfMenuCallContext* m_context; // 0x108: update's, for disp_result's get-item windows
    // 0x110: update's won items; [0] holds the next one to show (m_id) and the end (m_num)
    minigame::ResultItem* m_results;
};
}}  // namespace minigame::tora

namespace ui { class UIObjectAcc; }

namespace minigame { namespace tora { namespace factory {
// a new minigame object on that UI object (registered with fw::UpdatableObjectManager; GfMenuObjMiniGame keeps it)
MinigameUpdatableObject* create(ui::UIObjectAcc* acc);
}}}  // namespace minigame::tora::factory

#endif
