# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A multithreaded C++ Monte Carlo simulation engine for Counter-Strike weapon cases that calculates ROI data. A Python script fetches case/skin data from the Steam Web API, and the C++ engine simulates case openings to produce statistical results.

## Build & Run

```bash
# Configure and build
cmake -B build
cmake --build build

# Run
./build/case_risk_engine
```

## Data Fetching (Python)

Requires a `.env` file with `STEAMWEBAPI_KEY` set.

```bash
# Fetch case data (edit slug in scripts/fetch.py first)
python scripts/fetch.py
```

Fetched JSON is saved to `data/<slug>.json` (gitignored).

## Architecture

The pipeline flows: fetch → load → simulate → output.

- **`scripts/fetch.py`** — fetches CS case collection data from `steamwebapi.com` and saves to `data/`. The `slug` is currently hardcoded and needs to become a parameter.
- **`include/drop.hpp`** — `Drop` represents a single skin with slug, rarity, wear, price, and StatTrak flag.
- **`include/case.hpp`** — `Case` holds the skin pool organized by rarity. Contains two maps: `rarityToGroupNames` (rarity → list of group names) and `skinGroupToSTPair` (group name → StatTrak/non-ST pairs). `addDrop()` is a stub that needs implementation to populate these structures.
- **`include/simulator.hpp`** — empty stub for the Monte Carlo simulation logic.
- **`include/json.hpp`** — bundled single-header [nlohmann/json](https://github.com/nlohmann/json) for JSON parsing.
- **`src/main.cpp`** — CLI entry point; currently accepts case name input but data loading and simulation calls are not yet wired up.

## RNG Flow (intended design)

Per-opening: determine rarity via weighted roll → pick equally-weighted skin group from `rarityToGroupNames` → look up the `Drop` pair from `skinGroupToSTPair` → roll float/wear and StatTrak flag.
