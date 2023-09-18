Do writers need to take lock while operating inside the critical section?
=============================================================================

Locks are required in case of writers using RCU to avoid another writer concurrently entering critical section
