#include "turing_header.h"
#include "TuringMachine.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <rules_file> [-log]" << endl;
        return 1;
    }

    string filename = argv[1];
    bool log = false;

    for (int i = 2; i < argc; i++) {
        if (string(argv[i]) == "-log") {
            log = true;
        }
    }

    TuringMachine machine(filename);
    cout << "Start: ";
    machine.tape.print();
    machine.run(log);
    cout << "Finale: ";
    machine.tape.print();

    return 0;
}
