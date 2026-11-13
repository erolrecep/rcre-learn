# rcre-learn: The Silicon Odyssey

<p align="center">
  <strong>A 10-Week Systems Engineering Curriculum & Interactive Web Journey from Raw Silicon to Modern Computer Vision & AI.</strong>
</p>

<p align="center">
  <a href="https://erolrecep.github.io/rcre-learn/"><img src="https://img.shields.io/badge/Demo-Live_Odyssey_App-ff781f?style=flat" alt="Live Odyssey Web App"></a>
  <img src="https://img.shields.io/badge/Language-ISO_C23-00599C?logo=c&style=flat" alt="ISO C23">
  <img src="https://img.shields.io/badge/Sanitizers-ASan_%7C_UBSan_Clean-success?style=flat" alt="Sanitizers Clean">
  <img src="https://img.shields.io/badge/Theme-Warm_Autumn-d4a373?style=flat" alt="Autumn Palette">
  <img src="https://img.shields.io/badge/Audience-High_School_%7C_Beginners-orange?style=flat" alt="Audience">
  <img src="https://img.shields.io/badge/License-MIT-blue?style=flat" alt="License">
</p>

---

## 🌟 What is `rcre-learn`?

Most computer science education teaches students to treat computers as black boxes—stacking heavy abstractions until simple operations consume gigabytes of memory.

