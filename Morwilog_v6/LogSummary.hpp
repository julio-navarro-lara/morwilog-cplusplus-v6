//
//  LogSummary.hpp
//  Morwilog_v6
//
//  Created by Julio Navarro Lara on 12/06/2018.
//  Copyright © 2018 Julio Navarro Lara. All rights reserved.
//

#ifndef LogSummary_hpp
#define LogSummary_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstdlib>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
//include <string_view>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include <sys/mman.h>
#include <sys/stat.h>
#include <bitset>

//#include "boost/algorithm/string.hpp"

#include "Log.hpp"
#include "LogDictionary.hpp"
#include "Classifier.hpp"
#include "InvDictionary.hpp"

using namespace std;

#define INTERNAL_LOG_SUMMARY Log
#define CONTAINER_LOG_SUMMARY std::vector<INTERNAL_LOG_SUMMARY>

//It stores a summary of the logs for constructing the trees
class LogSummary {
    
    LogDictionary log_dict;
    
    Classifier cl;
    
    CONTAINER_LOG_SUMMARY log_list;
    
    friend class LogSubsetIterator;
    
    int POSITION_OF_ATTACK;
    int POSITION_OF_TIMESTAMP;
    
    //For sorting the logs according to time
    struct less_than_key
    {
        inline bool operator() (Log& log1, Log& log2)
        {
            return (log1.get_value(POSITION_TIMESTAMP) < log2.get_value(POSITION_TIMESTAMP));
        }
    };
    
    //Methods
    int add_log(vector<string> logline, Log & log);
    
    void add_log(vector<long> logline);
    
    bool is_an_attack(int log_position);
    
    bool is_integer(const string & s);
    
    int parse_from_file(string filename);
    
    void satf_to_map (string logline, std::vector<string>& log_map);
    
    std::string space2underscore(std::string text);
    
    
    
public:
    
    LogSummary(string filename_logs);
    
    LogSummary(string filename_logs, string filename_info);
    
    //It checks if the difference if time between the two logs indicated is less than MAX_TIME
    //If it is like that, it returns true
    bool check_time(int log_position_first, int log_position_second, long time_period_to_check);
    
    void extract_random_sequences(int length, vector<vector<int>> & result);
    
    long get_attack_value(int log_position);
    
    int get_field_number(string field_name);
    
    char get_field_equivalence(string field_name, string field_value, int & field_number, long & value_number);
    
    void get_hash(int log_position, vector<int> const & fields_to_compare, size_t & hash);
    
    void get_inv_dict(InvDictionary & inv_dict);
    
    bool get_log_value(int log_position, vector<long> & result);
    
    long get_value(int log_position, int field_number);
    
    void print_logs(string filename_logs);
    void print_logs(string filename_logs, int max_num_logs);
    
    void reset_all_attacks_value(long value);
    
    bool sequence_is_an_attack(vector<int> const & sequence);
    
    void set_attack_value(int log_position, long value);
    
    template<typename C>
    void test_custom(std::string const& s, char const* d, C& ret);
    
    uintmax_t wc(char const *fname, std::vector<std::string>& v_string);
    
    int sort_logs_by_timestamp();
    
    int change_log(vector<string> logline, int position);
    int change_timestamp(long timestamp, int position);
};

class LogSubsetIterator{
    
    ClassifierIterator clas_it;
    
public:
    
    LogSubsetIterator(LogSummary * logs);
    
    bool get_next(vector<int> & selected_logs);
    
};

#endif /* LogSummary_hpp */
