# Tasks

In FreeRTOS, **tasks** are like independent functions that run in parallel, each performing a specific job. e.g. Reading sensors, displaying data, transmitting data over WiFi etc.

## Create

You create a **task** using the `xTaskCreate()` or `xTaskCreatePinnedToCore()` function. Each task has:
- A **priority** which determines when and how often it runs compared to other tasks
- A **stack size** which defines how much memory it uses
- A **task function** where you define the task's behaviour.

FreeRTOS uses a **preemptive scheduler** to decide which tasks to run at any given moment. The task with the highest priority is always given CPU time. If two tasks have the same priority, the scheduler will switch between them in a round-robin fashion. This multitasking mechanism allows the ESP32 to handle multiple operations without blocking, making your application smoother and more responsive.

## Delay

The regular `delay()` blocks the CPU completely, stopping all other code from executing. In FreeRTOS, we have `vTaskDelay()` and `vTaskDelayUntil()` functions.

### `vTaskDelay(ticks)`

Suspends the task for a specific number of ticks (usually 1 tick = 1ms on ESP32). While this task is waiting, other tasks are free to run!

### `vTaskDelayUntil()`

Useful when you want tasks to run at a fixed, periodic interval, regardless of when the delay was called. This helps maintain precise timing, especially in sensor sampling or real-time control loops.

## Task States

Each task in FreeRTOS can be in one of several states:
- Running: The task currently using the CPU
- Ready: Task is waiting for CPU time
- Blocked: The task is waiting for a delay or an event (like a semaphore)
- Suspended: The task is paused until resumed
- Deleted: The task is removed from memory

The scheduler constantly checks these states. It only runs tasks that are in the `Ready` state.

## Context Switching

The scheduler performs a **context switch** whenever it changes which task is running. During a context switch, FreeRTOS saves the current task's data and loads the next task's data from memory. This process happens very quickly - usually every few milliseconds. Context switching allows multiple tasks to share the same CPU without interfering with each other. It's what makes FreeRTOS feel truly multitasking.

## Preemptive Scheduling

FreeRTOS uses preemptive scheduling by default. This means a higher priority task can interrupt a lower-priority one at any time. The scheduler instantly switches control to the more important task. This behaviour ensures that time-critical tasks -- like reading sensors or handling WiFi packages -- always gets priority. Lower priority tasks resume automatically once the high-priority work is done.

## Task Priorities

Every task has a priority level. Higher priority means higher importance. The scheduler always runs the highest-priority ready task. Higher as in numerically higher (3 > 1).
