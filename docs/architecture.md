# Architecture

## The executable

Xenoblade Chronicles 2 ships its code as four modules in the ExeFS. An update replaces the whole ExeFS, so the
3.0.1 update's modules are complete executables; the base game supplies the data, which the update's RomFS
patches. The DLC packs hold data only, so their code is part of 3.0.1's `main` too. This project decompiles
`main`, the game itself; the others are Nintendo's and stay as they are.

| Module | Contents |
|---|---|
| `main` | the game, Monolith Soft's libraries, inlined libc++ templates |
| `sdk` | NintendoSDK 3.5.0: nnSdk, NVN, libz |
| `subsdk0` | NintendoSDK 3.5.0 movie playback |
| `rtld` | the dynamic loader |

`main` (build id `4f5c96e2d97f45ac288bc67613ebef0a`) loads at `0x7100000000`:

| Section | Range |
|---|---|
| `.text` | `0x0000000`–`0x08B4180` |
| `.rodata` | `0x097BA60`–`0x09D93F0` (the game's), and `0x08B5000`–`0x097BA60`, `0x09D93F0`–`0x0B39F23` (the linker's) |
| `.data` | `0x0B3A000`–`0x0B8FDF0` |
| `.bss` | `0x0B8FDF0`–`0x15EE000` |

The read-only segment is mostly the linker's: the dynamic relocations, hash tables, symbols and strings before
the game's constants, and the unwind tables (`.eh_frame_hdr`, `.eh_frame`) after them. The symbols list each in a
section of its own, as a section table would, and no unit owns them.

It calls the SDK through 667 imports and exports only 21 symbols (`nnMain`, the allocator, `operator new` and
`delete`, two `std::vector` instances). Its 35,906 functions come from the unwind table, which clang writes for
every function. It was built without RTTI and without exceptions, so the module names no classes either.

## Names from 1.0.0

1.0.0's `main` exports almost every symbol it defines: 49,128 of its 49,907 functions and 5,221 data objects
(2,845 of them vtables) carry their original mangled names. 3.0.1 is the same code base built with the same
compiler, linked in the same order, but with nothing exported, so the linker also dropped every function nothing
calls. 1.0.0's [symbols](../config/XC2_100/symbols.txt) and [splits](../config/XC2_100/splits.txt) stay in the
repository as the reference build for 3.0.1's names.

zkit's signatures carry the names across. A function's shape is its instructions with every relocated field
cleared, and what each relocation names. A 3.0.1 function takes a 1.0.0 name when the evidence admits only that
one:

- **its shape**, unique among 1.0.0's functions, or confirmed by what it refers to or by its neighbours;
- **a reference**: a matched function's call or address names its target, and a matched constructor's vtable
  names the virtual functions in its slots. Slots pair with 1.0.0's by the code in them, not by index: the updates
  added and removed virtuals, so `gf::DataObjEnemy`'s table kept its length while its slots moved;
- **its place**: between two named functions, the functions in between are 1.0.0's functions in between, less
  what the linker dropped. Copies of one shape pair in order; code that changed pairs one to one, with the
  function it shares by far the most callees, data and strings with, or, in order, with the function whose code
  it is by far the most like (sixteen instructions or more: a short getter whose field moved reads exactly like
  its neighbour did). Code that differs from a sibling only in immediates pairs in order too, never by its exact
  code: the updates added BDAT columns and struct fields, so 3.0.1's `GfBdatItem::getInfoName` reads exactly like
  1.0.0's `getEventName`;
- **a call**: a changed function's one unnamed callee is its 1.0.0 version's one unclaimed callee, and its calls
  pair with its 1.0.0 version's in order: between two calls both name the same function, as many calls on each
  side pair one to one (an update that added a call leaves the counts unequal there). A caller one of whose
  pairings more callers contradict had its calls moved by an update and names nothing in order. A callee whose
  size changed past a third (an update grew it, or moved its constructor out of line) keeps the name only when it
  still shares by far the most of what it refers to with that 1.0.0 function (so does a callee a same-code caller
  or a vtable slot names). Hiding half the callees named by their code, the order named 1,475 of them again in
  each of three draws and 1 or 2 otherwise;
- **a use**: a changed function's other references (data, tables, the functions whose address it takes) pair
  with its 1.0.0 version's the same way, between two that name the same thing. Hiding half the data named by
  same-code references, this named 416 to 433 of them again in each of three draws and one otherwise.

