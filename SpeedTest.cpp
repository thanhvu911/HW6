#include <cstdlib>
#include <ctime>
#include "RedBlackTree.h"

using namespace std;


int main(){

	// create a simulated 3.7 million ID number system.
	const int N = 3700000;

	clock_t start = clock();
	RedBlackTree rbt = RedBlackTree();
	for(int i = 0; i < N; i++){
		rbt.Insert(i);
	}
	clock_t stop = clock();

	double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
	cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;

	// Your code goes here to simulate leaving / joining.
    // Repeat Remove() 5 times and measure each
    for (int i = 0; i < 5; i++) {
        start = clock();
        int leave;
        do {
            leave = rand() % (N * 10);
        } while (!rbt.Contains(leave));
        rbt.Remove(leave);
        stop = clock();
        duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
        cout << "Removed ID " << leave << " in " << duration << " seconds." << endl;
    }

    // Repeat Insert() 5 times and measure each
    for (int i = 0; i < 5; i++) {
        start = clock();
        int add;
        do {
            add = rand() % (N * 10);
        } while (rbt.Contains(add));
        rbt.Insert(add);
        stop = clock();
        duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
        cout << "Added ID " << add << " in " << duration << " seconds." << endl;
    }

    return 0;
}

