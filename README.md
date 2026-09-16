# University & Master Projects Archive

This repository gathers **academic projects, labs, and coursework** developed across different years of my **Bachelor’s degree and Master’s program**, recovered from multiple stages and consolidated here into a single technical archive.

The purpose of this repository is to **preserve, organize, and document** the work carried out during my academic training, without implying that all projects share the same level of maturity, complexity, or refactoring.

---

## 📚 Context and scope

* Projects come from **different courses, subjects, and academic stages** (Bachelor and Master).
* They include **labs, assignments, exercises, and small-to-medium projects**.
* In most cases, the code is kept **close to its original state**, with only minimal changes aimed at:

  * improving readability,
  * adding execution instructions,
  * and clarifying context or purpose.

This repository is **not intended to be production-grade software**, but rather a **structured record of technical learning and progression over time**.

---

## 🗂️ Repository organization

Projects are **classified by topic**, regardless of whether they belong to the Bachelor’s degree or the Master’s program.

Each top-level directory groups work related to a specific technical area. Individual projects may contain their own `README.md`, source code, notebooks, reports, datasets, test files, or hardware configuration files.

```text
Academic_projects/
├── communications/
│   ├── dss_ber_simulation/
│   ├── fourier_transform_and_filtering/
│   ├── ofdm_ber_simulation/
│   └── signal_detection/
│
├── embedded_systems/
│   ├── buffer_overflow/
│   ├── stm32_two_player_minigames/
│   └── xmc4500_morse_timing/
│
├── machine_learning/
│   ├── Classification/
│   ├── Linear_and_adaptive_noise_filtering/
│   └── Regression/
│
├── networks/
│   └── route_lookup/
│
└── programming/
    ├── c_user_interface/
    ├── concurrency/
    ├── data_structures_and_algs/
    └── tic_tac_toe/
```

---

## 📡 Communications

Academic work related to **digital communications and signal processing**, mainly developed in MATLAB.

* **[DSSS BER Simulation](./communications/dss_ber_simulation)** — Simulation of a Direct Sequence Spread Spectrum system, including spreading/despreading, noisy-channel transmission, and BER analysis.
* **[Fourier Transform and Filtering](./communications/fourier_transform_and_filtering)** — MATLAB exercises on Fourier-domain analysis, filtering, and audio signal processing.
* **[OFDM BER Simulation](./communications/ofdm_ber_simulation)** — OFDM/QAM simulation over noisy multipath channels, focused on evaluating BER and understanding channel effects.
* **[Signal Detection](./communications/signal_detection)** — Digital communications laboratory exercises covering noise, modulation, constellations, and signal detection techniques.

Some original reports and code comments in this section are written in Spanish.

---

## 🔧 Embedded Systems

Projects focused on **microcontrollers, low-level C programming, hardware interaction, timing, and embedded security**.

* **[Buffer Overflow](./embedded_systems/buffer_overflow)** — Embedded security laboratory on ARM/XMC4500 systems covering stack-based buffer overflows, exploit development, debugging, and mitigations such as MPU protection and stack canaries.
* **[STM32 Two-Player Mini Games](./embedded_systems/stm32_two_player_minigames)** — STM32L152C-Discovery project implementing two small two-player games using the LCD, LEDs, timers, ADC input, and PWM-generated tones.
* **[XMC4500 Morse Timing](./embedded_systems/xmc4500_morse_timing)** — XMC4500 project using SysTick, GPIO, LEDs, and buttons to generate Morse-code sequences and measure timing between user inputs.

---

## 🤖 Machine Learning & Signal Processing

Jupyter-based laboratory work covering **regression, classification, and adaptive signal processing** with Python scientific libraries.

* **[Classification](./machine_learning/Classification)** — Binary classification laboratory using the Breast Cancer Wisconsin dataset and several scikit-learn classifiers, together with standard evaluation techniques such as confusion matrices and ROC/AUC analysis.
* **[Linear and Adaptive Noise Filtering](./machine_learning/Linear_and_adaptive_noise_filtering)** — Notebook exploring linear filtering, Active Noise Cancellation (ANC), and adaptive filtering, including audio examples.
* **[Regression](./machine_learning/Regression)** — Regression laboratory using the Seoul Bike Sharing dataset to estimate hourly bicycle demand from weather and contextual features.

---

## 🌐 Networks

Low-level projects related to **computer networks and packet forwarding algorithms**.

* **[Route Lookup](./networks/route_lookup)** — C implementation of IPv4 route lookup using **Longest Prefix Match (LPM)** and a binary trie, including routing-table parsing, lookup tests, and trie compression.

---

## 💻 Programming

General programming coursework covering **C, Java, object-oriented programming, data structures, algorithms, operating-system concepts, and concurrency**.

* **[C User Interface / Process Scheduler](./programming/c_user_interface)** — Linux/POSIX C project with an interactive process-management interface and a simple round-robin-style scheduler using processes, signals, and IPC-related mechanisms.
* **[Concurrency](./programming/concurrency)** — Java multithreading simulation in which alchemists and dragons share constrained areas of a dungeon, with synchronization implemented using semaphores.
* **[Data Structures and Algorithms](./programming/data_structures_and_algs)** — Java implementations and exercises covering stacks, queues, deques, linked lists, trees, binary search trees, searching, sorting, recursion, and basic OOP concepts.
* **[Tic-Tac-Toe](./programming/tic_tac_toe)** — Early Java console project implementing a complete two-player Tic-Tac-Toe game, including turn management, input validation, and win/draw detection.

---

## 📝 Notes

Because these projects were developed at different stages of my studies, their structure, naming conventions, documentation, and coding style may vary. Some files have been preserved almost exactly as they were originally submitted in order to keep the repository representative of the work produced at that time.

Where available, project-specific README files provide additional context, build instructions, requirements, and implementation details.