**`rcre-learn` teaches systems engineering from first principles.** It takes high school students and non-technical learners on a step-by-step interactive journey into the real-world technologies powering three high-performance systems projects:
1. **`rcre` (Recep's Code Run Everywhere)**: A zero-dependency ISO C23 Computer Vision & Machine Learning engine featuring linear memory arenas, OpenCV bit-exact parity, dynamic hardware abstraction (SIMD), autograd DAGs, and transformers.
2. **`rcvc` (Recep's Computer Vision Code)**: A high-throughput planar imaging engine using Struct-of-Arrays (SoA) planar tiles, 64-byte cache line saturation, and lock-free execution.
3. **`gnew-parallel` (GNew Parallel)**: A high-speed scientific resource orchestrator featuring direct kernel execution (`posix_spawnp`), vector delimiter line splitting at 3+ GiB/s, and Apple Silicon / Linux resource sympathy.

---

## 🗺️ The 10-Week Journey Map

| Week | Station / Realm | Physical Metaphor | Core C23 Concept | Project Connection |
| :--- | :--- | :--- | :--- | :--- |
| **01** | **The Locker Room** | Memory as a hallway of numbered lockers | Variables, Types & Memory Addresses (`&`, `*`) | `rcre` Predictable Byte Footprint |
| **02** | **The Endless Whiteboard** | Erasable whiteboard vs renting hotel rooms | Linear Memory Arenas (`RL_Arena`), 64-byte Alignment | `RCRE_Arena` Zero Heap Allocations |
| **03** | **The Digital Mosaic** | Grid of colored flashlights | 2D Arrays & 15-bit Fixed-Point Color Spaces | `rcre` OpenCV Bit-Exact Grayscale |
| **04** | **Colored Pencils** | Trays of red pencils vs mixed pencil packs | Struct-of-Arrays (SoA) vs AoS & 64B Cache Lines | `rcvc` Planar Tile Cache Saturation |
| **05** | **The Magic Stencil** | Sliding magnifying glass with cutout weights | 2D Convolutions & Sobel Edge Detection | `rcre` Feature & Motion Detection |
| **06** | **The 8-Lane Highway** | 8-arm robotic stamping press | SIMD Vectors & Dynamic HAL Runtime Dispatch | `rcre_hal` Vector Dispatch Table |
| **07** | **The Stream Laser** | Shining a blacklight over text scrolls | Safe Fat-Pointer Slices (`RL_Slice`, pointer + len) | `gnew-parallel` 3.24 GiB/s Stream Splitter |
| **08** | **The Master Dispatcher** | Airport air traffic control tower | Direct Spawning (`posix_spawnp`), Worker Pools | `gnew-parallel` P/E-Core QoS Sympathy |
| **09** | **Teaching Silicon to Learn** | Pinball machine with self-adjusting ramps | Reverse-Mode Autograd DAGs & Attention Weights | `rcre` Micrograd DAG & NanoGPT |
| **10** | **The Alchemist's Portal** | Magic circle allowing C code to run anywhere | WebAssembly (`.wasm`), FFI & In-Browser Vision | `rcre` Live Web Vision Playground |

---

## 📖 Systems Lexicon & Technical Appendix

New to low-level computing terminology? Check out the comprehensive, beginner-friendly [**Technical Appendix & Glossary (`docs/GLOSSARY.md`)**](docs/GLOSSARY.md) explaining:
* **Sanitizers (ASan, UBSan)**: Compiler X-ray machines catching memory bugs and undefined behavior.
* **Zero-Dependency**: Handcrafted clockwork architectures that run forever without NPM/pip vulnerability drift.
* **SIMD**: 8-arm parallel robotic vector registers (ARM NEON, AVX2, WASM SIMD128).
* **Linear Memory Arenas**: $O(1)$ scratchpad memory buffers with bulk rewind.
* **SoA vs. AoS**: Struct-of-Arrays vs Array-of-Structs cache saturation.
* **Fat-Pointer Slices, Fixed-Point Math, LSB Bit-Exact Parity, Kernel Reactors**, and more.

*(You can also click the **"📖 Systems Lexicon"** button in the top-right header of the web app anytime for an interactive search modal!)*

---

## 🍓 Small-Form-Factor & Edge Computing Guide (RPi 3, RPi 4, RPi 5, Jetson)

Want to run `rcre`, `rcvc`, and `gnew-parallel` on single-board computers or resource-constrained devices?  
Read the complete [**Edge & Resource-Constrained Computing Guide (`docs/RESOURCE_CONSTRAINED_DEVICES.md`)**](docs/RESOURCE_CONSTRAINED_DEVICES.md) covering:
* **Home Edge Cluster Audit**: Benchmarks across Raspberry Pi 5, Pi 4, and Jetson Nano nodes.
* **RPi 3 & Older Devices (1GB RAM)**: Step-by-step compilation commands for 32-bit (`armhf`) and 64-bit (`aarch64`).
* **Memory Tuning**: Why zero-heap arenas (`RCRE_Arena`) and planar tiles (`rcvc`) keep memory usage under 20MB and prevent OOM swap freezes.
* **Browser Access Report**: Compatibility analysis of `rcre-learn` vs. `rcre` playground on embedded SBC browsers.

---

## 🚀 Quick Start

### 1. Run Verification Suite (ASan & UBSan Clean)
```bash
make test    # Runs all 10 weekly test suites
make san     # Compiles and validates under Clang ASan + UBSan
```

### 2. Launch the Interactive Web Odyssey
```bash
make serve   # Launches the web app at http://localhost:8000
```
Open your browser to `http://localhost:8000` to interact with the simulations, visualizers, and code inspector!

---

## 📂 Repository Structure

```
rcre-learn/
├── README.md                      # Syllabus, overview, and quickstart
├── Makefile                       # Automated build, test, and web serve targets
├── include/
│   └── rcre_learn.h               # Zero-dependency C23 systems educational header
├── curriculum/                    # 10 self-contained weekly lessons
│   ├── week01_lockers/            # Variables, types & pointers
│   ├── week02_whiteboard/         # Linear memory arena allocator
│   ├── week03_mosaic/             # 15-bit fixed-point color space
│   ├── week04_pencils/            # SoA vs AoS & CPU cache lines
│   ├── week05_stencil/            # 2D Convolutions & Sobel edges
│   ├── week06_simd/               # Dynamic HAL & vector registers
│   ├── week07_stream/             # Fat-pointer zero-copy text slices
│   ├── week08_dispatcher/         # Process worker pools & core affinity
│   ├── week09_intelligence/       # Autograd DAG & neural learning
│   └── week10_portal/             # WebAssembly FFI & real-time filter
└── web/
    └── index.html                 # Standalone interactive web application
```

---

## 📜 License
MIT License. Open-access educational material designed for students, educators, and systems enthusiasts.
