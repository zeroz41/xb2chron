#ifndef CLASSES_EVENT_TEXTMANAGER_H
#define CLASSES_EVENT_TEXTMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::TextManager no evidence names yet
class TUnk_B3D650 {
public:
    virtual ~TUnk_B3D650();
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::TextManager no evidence names yet
class TUnk_B3D678 {
public:
    virtual ~TUnk_B3D678();
};
// table 0x7100B3D650; base at 0x0 unknown (TUnk_B3D650), base at 0x8 unknown (TUnk_B3D678)
class TextManager : public TUnk_B3D650, public TUnk_B3D678 {
public:
    virtual ~TextManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
};
}  // namespace event

#endif
