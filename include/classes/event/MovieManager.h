#ifndef CLASSES_EVENT_MOVIEMANAGER_H
#define CLASSES_EVENT_MOVIEMANAGER_H

namespace event { enum MSG_TYPE : int; }

namespace event {
// a base of event::MovieManager no evidence names yet
class TUnk_B3D308 {
public:
    virtual ~TUnk_B3D308() {}
    virtual void OnEventProc(event::MSG_TYPE) = 0;
};
// a base of event::MovieManager no evidence names yet
class TUnk_B3D330 {
public:
    virtual ~TUnk_B3D330() {}
};
// table 0x7100B3D308; base at 0x0 unknown (TUnk_B3D308), base at 0x8 unknown (TUnk_B3D330)
class MovieManager : public TUnk_B3D308, public TUnk_B3D330 {
public:
    virtual ~MovieManager() {}  // slot 0
    virtual void OnEventProc(event::MSG_TYPE);  // slot 2
    void clear();
    void update();
    void render();
};
}  // namespace event

#endif
