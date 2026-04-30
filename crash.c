#include <stdio.h>

int main() {
    // We hardcode the exact memory address from your previous run
    int *bad_pointer = (int *)0x000000E36F1FFB0C; 
    
    printf("Attempting a hostile takeover of memory address: %p\n", bad_pointer);
    
    // We try to forcefully write the number 99 into that closed memory sector
    *bad_pointer = 99; 
    
    // If we succeed, this prints. Spoiler: We won't.
    printf("Hostile takeover successful!\n"); 
    return 0;
}