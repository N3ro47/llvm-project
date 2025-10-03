// RUN: %clang -o %t %s && %t | FileCheck %s

#include <stdio.h>

void check_value(int val) {
    defer {
        printf("...cleaning up after check_value.\n");
    };

    if (val < 10) {
        printf("Value is small, returning early.\n");
        return;
    }

    printf("Value is large, returning normally.\n");
}

int main() {
    printf("Start\n");
    // CHECK: Start

    defer { printf("First defer (runs third)\n"); };
    defer { printf("Second defer (runs second)\n"); };
    defer { printf("Third defer (runs first)\n"); };

    printf("End of main body\n");
    // CHECK: End of main body

    printf("\n--- Calling with small value ---\n");
    // CHECK: --- Calling with small value ---
    
    check_value(5);
    // CHECK: Value is small, returning early.
    // CHECK: ...cleaning up after check_value.

    printf("\n--- Calling with large value ---\n");
    // CHECK: --- Calling with large value ---
    
    check_value(20);
    // CHECK: Value is large, returning normally.
    // CHECK: ...cleaning up after check_value.

    // The deferred prints from main happen at the very end.
    // CHECK: Third defer (runs first)
    // CHECK: Second defer (runs second)
    // CHECK: First defer (runs third)
    return 0;
}
