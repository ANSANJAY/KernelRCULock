RCU Terminology:
====================

Quiescent state:	Any code that is not in an RCU read-side critical section


Readers could see stale data if they enter the read-side critical section before the writer finished updating.

Writer has to wait until all the readers drop their references to the stale data or they have entered the quiescent state.

Grace Period:	The above time span is called the grace period

		Grace period ends after all CPUs execute a context switch

				------------------	Context Switch
				|	RCU	 |	    |
				V       Reader   V          V
	CPU0		----------------------------------------


	
					------------------	Context Switch
					|	RCU	 |	    |
					V       Reader   V          V
	CPU1		---------------------------------------------------

					Synchronize_rcu()
						|
						V
	CPU2		---------------------------------------------------------
						|	Grace	      |
						|	Period	      |
						-----------------------
			
	
