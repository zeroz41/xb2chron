# Contributing

This is a matching decompilation: a function counts when the compiled code is byte-identical to the original,
lives in the unit that owns its address, is a real member of its class and is named on evidence. objdiff's report
(`build/XC2_301/report.json`) is the only measure of progress.

## Setup

Follow [Building](README.md#building) in the README. `zkit doctor` checks the setup and says how to fix what is
missing. Never commit the original or anything cut or built from it: `orig/`, `build/` and `objdiff.json` are
ignored.

## Recovering a function

1. Find the unit that owns it: `zkit lookup <address or name>`, `zkit unit <unit>`.
2. Start from Ghidra's reading (`zkit decompile <function>`) and the disassembly (`zkit asm <function>`).
3. Write the function as a member of its class, using the class's header and the shared declarations of what it
   calls. No `extern "C"` bodies on `void *`, raw pointer-plus-offset reads, hand-mangled names, private prototypes
   or hand-written vtables.
4. Check the candidate with `zkit try <function> <file>`. It compiles with the unit's own command and shows the
   differing words. Four attempts per function; past that, stop and leave a note.
5. Only a candidate that is identical and free of decompiler debt goes into `src/<unit path>`. Keep bodies in
   address order inside their unit.
6. `zkit build`, then `zkit progress --since <revision>` shows what changed, by original address.

The full rules are `zkit contract decomp`.

## Names

3.0.1's `main` exports almost nothing, but 1.0.0's exports almost every function and data symbol, and the two are
the same code in the same order. The names in `config/XC2_301/symbols.txt` are 1.0.0's original ones
(Itanium-mangled), carried over where the code proves them; [docs/architecture.md](docs/architecture.md#names-from-100)
says how. A placeholder (`fn_<address>`) is code an update added or changed past what that proves. It stays until
evidence replaces it: strings tied to the code, the vtable a constructor installs, `this` flowing from proven
methods, the function 1.0.0 had in its place. A rename changes every file that spells the symbol.

## Commits

One short line in plain words describing the change, under your own identity, with no co-author trailers. Run
`zkit hygiene` before committing; the git hooks (`zkit install git-hook --write .`) enforce the rest.
