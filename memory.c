#include <stdio.h>

int main() {
    int secret_key = 42;
    
    // Print the value
    printf("The value is: %d\n", secret_key);
    
    // Print the physical location in RAM
    printf("The memory address is: %p\n", &secret_key);
    
    return 0;
}