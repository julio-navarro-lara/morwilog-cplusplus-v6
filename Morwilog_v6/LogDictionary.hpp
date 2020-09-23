//
//  LogDictionary.h
//  
//
//  Created by Julio Navarro Lara on 19/04/16.
//
//

#ifndef ____LogDictionary__
#define ____LogDictionary__

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <arpa/inet.h>

#include "FieldEntry.hpp"

using namespace std;


class LogDictionary {
    
    map<string, FieldEntry> field_equivalence;
    
    vector<string> inv_field_equivalence;
    
    int next_field;
    
    //Methods
    int process_field_name(string field_name);
    
    long process_field_value(string field_name, string field_value);
    
public:
    
    LogDictionary(int start_field);
    
    void get_equivalence_field(string field_name, int & field_number);
    
    void get_equivalence_value(string field_name, string field_value, int & field_number, long & value_number, char & type);
    
    void get_inv_equivalence_field(int field_number, string & field_name);
    
    void get_inv_equivalence_value(string field_name, long value_number, string & value_name);
    
    //Returns a vector with key in 0 and value in 1
    vector<long> new_entry(string field_name, string field_value);
    
};

#endif /* defined(____LogDictionary__) */
