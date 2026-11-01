#ifndef MOVIE_DECODER_H
#define MOVIE_DECODER_H

// NintendoSDK's movie library (namespace movie, imported from the SDK's module): only what the sample player the
// game carries (MovieDecoderPlayer) reaches.

namespace movie {

// a decoder's data buffer, 0x30 bytes (std::vector<movie::Buffer> steps by 0x30); copied and destroyed by the
// library's own constructor and destructor
class Buffer {
public:
    Buffer(const Buffer&);
    ~Buffer();

    unsigned char pad_0[0x30];
};

class Decoder;

}  // namespace movie

#endif
