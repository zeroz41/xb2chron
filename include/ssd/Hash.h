#ifndef SSD_HASH_H
#define SSD_HASH_H

namespace ssd {

// a text's hash (CalcTextHash multiplies the running value by 0x89 and folds in each byte, then adds the byte
// count to the second word); the field names are not the original's
class Hash {
public:
    void Clear() {
        value = 0;
        size = 0;
    }
    // folds size bytes of data into the hash (1.0.0 has it out of line; 3.0.1 keeps no copy)
    void CalcDataHash(const void* data, unsigned int size) {
        const unsigned char* bytes = static_cast<const unsigned char*>(data);
        unsigned int hash = value;
        for (unsigned int i = 0; i < size; i++) {
            hash = hash * 0x89 ^ *bytes++;
        }
        value = hash;
        this->size += size;
    }
    void CalcTextHash(const char* text);
    void CalcTextHash(const char16_t* text);

    unsigned int value;
    unsigned int size;
};

}  // namespace ssd

#endif
