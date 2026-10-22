#include "classes/gf/IDataBdat.h"
#include "classes/gf/GfBdatBgm.h"
#include "plugin/Bdat.h"
#include "classes/gf/GfAllocator.h"
#include "classes/gf/GfDataBdat.h"

namespace gf {
// the BGM tables' column accessors, as 1.0.0's symbols name them: each table member's handle is looked up once (init)
// and a row's value read through it (get)
namespace _gfbbg {
// the column handles the init functions keep (the names are not the original's)
static unsigned char* s_memberBgmListfilename;
static unsigned char* s_memberBgmListNoExchange;
static unsigned char* s_memberBgmConditionConditionA;
static unsigned char* s_memberBgmConditionBgmIDA;
static unsigned char* s_memberBgmConditionConditionB;
static unsigned char* s_memberBgmConditionBgmIDB;
static unsigned char* s_memberBgmConditionConditionC;
static unsigned char* s_memberBgmConditionBgmIDC;
static unsigned char* s_memberBgmConditionConditionD;
static unsigned char* s_memberBgmConditionBgmIDD;
static unsigned char* s_memberBgmConditionPriority;

void initBgmListfilename(const CBdatWrapper& bdat) {
    s_memberBgmListfilename = bdat.getMember("filename");
}

const char* getBgmListfilename(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmListfilename != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (const char*)bdat.getValCheck(s_memberBgmListfilename, id, 7);
    }
    return nullptr;
}

// 3.0.1's column: 1.0.0 has no NoExchange accessors (the name is not the original's)
void initBgmListNoExchange(const CBdatWrapper& bdat) {
    s_memberBgmListNoExchange = bdat.getMember("NoExchange");
}

void initBgmConditionConditionA(const CBdatWrapper& bdat) {
    s_memberBgmConditionConditionA = bdat.getMember("ConditionA");
}

unsigned int getBgmConditionConditionA(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionConditionA != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionConditionA, id, 2);
    }
    return 0;
}

void initBgmConditionBgmIDA(const CBdatWrapper& bdat) {
    s_memberBgmConditionBgmIDA = bdat.getMember("BgmIDA");
}

unsigned int getBgmConditionBgmIDA(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionBgmIDA != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionBgmIDA, id, 2);
    }
    return 0;
}

void initBgmConditionConditionB(const CBdatWrapper& bdat) {
    s_memberBgmConditionConditionB = bdat.getMember("ConditionB");
}

unsigned int getBgmConditionConditionB(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionConditionB != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionConditionB, id, 2);
    }
    return 0;
}

void initBgmConditionBgmIDB(const CBdatWrapper& bdat) {
    s_memberBgmConditionBgmIDB = bdat.getMember("BgmIDB");
}

unsigned int getBgmConditionBgmIDB(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionBgmIDB != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionBgmIDB, id, 2);
    }
    return 0;
}

void initBgmConditionConditionC(const CBdatWrapper& bdat) {
    s_memberBgmConditionConditionC = bdat.getMember("ConditionC");
}

unsigned int getBgmConditionConditionC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionConditionC != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionConditionC, id, 2);
    }
    return 0;
}

void initBgmConditionBgmIDC(const CBdatWrapper& bdat) {
    s_memberBgmConditionBgmIDC = bdat.getMember("BgmIDC");
}

unsigned int getBgmConditionBgmIDC(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionBgmIDC != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionBgmIDC, id, 2);
    }
    return 0;
}

void initBgmConditionConditionD(const CBdatWrapper& bdat) {
    s_memberBgmConditionConditionD = bdat.getMember("ConditionD");
}

unsigned int getBgmConditionConditionD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionConditionD != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionConditionD, id, 2);
    }
    return 0;
}

void initBgmConditionBgmIDD(const CBdatWrapper& bdat) {
    s_memberBgmConditionBgmIDD = bdat.getMember("BgmIDD");
}

unsigned int getBgmConditionBgmIDD(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionBgmIDD != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned short)bdat.getValCheck(s_memberBgmConditionBgmIDD, id, 2);
    }
    return 0;
}

void initBgmConditionPriority(const CBdatWrapper& bdat) {
    s_memberBgmConditionPriority = bdat.getMember("Priority");
}

unsigned int getBgmConditionPriority(const CBdatWrapper& bdat, unsigned int id) {
    if (s_memberBgmConditionPriority != nullptr && bdat.getIdTop() <= id &&
        id < bdat.getIdTop() + bdat.getIdCount()) {
        return (unsigned char)bdat.getValCheck(s_memberBgmConditionPriority, id, 1);
    }
    return 0;
}

}  // namespace _gfbbg

