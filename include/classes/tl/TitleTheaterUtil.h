#ifndef CLASSES_TL_TITLETHEATERUTIL_H
#define CLASSES_TL_TITLETHEATERUTIL_H

namespace gf { class SDataGame; }

namespace tl {
// the event theater's checks (title_theater.cpp, new in 3.0.1); 2.0.0's symbols name the class and these
class TitleTheaterUtil {
public:
    // TitleStateMainScreen::loadSaveDataForTitle calls it on the loaded game: marks the events of 19 quests watched
    // when the quest is ordered (or, for some of them, finished)
    static void setEventPlayFlagByOrderedQuest(gf::SDataGame& game);
    static bool isDefaultWeaponEvent(unsigned int event);
    // GfMenuObjEvTheater::getEvthIDList asks them for each chapter event: when the event needs the saved-event
    // check, isOpenSavedEvent decides whether it is listed
    static bool isNeedCheckSavedEvent(unsigned int event);
    static bool isOpenSavedEvent(unsigned int event);
    // whether the title's save is cleared and the Torna ("ira") save, loaded from slot 22 (or imported), is too
    static bool isCompleteBothGame();
};
}  // namespace tl

#endif
