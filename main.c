#include <stdio.h>
#include "unicode.h"

int main(void) {
    uniprint(L"Hello, \\u25EF!\n");
    return 0;
}