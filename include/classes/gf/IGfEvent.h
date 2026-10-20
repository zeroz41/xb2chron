#ifndef CLASSES_GF_IGFEVENT_H
#define CLASSES_GF_IGFEVENT_H

namespace gf { class GF_OBJ_HANDLE; }
namespace gf { class MapjumpCallbackInfo; }
namespace gf { enum EXEC_STATE : int; }
namespace gf { enum GEV : int; }
namespace gf { enum GF_STATE : int; }
namespace gf { enum RELOAD_BDAT : int; }

namespace gf {
// table 0x7100B55698
class IGfEvent {
public:
    virtual ~IGfEvent();  // slot 0
    virtual void vf2();  // slot 2
    virtual void vf3();  // slot 3
    virtual void vf4();  // slot 4
    virtual void vf5();  // slot 5
    virtual void gevPartyMover(gf::GF_OBJ_HANDLE*, bool);  // slot 6
    virtual void vf7();  // slot 7
    virtual void vf8();  // slot 8
    virtual void vf9();  // slot 9
    virtual void vf10();  // slot 10
    virtual void vf11();  // slot 11
    virtual void gevPartyReturnFieldState(unsigned int);  // slot 12
    virtual void vf13();  // slot 13
    virtual void gevGameState(gf::GF_STATE, gf::GF_STATE);  // slot 14
    virtual void vf15();  // slot 15
    virtual void gevChangeLeader(gf::GF_OBJ_HANDLE*);  // slot 16
    virtual void gevSwapFormation(unsigned int, unsigned int);  // slot 17
    virtual void vf18();  // slot 18
    virtual void gevPartyMemberOK(bool);  // slot 19
    virtual void vf20();  // slot 20
    virtual void vf21();  // slot 21
    virtual void vf22();  // slot 22
    virtual void vf23();  // slot 23
    virtual void vf24();  // slot 24
    virtual void vf25();  // slot 25
    virtual void vf26();  // slot 26
    virtual void vf27();  // slot 27
    virtual void vf28();  // slot 28
    virtual void vf29();  // slot 29
    virtual void vf30();  // slot 30
    virtual void vf31();  // slot 31
    virtual void vf32();  // slot 32
    virtual void gevGameObjLeave(gf::GF_OBJ_HANDLE*);  // slot 33
    virtual void vf34();  // slot 34
    virtual void vf35();  // slot 35
    virtual void gevPlayEvent(gf::GEV, unsigned int);  // slot 36
    virtual void gevPause(unsigned int, unsigned int);  // slot 37
    virtual void gevLayerPause(unsigned int, bool);  // slot 38
    virtual void vf39();  // slot 39
    virtual void vf40();  // slot 40
    virtual void vf41();  // slot 41
    virtual void gevMapjump(gf::GEV, gf::MapjumpCallbackInfo const&);  // slot 42
    virtual void gevBattleStart();  // slot 43
    virtual void gevBattleEnd();  // slot 44
    virtual void vf45();  // slot 45
    virtual void vf46();  // slot 46
    virtual void vf47();  // slot 47
    virtual void vf48();  // slot 48
    virtual void vf49();  // slot 49
    virtual void vf50();  // slot 50
    virtual void gevExecState(gf::EXEC_STATE);  // slot 51
    virtual void gevReloadBdat(gf::RELOAD_BDAT, unsigned int);  // slot 52
    virtual void vf53();  // slot 53
    virtual void vf54();  // slot 54
    virtual void vf55();  // slot 55
    virtual void vf56();  // slot 56
    virtual void vf57();  // slot 57
    virtual void vf58();  // slot 58
    virtual void vf59();  // slot 59
    virtual void vf60();  // slot 60
    virtual void vf61();  // slot 61
    virtual void vf62();  // slot 62
};
}  // namespace gf

#endif
