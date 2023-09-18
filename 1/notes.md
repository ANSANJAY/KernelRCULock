Read Copy Update / RCU
===========================

Added in Kernel Version 2.5

RCU supports concurrency between a single updater/writer and multiple readers

Often used to update linked lists,which are used all over the kernel.

RCU Can be used in the following scenario:
------------------------------------------

	Lot of Reads

	Rare Writes

	Write should have priority when compared to Read

Problem with Read/Write Locks
---------------------------------

	Expensive (as they use atomic increment/decrement for reader count)

Problem with Seq Locks
----------------------------

	Cannot be used with pointers, only works on basic types like integer etc

	Reader needs to retry the operation

RCU solves the above problem, 

	to have pointer as a shared resource and 
	No locks in the reader
	Avoid reader to retry the operation

Constraints of RCU
---------------------

	Access to shared resource should be mostly read, and very rare write

	Cannot sleep into region protected by RCU

	Protected resource should only be accessed via pointer


Read Operation:
================

	No Locking is required

Write Operation:
=====================

	Locking is required


RCU allows read access to happen concurrently with write updates 

Note: RCU Updaters/writers cannot block readers or force them to retry their accesses like seqlocks.

Linux kernel uses many data structures that are read and updated intensively, especially in

	1. Virtual File System : Directory entry caches (dentry)
	2. Networking	       : Routing Tables. 
				Every outgoing packet requires to check routing table to determine which interface				  should be used.


How it works
================


	As readers do not check if the data they read is consistent(like the seqlock), writer have to
	apply all their changes with one atomical operation.


	RCU keep tracks of all users of the pointers to the shared data structure.

	When a shared data structure is going to change, it 

		first create a copy of the structure
		
		perform the change

		After all the readers have finished reading on the old copy, pointer is updated

Why it is called RCU?
=======================

	When the writing thread needs to be changed, 
		it makes a copy
		changes the copy
		updates the pointer to point to it
	
