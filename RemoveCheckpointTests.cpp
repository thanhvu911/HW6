#include <iostream>
#include <cassert>

#include "RedBlackTree.h"


void TestRemoveLeaf(){
	cout << "Testing Remove Leaf..." << endl;
	
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(40);

	// removing root
	rbt.Remove(40);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == "");
	//assert(rbt.root == nullptr);



	rbt.Insert(40);
	rbt.Insert(23);
	rbt.Remove(23);
	//cout << "rbt after: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B40 ");
	
	rbt.Insert(23);
	rbt.Insert(52);
	rbt.Remove(52);
	assert(rbt.ToPrefixString() == " B40  R23 ");


	rbt.Insert(52);
	rbt.Insert(15);
	rbt.Remove(15);
	//cout << "rbt after: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B40  B23  B52 ");
	assert(rbt.Size() == 3);
	
	cout << "PASSED!" << endl << endl;
}
void TestRemoveRootAsOnlyNode(){
	cout << "Testing Remove Root As Only Node" << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(40);

	// removing root
	rbt.Remove(40);
	//cout << "rbt: " << rbt->ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == "");
	//assert(rbt.root == nullptr); // should be true, but can't test since root is private

	cout << "PASSED!" << endl << endl;
}

void TestRemoveWithOneChildSimple(){
	cout << "Testing Remove Node With One (simple) Child..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(45);
	rbt.Insert(17);
	rbt.Insert(50);
	rbt.Insert(22);

	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B45  B17  R22  B50 ");

	rbt.Remove(17);
	assert(rbt.ToPrefixString() == " B45  B22  B50 ");

	cout << "PASSED!" << endl << endl;
}

int main(){
	
	TestRemoveLeaf();
	TestRemoveRootAsOnlyNode();
	TestRemoveWithOneChildSimple();
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
