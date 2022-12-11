# mc++

A minecraft protocol stack written in C++20.

## Building On Linux with LLVM

**Requirements:**

- LLVM >=15
- libc++
- clang
- lld
- cmake >=3.21
- Boost ASIO
- spdlog
- fmt

```sh
./tools/build.sh
```

You should now be able to find an `mcpp` binary in the `build` folder.
