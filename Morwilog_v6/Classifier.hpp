//
//  Classifier.h
//  
//
//  Created by Julio Navarro Lara on 22/04/16.
//
//

#ifndef ____Classifier__
#define ____Classifier__

#include <stdio.h>
#include <map>
#include <vector>
#include <cstdlib>

#include "Log.hpp"

using namespace std;

class Classifier{
    
    double proportion_erased;
    
    int field_to_classify;
    //Position of the timestamp in the log
    int position_timestamp;
    //Maximum time to search
    long maximum_time;
    
    long debug_size;
    
    //The key is the value of the field classifying, and the value is a vector with the id of each log. We separate the logs for each key in different vectors depending on the time set.
    map<long, vector<vector<int>>> classification;
    //We need to know which is the last timestamp saved in each of the batches
    map<long, long> last_timestamps;
    
    //Methods
    void erase_not_needed(int length, vector<int> & log_vector);
    
    void get_sequences_random(int length, vector<int> & log_vector, vector<vector<int>> & separated_log_vector);
    
    void get_sequences_separated(int length, vector<int> & log_vector, vector<vector<int>> & separated_log_vector);
    
public:
    
    Classifier(int field_to_classify, int position_timestamp, long maximum_time, double proportion_erased);
    
    void classify_log(Log & log, int log_position);
    
    //WE extract the random sequences for the trees
    void extract_random_sequences(int length, vector<vector<int>> & result);
    
    void get_iterator_begin(map<long, vector<vector<int>>>::iterator & it, vector<vector<int>>::iterator & subit);
    
    void get_iterator_end(map<long, vector<vector<int>>>::iterator & it, vector<vector<int>>::iterator & subit);
    
    size_t get_max_size_vector(map<long, size_t> & result_size);
};

class ClassifierIterator{
    
    map<long, vector<vector<int>>>::iterator the_begin;
    vector<vector<int>>::iterator the_subbegin;
    
    map<long, vector<vector<int>>>::iterator it;
    vector<vector<int>>::iterator subit;
    
    map<long, vector<vector<int>>>::iterator the_end;
    vector<vector<int>>::iterator the_subend;
    
    size_t max_size_vector;
    size_t size_counter;
    
    map<long, size_t> max_size_vector_map;
    
public:
    
    ClassifierIterator(Classifier * cla);
    
    bool get_next(vector<int> & selected_logs);
    
};

#endif /* defined(____Classifier__) */
