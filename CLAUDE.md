# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A multithreaded C++ Monte Carlo simulation engine for Counter-Strike weapon cases that calculates ROI data. A Python script fetches case/skin data from the Steam Web API, and the C++ engine simulates case openings to produce statistical results.

## Build & Run

```bash
# Configure and build
cmake -B build && cmake --build build

# Run
./build/case_risk_engine
```

## Data Fetching (Python)

Requires a `.env` file with `STEAMWEBAPI_KEY` set. Uses a virtual environment:

```bash
python -m venv venv
source venv/bin/activate
pip install -r requirements.txt

# Fetch case data (edit slug in scripts/fetch.py first)
python scripts/fetch.py
```

Fetched JSON is saved to `data/<slug>.json` (gitignored).

## CLI Commands (runtime)

- `p` — parse and load the hardcoded revolver case JSON into memory
- `s` — run simulation on the loaded case (not yet implemented)
- `q` — quit

## Architecture

The pipeline flows: fetch (Python) → load → simulate → output.

- **`scripts/fetch.py`** — fetches CS case collection data from `steamwebapi.com` and saves to `data/`. The `slug` is currently hardcoded.
- **`include/drop.hpp`** — `Drop` represents a single skin variant with `slug`, `rarity`, `wear`, `price` (pricereal), and `isstattrak`.
- **`include/skingroup.hpp`** — `SkinGroup` represents one skin (e.g. "M4A4 | Royal Paladin") with a `name`, `rarity`, and `vector<Drop>` of all its wear/StatTrak variants.
- **`include/case.hpp`** — `Case` holds `rarityToSkinGroup`: an `unordered_map<string, vector<SkinGroup>>` mapping rarity tier to all skin groups in that tier. `addSkinGroup()` populates it.
- **`include/loader.hpp`** — `loadCase(filepath)` free function. Opens the JSON, iterates `items` (skin groups), reads `groupname` and `tag6` (rarity) at the group level, then iterates `groupitems` to construct `Drop` objects and build each `SkinGroup`. Returns a fully populated `Case`.
- **`include/simulator.hpp`** — empty stub for Monte Carlo simulation logic.
- **`include/json.hpp`** — bundled single-header nlohmann/json for JSON parsing.
- **`src/main.cpp`** — CLI entry point. Holds an `optional<Case> loadedCase` that persists across the input loop.

## Simulation RNG Flow (intended design)

Per-opening: roll rarity via fixed probability weights → pick random `SkinGroup` from `rarityToSkinGroup[rarity]` → pick random `Drop` from `skinGroup.drops` → use `isstattrak` flag for StatTrak handling.

Each thread gets its own `mt19937` RNG seeded independently. The `Case` object is read-only during simulation — no locking needed. Each thread accumulates results locally and merges at the end.
