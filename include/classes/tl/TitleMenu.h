#ifndef CLASSES_TL_TITLEMENU_H
#define CLASSES_TL_TITLEMENU_H

namespace gf { class GfMenuCallContext; }

namespace tl {
// The title screen's menus (title, event theater, option) and the call context they report through. TitleMain
// holds one at +0x198 (TitleStateMainScreen::dispTitleMenu passes title + 0x198 to setupTitle). Its size is not
// known: its functions read only +0x8; the title states use +0x0.
class TitleMenu {
public:
    TitleMenu() : m_request(0), m_context(nullptr) {}
    void destroyMenuCallContext();
    void openTitle(bool flag);
    bool isOpenTitle() const;
    void setupTitle();
    bool hasResultSelect() const;
    int getResult() const;
    void closeTitle(bool flag0, bool flag1);
    bool isCloseTitle() const;
    void openEventTheater();
    bool isOpenEventTheater() const;
    void setupEventTheater();
    bool hasResultEventTheater() const;
    // 2.0.0's symbols name it. What it does: false without a context, else the context's isTerm().
    bool isExitEventTheater() const;
    void openOption();
    bool isOpenOption() const;
    void setupOption();
    // 2.0.0's symbols name it. A member for the same reason as isExitEventTheater; same body: false without a context,
    // else isTerm().
    bool isExitOption() const;
    void exitOption();
    int getPlayEventID() const;
    void exitEventTheater();
    void fadeoutEventTheater();

    // TitleStateMainScreen::update reads it (tests for 3) and clears it; TitleStateLoad::update, TitleStateToTitle::update
    // and TitleStateWarning's step clear it (the name is not the original's)
    int m_request;
    unsigned char pad_4[0x4];
    gf::GfMenuCallContext* m_context;  // made on first use, released by destroyMenuCallContext
};
}  // namespace tl

#endif
