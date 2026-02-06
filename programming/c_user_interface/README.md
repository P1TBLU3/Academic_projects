# Process Scheduler (C)

Small academic project in C: an interactive menu that lets you manage a set of processes (create, delete, list, sort, save/load) and execute them with a simple round-robin style scheduler.

## Files
- `program.c`: main entry point (menu loop).
- `menu.c/.h`: UI menu and actions.
- `collection.c/.h`: collection (list/array) of processes + scheduling execution.
- `item.c/.h`: process/item structure, creation, printing, comparators.
- `input_usr.c/.h`: user input helpers.
- `proceso.c`: worker process binary (prints a line periodically).
- `stats_process.c`: reads execution stats (from FIFO/pipe defined in the project).

## Build
```bash
make
```

This produces:
- `./program` (main menu)
- `./proceso` (worker)
- `./stats_process` (stats viewer)

## Run
Typically in two terminals:

**Terminal 1**
```bash
./stats_process
```

**Terminal 2**
```bash
./program
```

From the menu you can create processes (with parameters), list/sort them, save/load to file, and execute them.

## Notes
- The code uses POSIX APIs (`fork`, signals, `getline`, etc.). It is intended to run on Linux.