GfBdatBgm::GfBdatBgm() {
    m_fpBgmList = nullptr;
    m_fpBgmCondition = nullptr;
    bdatRefresh();
}

GfBdatBgm::~GfBdatBgm() {
    destroyFP();
}

void GfBdatBgm::destroyFP() {
    if (m_fpBgmList != nullptr) {
        delete m_fpBgmList;
        m_fpBgmList = nullptr;
    }
    if (m_fpBgmCondition != nullptr) {
        delete m_fpBgmCondition;
        m_fpBgmCondition = nullptr;
    }
}

void GfBdatBgm::createFP() {
#line 84
    m_fpBgmList = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xB0));
    m_fpBgmCondition = new (getAllocator(ALLOCATOR(1)), __FILE__, __LINE__, 8) CBdatWrapper(GfDataBdat::getFP(0xB1));
}

void GfBdatBgm::bdatRefresh() {
    destroyFP();
    createFP();
    _gfbbg::initBgmListfilename(*m_fpBgmList);
    _gfbbg::initBgmListNoExchange(*m_fpBgmList);
    _gfbbg::initBgmConditionConditionA(*m_fpBgmCondition);
    _gfbbg::initBgmConditionBgmIDA(*m_fpBgmCondition);
    _gfbbg::initBgmConditionConditionB(*m_fpBgmCondition);
    _gfbbg::initBgmConditionBgmIDB(*m_fpBgmCondition);
    _gfbbg::initBgmConditionConditionC(*m_fpBgmCondition);
    _gfbbg::initBgmConditionBgmIDC(*m_fpBgmCondition);
    _gfbbg::initBgmConditionConditionD(*m_fpBgmCondition);
    _gfbbg::initBgmConditionBgmIDD(*m_fpBgmCondition);
    _gfbbg::initBgmConditionPriority(*m_fpBgmCondition);
}

unsigned int GfBdatBgm::getBgmListStart() const {
    return Bdat::getIdTop(m_fpBgmList->m_fp);
}

unsigned int GfBdatBgm::getBgmListEnd() const {
    return Bdat::getIdTop(m_fpBgmList->m_fp) + Bdat::getIdCount(m_fpBgmList->m_fp);
}

const char* GfBdatBgm::getBgmListfilename(unsigned int id) const {
    return _gfbbg::getBgmListfilename(*m_fpBgmList, id);
}

unsigned int GfBdatBgm::getBgmConditionStart() const {
    return Bdat::getIdTop(m_fpBgmCondition->m_fp);
}

unsigned int GfBdatBgm::getBgmConditionEnd() const {
    return Bdat::getIdTop(m_fpBgmCondition->m_fp) + Bdat::getIdCount(m_fpBgmCondition->m_fp);
}

unsigned int GfBdatBgm::getBgmConditionConditionA(unsigned int id) const {
    return _gfbbg::getBgmConditionConditionA(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionBgmIDA(unsigned int id) const {
    return _gfbbg::getBgmConditionBgmIDA(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionConditionB(unsigned int id) const {
    return _gfbbg::getBgmConditionConditionB(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionBgmIDB(unsigned int id) const {
    return _gfbbg::getBgmConditionBgmIDB(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionConditionC(unsigned int id) const {
    return _gfbbg::getBgmConditionConditionC(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionBgmIDC(unsigned int id) const {
    return _gfbbg::getBgmConditionBgmIDC(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionConditionD(unsigned int id) const {
    return _gfbbg::getBgmConditionConditionD(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionBgmIDD(unsigned int id) const {
    return _gfbbg::getBgmConditionBgmIDD(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionPriority(unsigned int id) const {
    return _gfbbg::getBgmConditionPriority(*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionCondition(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*const s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbg::getBgmConditionConditionA,
        _gfbbg::getBgmConditionConditionB,
        _gfbbg::getBgmConditionConditionC,
        _gfbbg::getBgmConditionConditionD,
    };
    return s_getters[slot](*m_fpBgmCondition, id);
}

unsigned int GfBdatBgm::getBgmConditionBgmID(unsigned int id, unsigned int slot) const {
    // the slots' getters (the name is not the original's)
    static unsigned int (*const s_getters[])(const CBdatWrapper&, unsigned int) = {
        _gfbbg::getBgmConditionBgmIDA,
        _gfbbg::getBgmConditionBgmIDB,
        _gfbbg::getBgmConditionBgmIDC,
        _gfbbg::getBgmConditionBgmIDD,
    };
    return s_getters[slot](*m_fpBgmCondition, id);
}

}  // namespace gf
