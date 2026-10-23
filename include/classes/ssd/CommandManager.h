#ifndef CLASSES_SSD_COMMANDMANAGER_H
#define CLASSES_SSD_COMMANDMANAGER_H

namespace ssd {

// a command the library queues: ExecuteCommands calls slot 2 and then slot 0 (its destructor) on each (the
// name and the slot-2 name are not the original's; no table is identified yet)
class Command {
public:
    virtual ~Command();  // slot 0
    virtual void Execute() = 0;  // slot 2
};

// a list's entry: the command, constructed in the entry's space (0x88 bytes, CommandManager::Init's instance
// size; the name is not the original's)
struct CommandEntry {
    CommandEntry() {}

    Command* command;
    unsigned char pad_8[0x80];
};

// two command lists, one written while the other is executed (the field names are not the original's)
class CommandManager {
public:
    struct List {
        CommandEntry* entries;
        int count;
    };

    void Init(int capacity);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because Init inlines it on
    // its own this. What it does: makes the list other than the one write_ points to the written one (write_),
    // the other the executed one (execute_), and empties the newly written list.
    void fn_71008A22D0();
    void Quit();
    void ExecuteCommands();

    List lists_[2];
    List* write_;
    List* execute_;
    int capacity_;
};

}  // namespace ssd

#endif
