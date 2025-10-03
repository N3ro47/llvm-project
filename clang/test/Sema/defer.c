// RUN: %clang_cc1 -fsyntax-only -verify %s

defer { int y = 20; }; // expected-error {{defer statement can only be used within a function body}}

int main() {
    while (1) {
        defer {
            return 1; // expected-error {{'return' statement not allowed in a defer statement}}
        };
        defer {
            break;    // expected-error {{'break' statement not allowed in a defer statement}}
        };
        defer {
            continue; // expected-error {{'continue' statement not allowed in a defer statement}}
        };
        break;
    }
    return 0;
}
