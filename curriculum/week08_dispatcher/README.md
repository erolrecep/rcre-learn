# Week 8: Station 8 — The Master Dispatcher (Processes, Cores & OS Sympathy)

> *"An operating system is a magnificent orchestra; a great programmer is its conductor."*

---

## 1. The Story: Why Shell Scripts Make Computers Choke
When someone writes a Bash loop to run 1,000 commands in parallel:
```bash
for file in *.dat; do process "$file" & done
```
Their computer suddenly sounds like a jet engine, fans scream, the mouse cursor stutters, and the computer runs out of memory (OOM Crash).

Why?
1. Bash launches a heavy `/bin/sh` shell interpreter for every single job.
2. It launches all 1,000 jobs simultaneously, overwhelming the CPU and RAM.
3. It has no idea whether the computer is running out of memory.

---

## 2. The Metaphor: The Air Traffic Control Tower
Imagine an airport with:
* **4 Long Runways**: High-Power Performance (P) Cores for heavy cargo jets (heavy math jobs).
* **4 Short Runways**: Low-Power Efficiency (E) Cores for light passenger planes (quick I/O jobs).
* **Fuel Tanks (RAM)**: Monitored constantly so planes are never scheduled when fuel is empty!

A **Master Dispatcher** sits in the tower:
1. It bypasses the bureaucracy (`/bin/sh`) and speaks directly to the runway crews (`posix_spawnp`).
2. It listens to the kernel's event loop (`kqueue` on macOS, `epoll` on Linux).
3. If memory pressure rises, it holds planes on the taxiway until space frees up!

---

## 3. Real Systems Connection: `gnew-parallel`
`gnew-parallel` replaces legacy shell scripts with a C23 event reactor:
* Direct `posix_spawnp` execution (zero shell overhead).
* Steers jobs to Apple Silicon Performance vs. Efficiency cores using Mach Quality-of-Service (`QoS`).
* NVML GPU VRAM ledger scheduling to prevent Out-Of-Memory crashes.

---

## 4. Code Sample: Direct Process Execution
```c
#include <stdio.h>
#include <spawn.h>
#include <sys/wait.h>

int run_command_direct(char* const argv[]) {
    pid_t pid;
    // Bypasses /bin/sh overhead!
    int status = posix_spawnp(&pid, argv[0], NULL, NULL, argv, NULL);
    if (status != 0) return -1;

    int exit_code = 0;
    waitpid(pid, &exit_code, 0);
    return exit_code;
}
```

---

## 5. Your Mission: The Job Queue Dispatcher
In `starter.c`, implement a simple multi-job dispatch queue that manages worker slots.
