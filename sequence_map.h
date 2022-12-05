//Shahreaz Kabir
//SequenceMap class used to create sequence map object which holds a dna recognition sequence and its corresponding enzyme acronym

#ifndef SEQUENCE_MAP_
#define SEQUENCE_MAP_

#include <string>
#include <vector>
#include <iostream>

class SequenceMap 
{
public:
    //default constructor
    SequenceMap() = default;

    //copy constructor
    SequenceMap(const SequenceMap &rhs) = default;

    //copy assignment
    SequenceMap& operator=(const SequenceMap &rhs) = default;

    //move constructor
    SequenceMap(SequenceMap& rhs) = default;

    //move assignment
    SequenceMap& operator=(SequenceMap &&rhs) = default;

    //destructor
    ~SequenceMap() = default;

    //one parameter constructor
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro) :recognition_sequence_(a_rec_seq) {
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    //overloaded comparison operator to check if this object less than rhs object
    bool operator<(const SequenceMap &rhs) const {
        return(this->recognition_sequence_ < rhs.recognition_sequence_);
    }

    //overloaded comparison operator to check if this object greater than rhs object
    bool operator>(const SequenceMap &rhs) const {
        return(this->recognition_sequence_ > rhs.recognition_sequence_);
    }

    //Overloaded ostream operator to print out enzyme acronyms from sequence map object
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &sequencemap){
        for (auto x : sequencemap.enzyme_acronyms_){
            out << x << ' ';
        }
        return out;
    }

    //Overloaded extraction operator to input sequence map object
    friend std::istream &operator>>(std::istream &in, SequenceMap &sequencemap){
        in >> sequencemap.recognition_sequence_;
        return in;
    }

    //Returns the recognition sequence
    std::string getRecognitionSequence() {
        return recognition_sequence_;
    }

    //adds enzyme acronyms to vector of calling function
    void Merge(const SequenceMap &other_sequence){
        for(size_t i = 0; i < other_sequence.enzyme_acronyms_.size(); ++i) {
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }

private:
    std::string recognition_sequence_;
    std::vector<std::string> enzyme_acronyms_;

};

#endif
