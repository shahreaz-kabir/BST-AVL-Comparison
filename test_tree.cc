// Shahreaz Kabir
// Main file for Part2(b) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.
//This file reads in a database file and file of sequences to construct a tree. Tree then undergoes a variety of tests to measure performance and attributes

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <cmath>
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
	string sequence,enzyme; //string variables initialized to hold parsed data
	while(!inFile.eof()){ //reads file stream until end of file is reached
		inFile>>enzyme>>sequence; //parsed data extracted into variables
		SequenceMap ins(sequence,enzyme);//sequence map object created with parsed data and inserted into tree
		a_tree.insert(ins);
	}
	inFile.close();
}

//@post: reads sequence.txt file and and pushes contents into vector of sequence map objects
//@seq_filename: parameter representing sequence.txt
//@a_tree: 
template <typename TreeType>
vector<SequenceMap> readSequencetxt(const string &seq_filename){
	ifstream data(seq_filename);
	vector<SequenceMap> res; //result vector to be returned at function end
	string sequence;

	while(getline(data, sequence)){ //while getline keeps parsing data sequence map objects created and pushed into vector
		SequenceMap ins2(sequence,""); //only inputs into sequence portion of sequence map
		res.push_back(ins2);
	}
	data.close();
	return res; //returns filled vector
}

//@post:searches through tree and checks if it finds recog sequences from sequences.txt
//@a_tree: tree that is being searched through
//@seq: vector of sequence map objects
//@num: counter for successful queries
//@count: counter for total # of recursive calls
template <typename TreeType>
void searchSequence(TreeType &a_tree, vector<SequenceMap> &seq, int &num, float &count){
	for (auto x : seq){ //while iterating through contents of vector seq
		if (a_tree.find(x, count).getRecognitionSequence() == x.getRecognitionSequence()){ //if recognition sequence matches of x matches with that found in tree, increment num
			num++;		
		}
	}
}

//@post:function removes every third sequence previously inserted into tree
//@a_tree: tree that is being removed from
//@sequences: vector of sequence map objects
//@num: counter for number of successful deletes
//@count: counter for total number of recursive calls
template <typename TreeType>
void removeSequence(TreeType &a_tree, vector<SequenceMap> &sequences, int &num, float &count){
	for(size_t i = 2; i < sequences.size(); i+=3){ //loop starts at third sequence iterates by 3 afterwards
		if(a_tree.contains(sequences[i])){ //check to see if a_tree contains sequence to be deleted
			a_tree.remove(sequences[i], count); //remove sequence if contained in tree
			num++;//increments number of successful removes
		}
	}
}


// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
	// Code for running Part2(b)
	buildTree<TreeType>(db_filename, a_tree); //constructs tree from database file

	cout << "2: " << a_tree.countNodes() << endl; //Outputs node count in given tree
	cout << "3a: " << a_tree.avgDepth() << endl; //Outputs average depth of given tree
	cout << "3b: " << (a_tree.avgDepth() / (log2(a_tree.countNodes()))) << endl; //Outputs ratio of avg depth to log2n

	
	vector<SequenceMap> sequences = readSequencetxt<TreeType>(seq_filename);
	int num = 0;
	float count = 0.0;
	searchSequence<TreeType>(a_tree, sequences, num, count);
	cout << "4a: " << num << endl; //Outputs total number of strings found
	cout << "4b: " << count / sequences.size() << endl; //Outputs the average number of recursive calls
	
	num = 0; //reset num variable
	count = 0.0; //reset count variable
	removeSequence<TreeType>(a_tree, sequences, num, count); // hh
	cout << "5a: " << num << endl; //Outputs total number of successful removes
	cout << "5b: " << count/num << endl; //Outputs average number of recursive calls
	
	cout << "6a: " << a_tree.countNodes() << endl; //Outputs number of nodes in tree
	cout << "6b: " << a_tree.avgDepth() << endl; //Outputs average depth of tree
	cout << "6c: " << (a_tree.avgDepth() / (log2(a_tree.countNodes()))) << endl; //Outputs ration of average depth to log2n
	
}

}  // namespace

int
main(int argc, char **argv) {
	if (argc != 4) {
		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string seq_filename(argv[2]);
	const string param_tree(argv[3]);
	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
	cout << "Type of tree is " << param_tree << endl;
	if (param_tree == "BST") {
		BinarySearchTree<SequenceMap> a_tree;
		TestTree(db_filename, seq_filename, a_tree);
	} else if (param_tree == "AVL") {
		AvlTree<SequenceMap> a_tree;
		TestTree(db_filename, seq_filename, a_tree);
	} else {
		cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
	}
	return 0;
}
