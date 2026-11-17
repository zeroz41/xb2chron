# Contributing

This is a matching decompilation: a function is done when its source compiles to exactly the original's bytes, in
the source file (unit) that owns its address, as a real member of its class, with names backed by evidence.
objdiff's report decides what matches. Use whatever tools you like and send a clean pull request.

## Setup

1. Build the project once: follow [Building](README.md#building) in the README.
2. The commands in this guide are [zkit](https://github.com/zeroz41/zkit-gcnx)'s, which the build installed. Run
   them through the build script, from the repository folder:

   | | `zkit lookup 0x710067A41C` is |
   |---|---|
   | Windows | `py build.py zkit lookup 0x710067A41C` |
   | macOS, Linux | `python3 build.py zkit lookup 0x710067A41C` |

   `zkit doctor` checks your setup and says how to fix anything missing.
3. Get [objdiff](https://github.com/encounter/objdiff/releases) and open the repository folder in it. It shows
   each function next to the original and rebuilds the file when you save.

**Optional: Ghidra.** `zkit decompile <function>` shows Ghidra's decompilation of an original function. It needs
[Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases) 11.3 or newer (with JDK 21), and one run of
the build with `--ghidra` (`python3 build.py --ghidra`, or `py build.py --ghidra` on Windows). Set
`GHIDRA_INSTALL_DIR` to the Ghidra folder unless it is on your `PATH` or in `/opt/ghidra`.

Never commit the game or anything made from it. `rom/`, `orig/`, `build/` and `objdiff.json` are ignored by git
for that reason.

[docs/architecture.md](docs/architecture.md) explains how the repository is organised: units, names, classes,
and the compiler.

## What you can work on

- **Match functions**: write C++ for a function that isn't matched yet, until objdiff reports it exact.
- **Define data**: a unit's tables, strings and variables in source, so its data matches.
- **Link a unit**: once everything in a unit matches, the build uses that unit's compiled code in the rebuilt
  game. `zkit unit --blocked` lists units that match but don't link yet, and what stops them.
- **Fix units**: move functions or data to the unit that really owns them, in `config/XC2_301/splits.txt`, with
  the evidence ([Units](docs/architecture.md#units)).
- **Name things**: real names for functions, classes, members and data, with the evidence in the same change.
- **Clean up matched code**: real types, members and names in place of what a first match left behind, without
  changing a byte ([Checking a change](#checking-a-change)).

## Working on a function

1. **Find its file.** `zkit lookup <address or name>` shows its unit, status, callers and callees; the source file
   is `src/<unit path>`. `zkit unit <unit>` shows the whole unit.
2. **Read the original.** `zkit asm <function>`, and with Ghidra, `zkit decompile <function>`.
3. **Write it** as a member of its class, using the class's header in `include/classes/` and the existing
   declarations of what it calls. Add the fields, static members and return types it needs to the header, named
   on evidence ([Classes](docs/architecture.md#classes)).
4. **Compare.** In objdiff, pick the unit and save. Or from the command line: `zkit compiled <function>` compares
   what is in `src/` with the original, and `zkit try <function> <file>` compiles a separate candidate file the
   same way. (`zkit try` stops after four tries of one function, a guard for AI agents; add `--force` to keep
   going.)
5. **Keep the functions in a file in address order.**

Things the original's source did that yours has to do too:

- **Line numbers.** File names in assertions are already right. Line numbers are not: put `#line <n>` before a
  statement whose `__LINE__` the original prints. In a header, give the path the original printed too:
  `#line <n> "<that path>"`. For example, mm_lib's singleton.h prints as
  `D:/Monolithsoft/BF2/prog/application/BF2//../../libs/mcl/mm_lib/source\mm_mtl/singleton.h`.
- **Local variables change the code.** The original was built with `-g`, and in this compiler that changes
  optimisation. If a near miss differs only in the order of floating-point operations or in which registers it
  uses, try adding or removing a local variable ([Compiler and flags](docs/architecture.md#compiler-and-flags)).
- **The C library is the SDK's.** `include/string.h` and its neighbours declare what the game imports; the
  build never reads your system's headers. Add a declaration there when code needs one.
- **Empty destructors.** A destructor whose code stores its class's table and returns had a statement the build
  compiles away. clang skips the store for an empty body, so write a null statement (`;`) with a comment saying
  so.
- **Unknown fields** stay `pad_<offset>` arrays so the class keeps its layout. A field the code uses gets a name
  from what it demonstrably does (a setter that writes it, an assertion that names it), never `m_<offset>`.

## Checking a change

Before you start, build and save the result as your baseline:

    zkit progress --save

(after `python3 build.py`, or `py build.py` on Windows). Then make your change and run the same check CI runs on
every pull request:

    zkit ci check --base master

It passes only if all of these pass:

- **The build**: it rebuilds the game's executable and checks that it is identical to the original.
- **Nothing lost**: no function, data or unit that matched or linked in your baseline stops matching or
  linking. It compares by address, so renames and moves can't hide a loss.
- **No decompiler leftovers** in the lines you added: raw pointer offsets, hand-mangled names, Ghidra
  temporaries, offset-named members, hand-written vtables, assembly and the like.
- **No files that must not be committed**: game files, build output, scratch files.

`zkit hygiene --since master --only commits` checks your commit messages ([Pull requests](#pull-requests)).

A change that must not change any code, such as a cleanup or a rename, is proven by comparing objects:
`zkit objects --save` before it, then build and `zkit objects --compare` after.

## Rules

- Nothing that matches or links today may stop matching or linking.
- One source file per unit, functions in address order, class declarations in `include/`.
- No assembly. A function that can only be matched with it stays unmatched. (The only `asm` in the tree is the
  undefined instruction `.inst 0xe7ffdefe` that the original stops on.)
- No data from the game beyond what its code needs: no textures, models, sounds, text or other assets.
- Write source, not decompiler output: class members and real types, not raw pointer offsets, `void *`
  parameters, hand-mangled names, decompiler macros or hand-written vtables.
- Comment what the code can't say itself: the evidence for a name, why a statement has an odd shape, what is still
  missing. Never point at files outside the repository.
- Names come from evidence ([Names](#names)). If there is none, keep the placeholder; never guess.
- Code copied or adapted from another project keeps its notices. Add the project to
  [third_party/README.md](third_party/README.md), with its license under `third_party/LICENSES/` if its terms
  require a copy.

## Names

The names in `config/XC2_301/symbols.txt` are the game's original ones, carried over from versions 1.0.0 and 2.0.0
where the code proves them ([Names](docs/architecture.md#names)). A placeholder (`fn_<address>` for a function,
`lbl_<address>` for data) means nothing has proven a name yet.

Evidence that can name something: strings tied to the code, the vtable a constructor installs, `this` passed from
methods with proven names, or the function 1.0.0 had in the same place. Data the symbols leave unnamed can get a
proposed name, with a comment giving its `lbl_<address>`. A rename changes every file that uses the symbol.

## Pull requests

- Keep a pull request to one piece of work, such as one class or one unit, so it is quick to review. A bigger one
  is welcome too when all of it is solid, such as many related functions across several units: say in the
  description what it covers.
- Title it with the result: `Match GfMenuObjOCG`, `Link ui_input_pad.cpp`, `Name the quest task functions`.
- Give the evidence for any unit boundary or name. The [pull request template](.github/pull_request_template.md)
  has a place for it.
- Base it on the current `master`, and run the checks again after rebasing.
- Commit messages are one short line in plain words, under your own name. Pull requests are squash-merged.

## CI

Every pull request is built on the project's own build machine, which has the game's executable, and runs
`zkit ci check` against the commit it starts from. CI then comments the result on the pull request: each check,
and what changed in matched and linked code, data, functions and units. A first-time contributor's pull request
waits for a maintainer to start its run.

When a pull request is merged, the [progress page](https://zeroz41.github.io/xb2chron/), the
[treemap](https://zeroz41.github.io/xb2chron/treemap.html) and the README's badges update by themselves.
