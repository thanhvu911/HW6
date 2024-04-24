all:
	g++ -Wall -g RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o rbt1-test
	g++ -Wall -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-test
	g++ -Wall -g RedBlackTree.cpp SpeedTest.cpp -o speed-test
	g++ -Wall -g RedBlackTree.cpp RemoveCheckpointTests.cpp -o check-test

