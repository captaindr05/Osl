How to Execute on Ubuntu

1️⃣ Compile both files

gcc parent.c -o parent
gcc child.c  -o child

./parent




🧩 To Demonstrate Zombie

1️⃣ Open parent.c.
2️⃣ In the parent block, comment out the wait(NULL); line and add a short sleep:

// wait(NULL);        // comment this line
sleep(20);            // parent sleeps 20 s

gcc parent.c -o parent
./parent
While it pauses 20 seconds, open another terminal and type:

ps aux | grep defunct


You’ll see the child listed as <defunct> → that’s your zombie.
Tell examiner:

“Here child has finished but parent hasn’t waited, so it’s a zombie shown as <defunct>.


🧩 To Demonstrate Orphan

1️⃣ In parent.c, again remove wait(), but this time make parent exit fast,
and in child.c add a sma
ll delay + print parent PID:


