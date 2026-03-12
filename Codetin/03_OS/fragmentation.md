# Fragmentation

## External Fragmentation:

**This happens when there is enough total free memory, but it's scattered in small, non-contiguous blocks, preventing the system from allocating a large block of memory when required.**

For example, if you free a small chunk of memory, but the free memory space left behind is not large enough to fulfill a subsequent allocation request, even though the total free memory might be enough.

## Internal Fragmentation:

**This happens when the memory allocated is larger than what is actually needed, leaving unused space within the allocated block.**

For example, if you allocate a memory block for an array of 10 integers but the system allocates 20 bytes (because of padding or alignment), you end up with unused memory within the block.