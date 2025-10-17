#include "Markov.h"

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

    Markov machine(filename);

    cout << machine.start << endl;

    machine.run(log);
    
    cout << machine.start << endl;

    return 0;
}


// abcde
// ab xz
// cd y
// e uv
// xz q