3.0.1 was built from `D:/`, 1.0.0 from `C:/`, so the source paths that assertions cite compare without their
drive letter. The steps that pair changed code were checked against changed functions named independently (by their callers or
their vtable slots) and kept only where they were never wrong. A function's own `__FILE__` names the file it was
compiled in, so no name is taken from a 1.0.0 function that cites only other files, nor a class table's from a
1.0.0 class whose function in some slot cites another file than the function in that slot here (nor that class's
names in its other slots); and a one-call wrapper between two matched functions is not named for its call alone
where the code around it is other code. That withdrew 17 names 1.0.0 gave code an update added in new files: the
classes citing `gf_menu_obj_btl_time.cpp`, `gf_menu_obj_combo_route_simple.cpp` and `gf_menu_btlch_adapter.cpp`
had taken the names of `GfMenuObjButtonChallenge`, `GfMenuObjCommonJog`/`GfMenuObjCommonList` and
`GfMenuBladeDataAdapter`, whose files 3.0.1 no longer cites anywhere (a class renamed with its file has another
name too), and `GfMenuObjSort`'s destructors and a `SaveLoad` listener's had taken `GfMenuObjOpeningTelop`'s and
another listener's. Re-derived from a symbols list of placeholders, 30,358 of the 35,906 functions and 4,218 data
objects take 1.0.0's names this way, each with 1.0.0's binding: 7,824 functions are inlines or template instances
and 1,360 data objects their statics, members and tables (`scope:weak`);
`build/XC2_301/analysis/analysis.json` lists the evidence for each, and
[`config/XC2_301/symbols.txt`](../config/XC2_301/symbols.txt) holds them, with the import stubs and exports the
module names itself. The other 5,406 functions are code an update added, or changed past what the evidence settles.

Every other address the code forms, loads or stores through, and every address a relocated pointer holds, starts
a data object too, named `lbl_<address>` until evidence names it (19,140 still are), sized by what they are (a
string to its NUL, a scalar the code only reads at one width to that width, else up to the next object). Strings
no code or data refers to after a string are objects of their own (1,221 of them): literals of code the linker
dropped (`--gc-sections`), which it kept. `.bss` ends where the module's MOD0 header says (`0x15ED4E0`), not at the
NSO's page-rounded size. To redo
the transfer, with 1.0.0's `main` at `orig/XC2_100/main`, build
1.0.0's signatures and analyze 3.0.1 with `config/XC2_301/symbols.txt` moved aside, so the analysis starts from
the module's own tables and inherits no name:

    zkit signatures build xc2_100 --image orig/XC2_100/main --symbols config/XC2_100/symbols.txt \
        --splits config/XC2_100/splits.txt
    zkit analyze --out build/XC2_301/analysis

## Names from 2.0.0

2.0.0 lies between the two builds, so code an update added after 1.0.0, or changed, often has its 3.0.1 form
there already. Its `main` survives as an IDA Pro 7.0 XML export (`xb2_200.xml` with its `.bytes`, under `rom/`,
not in the repository): 53,101 functions and 5,472 data objects under their original mangled names, and 18,649
more under IDA's placeholders. The export's memory, placed at its addresses, and its function list (the unwind
table is not in the dump, so the function ranges come from the symbols' sizes and IDA's ranges) make a second
donor, `xc2_200`, read by the same signatures as `xc2_100`. Rebuilding that module from an export is not part of
zkit yet.

The 3.0.1 symbols now hold 2,807 function names and 206 data names only 2.0.0 has; for 31,940 functions both
donors give the same name. 2.0.0 also checks and extends what 1.0.0 gave:

- **seeded match** (`zkit signatures match --seeded --donor xc2_200`): with the names already in place as seeds,
  every 3.0.1 function pairs with a 2.0.0 function by its shape, references and place. Where the name differs, the
  declaration was wrong: a `const`, a parameter type, a member of another class, or a `TUnk_<address>` class that
  2.0.0 names (often a listener nested in its menu object). Those were applied in the source unit by unit, each
  unit compiled and compared, losing no match;
- **order**: between two functions both builds name the same, placeholders pair in order with the 2.0.0
  functions 3.0.1's names lack, where the counts, the class and the size (within twice) agree. Hiding names that
  are known, this was wrong 3 times in 24,484, all in gaps holding several pairs; class tables placed by data order
  between named tables were never wrong;
