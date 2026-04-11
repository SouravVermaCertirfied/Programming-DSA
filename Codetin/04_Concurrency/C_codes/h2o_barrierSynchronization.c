/*
1. The H2O Molecule Builder (Barrier Synchronization)The Goal: 
You have two types of threads, Oxygen and Hydrogen. 
Your goal is to group them to form water molecules (H2O).Constraint: 
An oxygen thread must wait for two hydrogen threads, 
and hydrogen threads must wait for one oxygen and another hydrogen.


Challenge: You must ensure that the bond() function is called exactly three times (twice by H, once by O) 
for each molecule before any thread from the next molecule starts bonding.Concepts: Semaphores, Barriers.
*/