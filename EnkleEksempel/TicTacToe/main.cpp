#include "XrowWindow.h"

// C++ programs start by executing the function main
int main() {
    // Opprett et XrowWindow-objekt med passende dimensjoner og tittel
    XrowWindow win{400, 400, "4 på rad"};

    // Start spill-løkken
    win.run();

    return 0;
}

//------------------------------------------------------------------------------
