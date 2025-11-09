gcc producer_consumer.c -lpthread
./a.out





🧠 1. Core Problem — What is Producer–Consumer?

It’s a synchronization problem — multiple processes or threads share a bounded buffer.

Producer: generates data items and puts them in buffer.

Consumer: removes data items and uses them.

Goal: Producers shouldn’t put more items than buffer size (no overflow).
Consumers shouldn’t take from empty buffer (no underflow).

⚙️ 2. What is Synchronization?

It’s the process of controlling access to shared resources (like a buffer or file) when multiple threads run at once.
Without synchronization → race condition (two threads modify data at same time → wrong output).

🧩 3. Tools Used

We use two things:

🔹 Mutex (Mutual Exclusion)

It allows only one thread to enter a critical section at a time.

Example: locking access to shared buffer when inserting/removing.

Think of mutex like a room key — only one thread holds it at once.

🔹 Semaphore

It’s a counter that controls access to a resource.

Two types:

Binary semaphore → behaves like mutex (0 or 1).

Counting semaphore → can have value >1, used to count available resources.

🧮 4. Semaphores in Producer–Consumer

We use two counting semaphores:

empty: counts available empty slots in buffer → initial = buffer size.

full: counts number of filled slots → initial = 0.

Also 1 mutex to protect buffer access.

🔄 5. Working Logic
Operation	Sequence
Producer	wait(empty) → lock(mutex) → add item → unlock(mutex) → post(full)
Consumer	wait(full) → lock(mutex) → remove item → unlock(mutex) → post(empty)
