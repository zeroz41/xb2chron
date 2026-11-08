#ifndef CLASSES_GF_LOADIRASAVEDATA_H
#define CLASSES_GF_LOADIRASAVEDATA_H

namespace gf {
// reads the Torna ("ira") save into a buffer on its own thread ("LoadIraSaveData");
// GfGameLoad::execDirectImportIraGameWithMicroThread builds one on its stack (data, size none, result -1)
class LoadIraSaveData {
public:
    LoadIraSaveData() : m_data(nullptr), m_size(0), m_result(-1) {}

    int execLoad(void* data, unsigned long size);
    static unsigned int fnThreadLoad(void* argument);
    void loadData();

    // (the member names are not the original's)
    void* m_data;
    unsigned long m_size;
    int m_result;  // what execLoad returns; GfGameLoad keeps it as the file result
};
}  // namespace gf

#endif
