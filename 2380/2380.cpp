#include <iostream>
using namespace std;

// Simplification of UnionFind
class BankFusions {
  long *rootBanks;
  long *fusionsSizes;
  public:

BankFusions() { }
~BankFusions() { delete[] rootBanks; delete[] fusionsSizes; }

    void setNumberOfBanks(int numberOfFusions) {
        this->rootBanks = new long[numberOfFusions];
        this->fusionsSizes = new long[numberOfFusions];
        for (int i = 0; i < numberOfFusions; i++) {
            // the start root of a bank is itself
            this->rootBanks[i] = i;
            // the start size of a fusion is 1 (the bank itself)
            this->fusionsSizes[i] = 1;
        }
    }

    void updateRoots(long bank, long root) {
        // optimization: updating the bank direct root
        //  to the root was found in the previous while
        //  perform this operation for every bank in the way to the root
        // example: if 4 (bank) > 3 > 2 > 1 > 0 (root)
        //  the alg will set 4,3 and 2 to point directly to 0
        //  will stop that 1 because it already points to 0
        while (bank != root) {
            int newBank = this->rootBanks[bank];
            this->rootBanks[bank] = root;
            bank = newBank;
        }
    }

    // To which root the bank belongs?
    // All banks on a fusion always same the same root
    long getFusionRoot(long bank) {
        long fusionRoot = bank;
        while (fusionRoot != this->rootBanks[fusionRoot])
            fusionRoot = this->rootBanks[fusionRoot];

        this->updateRoots(bank, fusionRoot);
        return fusionRoot;
    }

    bool areBanksFusioned(long bank1, long bank2) {
        // two banks are fusioned if they have the same root
        return getFusionRoot(bank1) == getFusionRoot(bank2);
    }

    // Replace sets containing x and y with their union.
    void fusionBanks(long bank1, long bank2) {
        long rootBank1 = getFusionRoot(bank1);
        long rootBank2 = getFusionRoot(bank2);
        
        // if they are already fusioned
        if (rootBank1 == rootBank2)
            return;
        
        // both banks should point to the same root
        this->rootBanks[rootBank1] = rootBank2;
        this->fusionsSizes[rootBank2] += this->fusionsSizes[rootBank1];
    }
};

int main()
{
    long numberOfBanks, numOperations;
    cin >> numberOfBanks >> numOperations;

    BankFusions* bankFusions = new BankFusions();
    bankFusions->setNumberOfBanks(numberOfBanks);

    for (int i = 0; i < numOperations; i++) {
        long bank1, bank2;
        char operation;
        cin >> operation >> bank1 >> bank2;
        if (operation == 'F') {
            bankFusions->fusionBanks(bank1-1,bank2-1);
        } else if (operation == 'C') {
            if (bankFusions->areBanksFusioned(bank1-1,bank2-1)) {
                cout << 'S' << endl;
            } else {
                cout << 'N' << endl;
            }
        }
    }
}