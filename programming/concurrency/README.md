# Java Concurrency Project – Dungeon Simulation with Semaphores

## Overview

This project is a **final assignment for a Java concurrency course**, where the use of **semaphores was mandatory**.
The goal was to design and implement a **multi-threaded simulation** with complex synchronization constraints, **without using high-level concurrency utilities** (such as monitors, locks, or synchronized blocks).

The scenario models a **Dungeon** inhabited by **Alchemists** and **Dragons**, where access to shared areas is strictly controlled using **counting and binary semaphores**.

The project focuses on:

* Correct **mutual exclusion**
* **Capacity constraints**
* **Directional flow control**
* **Conditional blocking and awakening**
* Avoidance of **deadlocks** and **race conditions**

---

## Scenario Description

The dungeon is composed of several logical areas:

* **Outside**
* **Antechamber**
* **Corridor (Pasillo)**
* **Lair (Guarida)**

Multiple **Alchemist threads** repeatedly attempt to traverse the dungeon, while **Dragon threads** intermittently enter and leave the lair, dynamically changing its capacity.

The system must enforce a set of **non-trivial synchronization rules**, entirely implemented using semaphores.

---

## Main Entities

### `Dungeon`

The `Dungeon` class is the **entry point of the simulation**.

Responsibilities:

* Initializes **all semaphores** used in the system.
* Defines **capacity limits** for each area.
* Creates and launches:

  * Multiple `Alchemist` threads.
  * Three `Dragon` threads (one large dragon and two small ones).
* Ensures all threads share the same synchronization primitives.

This class contains **no logic**, only orchestration and setup.

---

### `Alchemist` (Thread)

Each `Alchemist` represents a worker thread that repeatedly traverses the dungeon.

#### Lifecycle

An alchemist follows a fixed routine:

1. Waits to enter the dungeon (global capacity limit).
2. Enters the **Antechamber** (limited capacity).
3. Forms a **group of three alchemists** before moving forward.
4. Crosses the **Corridor**, respecting:

   * Maximum occupancy.
   * Directional constraints (no crossing in opposite directions).
5. Enters the **Lair**, subject to:

   * Dynamic capacity controlled by dragons.
6. Returns through the same areas in reverse order.
7. Leaves the dungeon.

#### Key Synchronization Concepts

* **Barrier synchronization** to form groups of exactly three alchemists.
* **Directional exclusion** in the corridor using semaphores and shared state.
* **Dynamic blocking** when dragons reduce lair capacity.
* Careful use of **mutex semaphores** to protect shared counters.

The alchemist logic is intentionally complex to stress-test semaphore-based coordination.

---

### `Dragon` (Thread)

Dragons are long-lived threads that **periodically enter and leave the lair**, affecting how many alchemists are allowed inside.

There are three dragons:

* **One large dragon** (`Drogon`)
* **Two small dragons** (`Viserion`, `Rhaegal`)

#### Dragon Behavior

* A dragon attempts to enter the lair.
* Entry may block if:

  * Alchemists are moving in a conflicting direction.
  * Capacity constraints would be violated.
* Once inside, the dragon:

  * Reduces the lair capacity:

    * Large dragon → capacity becomes 0.
    * One small dragon → capacity becomes 10.
    * Two small dragons → capacity becomes 5.
* When leaving, the dragon:

  * Restores or adjusts the lair capacity.
  * Wakes up waiting alchemists using semaphores.

#### Synchronization Features

* Multiple **independent waiting queues**, one per dragon type.
* Explicit control of:

  * Who is waiting.
  * Who is allowed to enter.
* Precise ordering of semaphore releases to avoid lost wake-ups.

Dragons demonstrate **conditional admission**, a classic concurrency challenge.

---

## Concurrency Constraints Enforced

This project enforces all of the following using semaphores only:

* Maximum number of alchemists in the dungeon.
* Maximum number in each area.
* Group formation (exactly 3 alchemists).
* One-direction-at-a-time corridor traversal.
* Dynamic lair capacity depending on dragon presence.
* Fair blocking and awakening of threads.
* No busy waiting.
* No deadlocks.
