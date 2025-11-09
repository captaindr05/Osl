# Compile both files with custom names
gcc process1.c -o process1
gcc process2.c -o process2

🧩 Run Order (very important)

➡️ Step 1: Open two terminals side by side.
➡️ In Terminal 1, start the receiver/analyzer first:

./process2

➡️ In Terminal 2, run the sender:

./process1



Terminal 2 (process1)

Enter sentence:
Operating system lab is fun!

--- Result from Process 2 ---
Characters: 30
Words: 5
Lines: 1

