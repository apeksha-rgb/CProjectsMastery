# C File Copy Performance Comparison
![Diagram](./Buffer.png)


This repository contains **two C programs** that copy files, demonstrating **different I/O strategies** and measuring performance:

1. **Chunked Copy** – Reads and writes the file in **small chunks** (default 128 bytes) with optional buffered I/O.
2. **Full RAM Copy** – Reads the **entire file into memory** and writes it in one go.

Both programs measure and display the **time taken** for the copy operation.

---

## Features

- Compare **chunked vs full memory read/write**  
- Optional **buffered I/O** for chunked version (`USE_BUFFERED_IO`)  
- Cross-platform compatible (Linux / Windows)  
- Reports copy duration using high-resolution timers (`clock_gettime`)  

---

## How It Works

### 1. Chunked Copy

- Reads the source file in **small chunks** (`CHUNK_SIZE`)  
- Writes each chunk immediately to the destination  
- Optional buffering reduces disk I/O overhead for large files  
- Useful when file is **too large to fit in RAM**

### 2. Full RAM Copy

- Allocates **one large buffer** for the entire file  
- Reads the whole file at once into memory  
- Writes the entire buffer to the destination in one call  
- Fast for small to medium files, but may fail for very large files due to memory limits

---

## Compile & Run

### Linux / GCC

**Chunked Copy:**
```bash
gcc chunk_copy.c -o chunk_copy -DUSE_BUFFERED_IO
./chunk_copy source_file dest_file
```
**Full RAM Copy:**
```bash
gcc full_copy.c -o full_copy
./full_copy source_file dest_file
```

### Windows / MinGW

**Chunked Copy:**
```bash
gcc chunk_copy.c -o chunk_copy.exe -DUSE_BUFFERED_IO
chunk_copy.exe source_file dest_file
```

**Full RAM Copy:**
```bash
gcc full_copy.c -o full_copy.exe
full_copy.exe source_file dest_file
```
## What You Will Learn / Code Takeaways

- How to perform file I/O in C using fread() and fwrite()

- Differences between chunked read/write vs full memory read/write

- Implementing optional buffered I/O for better performance

- Measuring execution time for file operations using clock_gettime()

- Managing memory allocation for file operations safely

- Understanding performance trade-offs between memory usage and speed