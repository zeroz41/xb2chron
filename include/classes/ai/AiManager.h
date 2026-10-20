#ifndef CLASSES_AI_AIMANAGER_H
#define CLASSES_AI_AIMANAGER_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { namespace IGfObjListener { enum OBJEVT : int; }}

namespace ai {
// a base of ai::AiManager no evidence names yet
class TUnk_B3A360 {
public:
    virtual ~TUnk_B3A360();
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// a base of ai::AiManager no evidence names yet
class TUnk_B3A388 {
public:
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int) = 0;
};
// table 0x7100B3A360; base at 0x0 unknown (TUnk_B3A360), base at 0x8 unknown (TUnk_B3A388)
class AiManager : public TUnk_B3A360, public TUnk_B3A388 {
public:
    virtual ~AiManager();  // slot 0
    virtual void listenerGfObj(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*, unsigned int);  // slot 2
};
}  // namespace ai

#endif
