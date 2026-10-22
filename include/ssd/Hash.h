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
    void CalcTextHash(const char* text);
    void CalcTextHash(const char16_t* text);

    unsigned int value;
    unsigned int size;
};

}  // namespace ssd

#endif
