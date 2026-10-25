#ifndef CLASSES_MOVIEDECODERPLAYER_H
#define CLASSES_MOVIEDECODERPLAYER_H

// NintendoSDK's movie decoder sample player, as CMovieNX::CMovie drives it. Only the fields the matched code
// reaches are written out; the field names are not the original's.

class AudioOutRenderer {
public:
    void Render();

    unsigned char pad_0[0x9];
    bool m_exit;  // the render thread runs until it is set
    unsigned char pad_a[0x1];
    bool m_started;  // the render thread renders while it is set
    unsigned char pad_c[0x474];
    long m_sleepMs;  // the render thread's wait between frames, in milliseconds
    unsigned char pad_488[0x28];
    bool m_eos;  // isplaying's: the audio has played out
};

class VideoRenderer {
public:
    unsigned char pad_0[0x268];
    bool m_started;  // isstandby's: the first frame is shown
    bool m_eos;  // isplaying's: the video has played out
};

class MovieDecoderPlayer {
public:
    unsigned char pad_0[0x430];
    AudioOutRenderer* m_audioOutRenderer;
    VideoRenderer* m_videoRenderer;
    unsigned char pad_440[0x6F0];
    bool m_done;  // isplaying sets it once audio and video have played out
};

#endif
