Do the reader needs to retry the read operation like seqlock when the writer is also in critical section?
=============================================================================================================

Not required. Writer needs to handle this and atomically update the shared resource to the latest 
