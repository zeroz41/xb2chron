## What this does

<!-- What was matched, defined, linked, named or cleaned up. For a big pull request, list what it covers. -->

## Evidence

<!-- For any name or unit boundary: what in the executable proves it. Delete if there is none. -->

## Checklist

<!-- Run zkit through the build script: `python3 build.py zkit ...`, or `py build.py zkit ...` on Windows. -->

- [ ] `zkit ci check --base master` passes (CI runs it too and comments the result)
- [ ] `zkit hygiene --since master --only commits` is clean