- **sizes**: an object the base symbols cut short at a member's label grows to 2.0.0's size where only labels lie
  inside (`zkit analyze`); 49 grew and took in 455 labels;
- **guards**: a static's initialization guard is named after the object its initializer constructs, which the
  code shows (`_ZGV` and the object's name).

- **copies**: a data name the base symbols carry at two addresses, which the donors place at one of them, is a
  label at the other (`zkit analyze`; `s_jobs` and `s_aArgParam` were such copies).

Where 2.0.0 and 1.0.0 name a class table differently, the code decides. Both times it chose 2.0.0: the table the
tree called `GfMenuMissionAdapter::MissionListConverter` is built by `GfMenuWorldMapAdapter::createFromListWork`
and its third slot is the size of 2.0.0's `ListWorkConverter::getMapId`, not of `getMissionId`; the one called
`GfMenuObjChainCount::MainListener` is installed by `GfMenuObjChainAttack::initialize` and its `reciveEvent` is
the size of 2.0.0's `OverkillListener::reciveEvent`. 1.0.0 has neither class, so its match took the nearest one
with the same slots. With both donors' signatures in the cache, `zkit analyze` uses both.

## Source layout

The game's assertions name their source files, as built on Monolith Soft's machines under
`D:/Monolithsoft/BF2/prog/` for 3.0.1 (`C:/` for 1.0.0; BF2 is the game's internal name). `mm_lib` cites
`C:/MonolithSoft/` in 3.0.1 too: it was linked prebuilt. Units keep that layout, relative to `prog/`:

- `application/BF2/`: the game. `gf/` (game framework: objects, menus, fields, data), `ui/`, `framework/`,
  `battle/`, `execute/`, `minigame/`, `plugin/`.
- `libs/`: Monolith Soft's libraries. `monolib_mm` (`ml`), `mcl/mm_lib` (`mm`: math, containers, threads),
  `anmlib` (animation), `eflib` (effects), `wndlib` (wind), `aiLib`, `skdlib`.

The sound driver (`ssd`) cites a separate tree; its unit is `sources/voice_handle_api.cpp`.

The progress categories (`categories` in [`xc2.project.json`](../xc2.project.json)) follow the libraries, which
the link lays out one after another: NintendoSDK's start-up object, the game, five of `mm_lib`'s files, monolib,
eflib, aiLib, anmlib, skdlib, LibMessageStudio, wndlib, csvb, the sound driver, NintendoSDK's zlib and
`nn::init`, the rest of `mm_lib`, and the PLT. The game also has a category for each of its four largest folders. Units no file names are
assigned by link position and namespace:

- the game: `apps/FrameworkLauncher.cpp` (the first object linked, `apps::` and `ai::AiData`), `ui/` and
  `users/` (`ui::`, after the game's last file `ui/ui_resource.cpp`), `gf/_gfbdb.cpp` and the `unit_` runs
  between the game's own files;
- monolib: `ml/` (monolib's namespace), and `grlib/`, `cloud/`, `layer/`, `Stream.cpp`, `WriteChar.cpp` and
  `WriteStr.cpp`, which link between monolib's `font.cpp` and eflib's first file;
- skdlib: `skt/CommandManager.cpp` (`skd::`, after skdlib's last file);
- NintendoSDK and middleware: `unit_7100000024.cpp` and `unit_71000001B0.cpp` (start-up), the three
  `LMS_*` units (LibMessageStudio), and `unit_71008AC858.cpp` with `nn/gfx/detail/GlslcDll.cpp` (zlib's
  `adler32`, `crc32`, then `nn::init`).

## Units

[`config/XC2_301/splits.txt`](../config/XC2_301/splits.txt) assigns every function, and the data only its code
uses, to one of 637 units: 504 named after a source file (469 after the file their own code cites, 35 after the
file 1.0.0's splits put their functions in), 112 after the class most of their functions belong to, and 21 by
address. A unit named by class or address is code no file string reaches, such as the event system (`event::`,
1,716 functions), monolib's renderer, or files that assert nothing; its name is a placeholder until evidence
names the file. The first, `unit_7100000024.cpp`, is NintendoSDK's start-up object (`_init`, `_fini`), which ends
with the markers the SDK gives its objects (`__nnDetailNintendoSdkRuntimeObjectFile`); the module's start and
end bound the first and last files' reach like any other file's. The evidence, strongest first:

- **first use**: clang compiles an inline function or a template instance (weak in 1.0.0's symbols, and so in
  3.0.1's where the name came from 1.0.0) into every unit whose code still calls it or takes its address, or that
  emits a weak table holding it, right after the code that first refers to it there, and the linker keeps the
  copy of the unit it links first. So a weak function is in the unit of the earliest code referring to it: a
  `PtrSingleton<T>`'s destructors, which only `T`'s constructor and destructor reach through the singleton's
  table, end `T`'s file, not start the next one. A table with a key function is emitted with that function
  alone, and so are the inline virtuals only it holds, so only weak tables count;
- **citations**: a function's own `__FILE__` names its unit, and two functions citing different files are in
  different units, whatever data joins them (a class's static member another file's code reads) and whatever
  1.0.0's units say between them. Where two files' citations interleave (`a.cpp`, `b.cpp`, `a.cpp` again), one
  file includes the other: they are one unit, named after the file citing most, in both builds (eflib's
  `particle_emitter.cpp` and `particle_emitter_manager.cpp`, `particle_system.cpp` and `particle_hash.cpp`,
  monolib's `dev_setting_nx.cpp` and `th_dev_file_nx.cpp`);
- **static initializers**: each unit with static initializers ends with its own initializer (one that tests no
  guard; a guarded one initializes a template's static member and goes with whichever unit came first), so the
  200 entries of `init_array` mark where those units end, and each entry is its unit's data;
- **classes**: 1.0.0's symbol table marks inlines and template instances weak (and so do 3.0.1's names that came
  from it), so a class's other functions are its own, compiled in one file (every one of the 636 classes with a
  citing function cites a single file); within 48 functions of that file's citations, with no function of a class
  citing another file between, they are that file's. A class whose constructor every caller inlined counts too:
  1.0.0's splits put each `gf::GfMove*Controler::update` in the next file (`GfMoveBrakeControler::update` in
  `gf_move_fall.cpp`), since only its `createReflection` cites one;
- **another build**: 1.0.0's splits, where 3.0.1's code says nothing. Where 3.0.1's code states a boundary between
  the same two files, 1.0.0's boundary there yields to it; where 1.0.0 puts a third file between them, it stands.
  Where 3.0.1's code joins a function to another file's (data only that run uses, a weak function and its first
  user), 1.0.0's unit for it yields too: the run is the file its own citations name, else the one 1.0.0 gives most
  of it (`GfMenuObjPartyGauge::GaugeListener::reciveEvent` shares a static with `GfMenuObjPartyGauge::open`, so
  it is `gf_menu_obj_party_gauge.cpp`'s, not `party_status`'s as 1.0.0's splits had it);
- **data**: data only one run of code uses holds the run in one unit, unless what the code states separates it
  (a template's table or an inline's static is shared, kept from whichever unit came first; a class's static
  member its subclasses' initializers refer to spans several units). A static no symbol names holds its users
  together however far apart they are, where no other file's evidence lies between them (the update added
  functions to the BDAT files that only their tables' cache ties to them);
- **reach**: a file's evidence reaches through the data its code shares, over the inlines and template
  instances clang emits after the code that first uses them, and at most 48 functions or 0x8000 bytes past
  that. A longer run tied to neither neighbouring file is neither's, but a unit of its own.

1.0.0's [splits](../config/XC2_100/splits.txt) are this same evidence applied to 1.0.0's `main` (`zkit units
--splits` on a project whose target is 1.0.0), not the original build's: no map of either build exists. In
1.0.0, 1,346 of the 1,349 functions that cite a file lie in that file's unit; the other three are in files
another includes. The units that begin with a weak function (which clang only compiles where a global's
constructor is its first user) are 6 of 678 there (119 of 694 before the first-use rule) and 15 of 637 in 3.0.1
(108 of 642). Two checks measure 3.0.1's units:

- hiding half of 3.0.1's own citations at random (three draws) and proposing units again, 95.1%, 96.6% and 97.5%
  of the hidden functions that land in a cited file's unit land in the file they cite (96.5%, 95.4% and 95.4%
  before the first-use, citation and class rules). They moved none out of the file it cites but where one file
  includes another: the unit takes one of the two names, and a hidden citation of the other counts against it;
- a class's table and static members are its file's (the table goes with the class's first out-of-line
  virtual): of the 758 in 3.0.1 whose file 1.0.0's classes fix, 704 lie in that file's unit, 8 in another and 46
  in none (699, 15 and 46 before).

Compilation also tests suspected boundaries. `AddBlendTree` and the first emitted `AsmState` helpers occupy
`0x7100884D5C`–`0x71008858C4`, before `anm_asm_callback_detector.cpp`. Compiling them together inlines
`CallBackDetector::execute` and `executeStartFrame` into the state notifications, unlike the original's calls.
Compiling them separately reproduces all 20 functions. The blend tree owns its table at `0x7100B81388`; the
callback detector owns the assertion strings at `0x71009B01A1`. `AddBlendTree.cpp` is a class-based placeholder
filename until evidence names the original file.

The link order follows the source paths, sorted case-insensitively by their upper-case spelling within the game
(`ik_lookat_solver.cpp` before `ik_look_solver.cpp`); 19 of the 507 file units step back in that order (20
before), which marks units still misnamed or holding several files (and the start of each library). Inline
functions and template instances take no unit from 1.0.0. 6 files still come out in more than one piece (11
before).

A unit owns one range per section, in link order like its code, and in the game's `.rodata` one per block: the
linker kept one copy of each string and each 4- and 8-byte constant for the whole module, each kind in one block
(the strings at `0x97BA60`, the 4-byte constants at `0x9B50F0`, the 8-byte ones at `0x9B57AC`), each literal the
first unit's that has it, so the units come in link order again in each block, and each unit's other read-only
data (tables) follows from `0x9B5884`, in link order too. A literal is its first user's; a block starts where
the claims' units start over and a cut lets at least half the claims of the smaller side stand in order. 99.6% of
`.bss`, 84% of `.data` and 97% of the game's `.rodata` have a unit (59% before the blocks). Of the 11,700
unnamed literals a unit owns and code uses, 20 are used by an earlier unit (a constant some file defines and
another reads, its name not carried from 1.0.0). Weak data (an inline's static, a template's member or table) is
in every unit using it and the linker keeps the first unit's copy, so it is the first using unit's wherever that
fits the link order of the other claims. The rest is data several units use, which the unit defining it has to
claim, and data no code refers to between two units' ranges. A file whose code the linker dropped keeps its
literals in link order, among them its own path (`__FILE__`) that no code refers to any more: that path is its
file's, which gives 11 files their `.rodata` (`ai_behavior_decorator.cpp`'s strings had sat in
`ai_behavior_root_node.cpp`'s range). Their units link once their source writes the dropped functions back, as
1.0.0 has them.

## Classes

The module has no RTTI, but its virtual tables name nearly every slot (1.0.0's names carried over), and a class's
table says its bases: a base's table is a prefix of its derived class's, every slot the class does not override
holding the base's function, and each further base has a group of its own at the offset of its subobject.
[`include/classes/`](../include/classes) holds one header per class with a table: 2,069 classes and 30 class
templates (for 422 instances), plus 10 classes with no table that only enclose others. Each declares its bases
in layout order and the virtuals it introduces or overrides in slot order, one destructor per destructor pair.

Constructors, destructors and new-expressions prove primary bases the tables cannot: they store the tables of
a class's primary ancestors at the start of the object, in order. That is how every singleton derives from its
`mm::mtl::PtrSingleton<T>`, whose own table holds only destructors, so no table prefix shows it; 593 classes'
primary bases are proven this way (226 by the code alone).

A table's symbol (named from 1.0.0) gives its size, but a size can stop short where an address inside the table
started another object, so its slots are read on while they hold functions, never into another object a
symbol names or code refers to (a label nothing refers to stops nothing): `layer::LayerObj`'s table is followed
by `LayerActBase::s_pCallActEnd`, member function pointers that read like slots and once made `LayerObj` too long
to be the base of the classes deriving from it, and `gf::GfBdatBlade`'s by a table of its column accessors. A
slot also names the function in it: an override has its base slot's name, so where 1.0.0's names put one on the
wrong function (`GfAssetSetupWeapon::getArcFile` and `getEfpFile`), the table decides. So does a destructor no name
says is one: a class keeps its virtual destructor in the two slots where its primary base has it (and a template's
instances where any one has it), and the function only that class's slot holds is its destructor when its code
agrees (it stores the class's table, the deleting one calls the complete one, or the base's own is another
function): 36 of the update's destructors are named so. Checked against 1.0.0, which names every destructor, the
rule named all 3,133 it reaches right. An override no name says is one is the method every named function in its
slot is (a slot keeps one method from the class that declares it down), spelled for its own class where that
spelling demangles to the same method: 68 of the update's functions are named so. 1.0.0's names agree with all
5,502 the rule reaches, and hiding half of the update's named overrides (three draws) it named 1,311, 1,275 and
1,271 of them again and none otherwise.

Compiled with the project's compiler, 2,415 of the 2,435 named tables come out word for word as the original's
(1,000 of them with a destructor the linker folded into its base's identical one, 237 with slots the names do not
reach yet); the 14 headers that do not compile or differ say why at their top. What the tables do
not say stays a placeholder: a base no evidence names (`TUnk_<address>`), a slot no function names
(`vf<slot>`), return types (`void` until code proves one), fields (padding where a derived class's layout proves
a base's size). 55 bases with no table of their own are rebuilt from the slots their derived classes inherit.

The headers are where matching starts, not output to regenerate: fields, static members and return types are
added by hand as functions need them, and a base the tables cannot tell apart is corrected from the constructor
that calls it (`ui::UIObjectPosPlugin` and `UIObjectNumberPlugin` derive from `UIObjectDispPlugin`, whose slots
they all override).

## Toolchain

The code was built with clang 3.9.1, the base of NintendoSDK 3.5.0's compiler. All four modules of 3.0.1 still
carry NintendoSDK 3.5.0's middleware strings, and 28,522 of 3.0.1's functions have the shape of a 1.0.0
function. Seed functions compiled from known source identify the compiler:

- libc++'s `__murmur2_or_cityhash<unsigned long, 64>::__hash_len_0_to_16` is byte-identical under 3.9.1. 4.0.1
  differs by one instruction, and 5.0 and 6.0 by most of the function.
- `mm::mtl::ReservedBitflag` methods match in their prologues only with unwind tables on.

The flags are:

    --target=aarch64-none-elf -mcpu=cortex-a57+fp+simd+crypto+crc -fPIC -O3 -fno-exceptions -fno-rtti
    -fno-strict-aliasing -fno-slp-vectorize -ffunction-sections -fdata-sections -fasynchronous-unwind-tables
    -std=gnu++14 -nostdlibinc

`-O2` and `-O3` produced the same code on every seed so far. `-fno-strict-aliasing` shows in constructors: the
`ui::UIEvent*Condition` ones store a member's initial value, read the plugin they watch and store the member
again, and only without type-based alias analysis does clang keep the first store. Neither did it vectorize
straight-line code: `gf::GfBdatMsg`'s destructor stores its two table pointers as a pair of registers, which
clang's SLP vectorizer turns into one vector store. Each function and object had
a section of its own: the linker dropped single unused functions from files it kept (1.0.0's
`gf::GfMenuStatus::initialize` is gone from 3.0.1, its `build` is not), and a call to a function of the same
file is relocated like any other. `-nostdlibinc` keeps the host's headers out: the C library the game calls is
the SDK's, declared in `include/`.

The game's units were compiled from `D:/Monolithsoft/BF2/prog/`, and the paths their assertions and allocations
cite (`__FILE__`) are that folder plus the unit's path. The build compiles each unit under that name
(`source_root`), so the strings come out the same; a cited line number (`__LINE__`) is the original's when the
statement follows a `#line` directive giving it.

The compiler differs from the stock 3.9.1 release in at least one optimizer rule, which zkit's clang plugins
(`clang_plugins`) put back. Its AArch64 load/store optimizer is from before LLVM commit 173b14db (February
2016): an `add/sub xN, xN, #imm` that starts a block stays unfolded before the `ldr [xN]` that follows it, where
3.9.1 makes one `ldr [xN, #imm]!` (`pre-index-skips-block-start`). Every such pair in the original is in a block
other than the function's entry block: dlmalloc's `mspace_free`, `dispose_chunk` and `try_realloc_chunk`, and
the `this`-adjusting thunk of `gf::GfComBehaviorEnemy::getTransformToSearchPlayer`. Entry blocks still fold:
`idcoli::IDColiPrimitive::calcBoxAaBb` merges its stack allocation into a store.

`xc2.project.json` pins all of this: the original's SHA-1, the compiler archive and its SHA-256, and the flags.
