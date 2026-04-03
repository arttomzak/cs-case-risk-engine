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
