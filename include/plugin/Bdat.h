#ifndef PLUGIN_BDAT_H
#define PLUGIN_BDAT_H

// a BDAT table in memory: its members by name, its rows by id
class Bdat {
public:
    static unsigned char* getMember(unsigned char* bdat, const char* name);  // null when the table has none
    // 0 when there is no such member (64 bits: 1.0.0's UIManager::createLayer tests bits of it above 16)
    static unsigned long getVal(unsigned char* bdat, const char* name, int id);
};

#endif
