# Low Latency Trading Engine (C++)

## Overview
This project is a high-performance, low-latency trading system . It simulates a simplified exchange and trading clients, focusing on deterministic performance, minimal latency, and efficient memory usage.

---

## 🧠 Design Goals

- Ultra-low latency execution
- Predictable performance (no jitter)
- Cache-friendly data structures
- Minimal dynamic memory allocation
- High throughput under load

---


##  Key Optimizations

### 1. Memory Management
- Pre-allocation of data structures
- Avoidance of heap allocations in hot paths
- Object reuse where possible

### 2. Cache Efficiency
- Contiguous memory layouts (`std::array` preferred over `std::vector` in critical paths)
- Avoid pointer chasing
- Struct packing and alignment considerations

### 3. Lock-Free / Low Contention Design
- Minimized locking in critical sections
- Single-threaded matching engine (deterministic execution)
- Message-passing style interactions

### 4. Branch Prediction Optimization
- Reduced unpredictable branches
- Likely/unlikely patterns in critical paths

### 5. Logging Optimization
- Deferred string formatting
- Reduced I/O overhead
- Benchmark-driven improvements

### 6. Compiler Optimizations
- `-O3`, `-march=native`, `-flto`

---

## Benchmarking

Run benchmarks:

```bash
bash scripts/run_benchmarks.sh
```

Benchmarks include:
- Logger performance
- Release vs Debug comparison
- Hash map vs array-based structures

---

##  Build Instructions

### Requirements
- C++20 compatible compiler
- CMake
- Ninja (recommended)

### Build

```bash
bash scripts/build.sh
```

### Run Exchange + Clients

```bash
bash scripts/run_exchange_and_clients.sh
```
---

## Git Hygiene

Ignored files:
- `build/`, `cmake-build-*`
- `.venv/`
- `logs/`, `profiling/`
- `*.log`, `perf.data*`

---

##  Future Improvements

- Kernel bypass networking (DPDK / openOnLoad )
- NUMA-aware memory allocation
- Multi-core scaling strategies
- Persistent order book snapshots

---

