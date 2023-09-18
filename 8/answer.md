When should i free memory?
============================

RCU should free after waiting For Pre-Existing RCU Readers to Complete

RCU waits on "RCU read-side critical sections".

RCU read-side critical sections
-------------------------------

	rcu_read_lock();
	.....
	critical section	
	.....
	rcu_read_unlock();



Basic idea behind RCU is to split updates/write into two phases:

        1. Removal

        2. Reclamation

Removal:

        Replaces references to data items with the latest


Reclamation:

        Freeing the old reference.

        It should happen only when all the readers completed accessing using old reference

