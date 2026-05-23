#include <tree/B_tree.h>
#include <string>
#include <iostream>

int main() {
    astra::b_tree<std::string, 4> test;

    test.push("hello");
}
