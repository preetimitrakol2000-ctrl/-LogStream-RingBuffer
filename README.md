# LogStream-RingBuffer

A low-overhead telemetry processing library written in C99 to defend network gateways against access spikes. It maps streaming connection volumes directly inside a **Circular Ring Buffer**, enabling continuous real-time threshold scoring over rolling time windows.

## ⚡ Performance Layer Strategy
* **Data Structure:** Contiguous Circular Array Queue with index-wrapping logic.
* **Time Complexity:** Constant overhead $O(1)$ telemetry insertion and sliding memory metrics tracking.
