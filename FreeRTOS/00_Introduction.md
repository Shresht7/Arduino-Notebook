# FreeRTOS

FreeRTOS is a real-time operating system that enables multitasking on microcontrollers, allowing you to run multiple tasks concurrently without blocking the execution of other tasks.

FreeRTOS schedules tasks according to their **priority** and **timing requirements**, ensuring that critical operations are executed on time. This is useful for IoT and embedded projects where multiple processes need to run simultaneously, such as reading sensors, controlling actuators, and communicating over Wi-Fi or Bluetooth.

A ***real-time operating system (RTOS)*** is an operating system that guarantees **deterministic behavior** for executing tasks. This means tasks run _predictably_ within a known timeframe, which is crucial for applications where timing matters.

Key features of an RTOS:
- Multitasking: Run multiple tasks "simultaneously" on a single CPU
- Task Priorities: Assign priorities to tasks so critical operations run first.
- Time Management: Control task execution with precise delays and timers.
- Resource Sharing: Use semaphores and mutexes to prevent conflicts between tasks.

> [!NOTE] This is concurrency, not parallelism!

## Why use it?

While the ESP32 is a powerful microcontroller with a dual-core processor, as the complexity of the project grows, the traditional "super loop" approach can quickly become messy and difficult to manage. This is where FreeRTOS comes in. It provides a structured and efficient way to handle **multiple tasks simultaneously**.

### 1. True Multitasking

Run multiple tasks in parallel, such as reading sensors, sending data to the cloud, and updating displays - all without blocking each other.

### 2. Better Code Organization

Separate different functionality into independent tasks instead of putting everything inside a single loop. This makes the code more modular, easier to read and maintain.

### 3. Precise Timing Control

`vTaskDelay()` or timers allow you to control the timing of tasks accurately, without relying on busy loops or blocking `delay()` functions.

### 4. Improved Responsiveness

High-priority tasks (e.g. safety check, interrupts, or critical sensors) can run immediately, while low-priority tasks wait, ensuring time-sensitive operations are never delayed.

### 5. Scalability

As you project grows, adding new features becomes easier. You can simply create new tasks and adjust priorities, without rewriting existing code.


## References

- https://www.freertos.org/
- [DigiKey Electronics FreeRTOS - YouTube](https://www.youtube.com/playlist?list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz)

