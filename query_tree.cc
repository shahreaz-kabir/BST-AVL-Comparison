// Shahreaz Kabir
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.
//This file reads in database file and builds a tree. After the tree is built, user input is accepted to find sequences within the tree

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace {

//@post: function reads from file and builds a tree from parsed data
//@db_filename: parameter corresponding to input filename
//@a_tree: parameter corresponding to tree being built
template <typename TreeType>
void buildTree(const string &db_filename, TreeType &a_tree){
	ifstream inFile;
	inFile.open(db_filename);
	string db_line;
	string sequence,enzyme;
	while(!inFile.eof()){
		inFile>>enzyme>>sequence;
		SequenceMap ins(sequence,enzyme);
		a_tree.insert(ins);
	}
	inFile.close();
}

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
	// Code for running Part2(a)
	// Parse input file @db_filename and feel tree @a_tree
	// Then prompt the user for exactly three strings (do a loop) and
	// provide the results of find() as described in the assignment.
	buildTree<TreeType>(db_filename, a_tree);

	string rec_sequence;
	for(int i = 0; i < 3; i++){ //loop to ask for 3 user inputs
		cin >> rec_sequence;
		SequenceMap temp(rec_sequence, ""); //each input read into a sequence map object
		cout << a_tree.find(temp) << endl; //tree attempts to search for input sequence map object 

	}
}

}  // namespace

int
main(int argc, char **argv) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string param_tree(argv[2]);
	cout << "Input filename is " << db_filename << endl;
	cout << "Type of tree is " << param_tree << endl;
	if (param_tree == "BST") {
		BinarySearchTree<SequenceMap> a_tree;
		QueryTree(db_filename, a_tree);
	} else if (param_tree == "AVL") {
		AvlTree<SequenceMap> a_tree;
		QueryTree(db_filename, a_tree);
	} else {
		cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
	}
	return 0;
}
