#ifndef CLASSES_UI_UIGAMELISTENER_H
#define CLASSES_UI_UIGAMELISTENER_H

namespace ui { struct EventData; }

namespace ui {
// table none (its derived classes'): what UIEventManager::setGameListener takes (1.0.0's signature); it hands the
// listener each game event through slot 0. gf::GfMenuManager is one at 0x18 (GfMenuManager::initialize passes
// that base to UIManager::setGameEventLisenter), the base its header calls TUnk_B5ECD0.
class UIGameListener {
public:
    // slot 0; the name is GfMenuManager's override's (TUnk_B5ECD0's slot)
    virtual void reciveEvent(const EventData& event, unsigned int handle) = 0;
};
}  // namespace ui

#endif
