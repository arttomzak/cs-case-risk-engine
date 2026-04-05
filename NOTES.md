# C++ Learning Notes

Running notes on C++ concepts encountered while building this project.

---

## `optional<T>`

`std::optional<T>` holds either a value of type `T` or nothing (like a nullable variable).

```cpp
optional<Case> loadedCase;       // empty by default
loadedCase = loadCase("...");    // now holds a Case
if (loadedCase) { ... }          // check if it has a value
loadedCase.value()               // access the value
```

Useful when you have a variable that might not be initialized yet — avoids raw pointers or sentinel values.

---

## Fuzzy String Matching (Levenshtein Distance)

**Planned use:** let users type a case name and match it against known cases from the API.

**Levenshtein distance** = the minimum number of single-character edits (insert, delete, substitute) to turn one string into another. Lower = more similar.

```
"revolv" vs "revolver" → distance 2 (2 inserts)
"reovlver" vs "revolver" → distance 2 (2 substitutions)
```

Classic dynamic programming implementation — build an `(m+1) x (n+1)` matrix where `dp[i][j]` = edit distance between the first `i` chars of `a` and first `j` chars of `b`.

**TODO:** implement this yourself when adding case search to the TUI.

---

## `#pragma once`

Tells the compiler to only include this header file once per compilation unit, even if `#include`d multiple times. Prevents "redefinition" errors.

The traditional equivalent:
```cpp
#ifndef MY_HEADER_HPP
#define MY_HEADER_HPP
// ...
#endif
```

`#pragma once` is one line and does the same thing. Not officially in the C++ standard but supported by all major compilers (GCC, Clang, MSVC).

---
