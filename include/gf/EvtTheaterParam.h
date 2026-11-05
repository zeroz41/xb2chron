#ifndef GF_EVTTHEATERPARAM_H
#define GF_EVTTHEATERPARAM_H

namespace gf {

// 2.0.0's symbols name it (GfManager::startEventTheater and GfPlayFactory::createTheaterEvent take one); the field
// names are not the original's and its size is not recovered (only what those two read is laid out).
struct EvtTheaterParam {
    unsigned short m_eventId;  // startEventTheater's getMapjumpID/getMapJumpPosition/getEventType argument
    unsigned short pad_2;  // createTheaterEvent's third addEvent argument
    unsigned char pad_4[2];
    unsigned char m_weather;  // createTheaterEvent's addEventWeather argument
    unsigned char pad_7;
    // the struct is 4-aligned: createTheaterEvent reads m_eventId and pad_2 for addEvent with one 32-bit load
    // (LLVM's GVN widens the first load only when the alignment allows it); which field brings it is not known
    unsigned int pad_8;
    unsigned char pad_C[3];
    bool pad_F;  // startEventTheater copies it into its map jump's flags
    char pad_10[0x10];  // a text: createTheaterEvent's fourth addEvent argument (its length is not known)
};

}  // namespace gf

#endif
