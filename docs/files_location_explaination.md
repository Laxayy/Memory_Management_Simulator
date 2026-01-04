## `include/` — Interfaces

Contains **header files** that define the interfaces for all major subsystems:
- Memory allocation strategies
- Cache hierarchy
- Virtual memory management
- Statistics tracking

## `source/` — Implementations

Holds the actual **logic and algorithms** behind the simulator:
- Allocation strategies (First Fit, Best Fit, Worst Fit, Buddy)
- Cache access and replacement
- Virtual memory translation and page replacement
- Statistics collection and reporting


## `tests/` — Validation & Correctness

Contains:
- `.txt` files representing **command-driven testcases**
- `.out` files containing **expected outputs**


## `logs/` — Runtime Traces

Stores logs generated during execution:
- Allocation decisions
- Cache hits and misses
- Page faults and replacements


## `docs/` — Documentation

Contains all written explanations:
- `assumptions.md` — design assumptions and simplifications
- `design.md` — system architecture and flow
- `files_location_explanation.md` — project structure overview


## Build & Automation

- **Makefile** handles compilation and linking
- **Shell scripts** automate testing and log generation
