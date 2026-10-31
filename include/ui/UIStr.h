#ifndef UI_UISTR_H
#define UI_UISTR_H

namespace ui {

// a UI text (0x18 bytes: UIObjectTextPlugin keeps one at 0x80 of its 0x98): a message table's text, a string it
// refers to, or a copy of a string in a buffer of its own (1.0.0's setupMstxt, setupReference, setupAllocated)
class UIStr {
public:
    // what it holds (the names are not the original's: they follow 1.0.0's setup functions)
    enum Type {
        TYPE_NONE,
        TYPE_MSTXT,      // m_file and m_msgId
        TYPE_REFERENCE,  // m_text, not its own
        TYPE_ALLOCATED,  // m_text, in a buffer of m_bufferSize bytes from UIUtil::getProgAllocator
    };
    UIStr();
    UIStr(unsigned char* bdat, unsigned int id);  // the text a message table has at that id
    UIStr(const char* text, bool allocated);  // a text as it is, or a copy (GfMenuGameAdapter passes false)
    UIStr(const UIStr& other);  // out of line: GfMenuStrLinker::addSelectString calls it
    ~UIStr();
    // empty (1.0.0's init; inline in 3.0.1)
    void init() {
        m_type = TYPE_NONE;
        m_ownerId = 0;
        m_bufferSize = 0;
        m_text = nullptr;
    }
    unsigned int size() const;
    bool isValid() const;
    bool compare(const UIStr& other);  // true when they are the same text
    void copy(const UIStr& other);
    void setupMstxt(unsigned char* bdat, unsigned int id);
    // refers to text (1.0.0's setupReference; inline in 3.0.1)
    void setupReference(const char* text) {
        release();
        m_text = text;
        m_type = TYPE_REFERENCE;
    }
    void setupAllocated(const char* text);
    void release();  // frees the text (GfMenuStrLinker::delString)
    const char* c_str() const;
    void allocate(const char* text);  // a copy of text in its own buffer
    void deepcopy(const UIStr& other);  // a copy of the other's text of its own
    unsigned short getStyle() const;  // the font style its text names
    unsigned char* getMsgFP() const;  // the message table of a TYPE_MSTXT text, null otherwise
    unsigned int getMsgID() const;    // the id of a TYPE_MSTXT text, 0 otherwise
    // a message table's text (the names are not the original's)
    struct Mstxt {
        unsigned int m_file;   // its table's handle in UITextManager (registTextFile's)
        unsigned int m_msgId;  // the text's id in the table
    };
    // both set (the tests read the pair as one value, so it is passed by value; the name is not the original's)
    static bool isValidMstxt(Mstxt mstxt) { return mstxt.m_msgId != 0 && mstxt.m_file != 0; }
    union {
        const char* m_text;
        Mstxt m_mstxt;
    };
    unsigned int m_bufferSize;  // TYPE_ALLOCATED: m_text's buffer
    unsigned char pad_0C[4];
    unsigned short m_type;  // Type (1: a message table's text; getMsgID answers only then)
    // what the text belongs to: GfMenuEnhanceAdapter::getEnhanceCaption stores the enhancement's id, copy copies it;
    // the name is not the original's
    unsigned short m_ownerId;
    // 0x14..0x18 is tail padding, not a member: GfMenuStrLinker::getString's static UIStr stays apart from its guard
    // in the original (GlobalMerge skips a global whose type has tail padding: its IR struct is packed)
};

}  // namespace ui

#endif
