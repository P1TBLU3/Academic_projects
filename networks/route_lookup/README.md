# Route Lookup – Longest Prefix Match (LPM)

## Overview
This project implements a **route lookup engine** based on the **Longest Prefix Match (LPM)** principle, which is the fundamental algorithm used by routers and switches to decide how to forward IP packets.

Given an IP routing table (prefixes + output interfaces) and a destination IP address, the program determines the **best matching route**, i.e. the route with the **longest prefix length** that matches the destination address.

The implementation is written in **C** and uses a **binary trie (prefix tree)**, closely mirroring how routing lookups are performed in real networking devices.

---

## Motivation and Networking Context

In IP networks (both IPv4 and IPv6), routers maintain a **routing table** with entries of the form:

<network prefix>/<prefix length> → output interface

When a packet arrives, the router must:
1. Compare the destination IP against all known prefixes.
2. Select the route with the **longest matching prefix**.
3. Forward the packet through the corresponding interface.

This operation is performed **millions of times per second** in real routers, so efficient data structures and algorithms are critical.

This project models that exact process and demonstrates:
- How routing tables are represented internally.
- How LPM is implemented efficiently using tries.
- Why a default route (`/0`) is necessary and how it is handled.

---

## Project Structure

- `my_route_lookup.c`  
  Core logic:
  - Construction of the prefix trie.
  - Insertion of routing entries.
  - Route lookup using Longest Prefix Match.
  - Trie compression for efficiency.

- `utils.c / utils.h`  
  Helper functions:
  - IP address parsing and bit manipulation.
  - Utility routines shared across the project.

- `io.c / io.h`  
  Input/output handling:
  - Reading routing tables from files.
  - Reading destination IPs for lookup.

- `routing_table.txt`  
  Example routing table used as input.

- `prueba3.txt`  
  Example destination addresses for testing.

- `Makefile`  
  Build configuration.

---

## Key Concepts Implemented

### Longest Prefix Match (LPM)
- Routes are chosen based on **maximum prefix length**, not on interface number.
- A `/0` prefix acts as a **default route** and must be considered valid.

### Binary Trie (Prefix Tree)
- Each node represents one bit of the IP address.
- Left child → bit `0`
- Right child → bit `1`
- Routes are stored only at nodes corresponding to the full prefix.

### Trie Compression
- Nodes without routing information and with a single child are compressed.
- This reduces memory usage and lookup depth, similar to optimizations used in real routers.

---

## Program Behaviour

1. The routing table is loaded and inserted into a trie.
2. The trie is optionally compressed.
3. For each destination IP:
   - The trie is traversed bit by bit.
   - All matching prefixes are considered.
   - The route with the **longest prefix length** is selected.
4. The selected output interface is printed.

---

## Relevance to Networking

This project directly relates to:
- IP routing and forwarding.
- Control plane vs data plane concepts.
- Router internal data structures.
- Performance considerations in packet forwarding.
- Fundamentals behind routing protocols (OSPF, BGP), which ultimately populate these tables.

It provides a **low-level view** of how abstract routing decisions translate into concrete algorithms and memory structures inside networking equipment.


---

## Build and Run

```bash
make
./my_route_lookup routing_table.txt prueba3.txt
