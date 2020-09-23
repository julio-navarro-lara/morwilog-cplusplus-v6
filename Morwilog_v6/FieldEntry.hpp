//
//  FieldEntry.h
//  
//
//  Created by Julio Navarro Lara on 19/04/16.
//
//

#ifndef ____FieldEntry__
#define ____FieldEntry__

#include <stdio.h>
#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include <arpa/inet.h>

#include "global_variables.h"

using namespace std;

class FieldEntry {
    int field_id;
    
    map<string, int> values_equivalence;
    
    vector<string> inv_values_equivalence;
    
    int next_value;
    
    //Definition of data types for each of the fields
    char type;
    
    //Methods
    
    string convert_from_IP(long input);
    
    //Return the IP address converted or -1 if it has not a valid format
    long convert_to_IP(string input);
    
    bool is_integer(const string & s);
    
public:
    
    FieldEntry();
    FieldEntry(int value);
    
    int decide_value_number(string value);
    
    int get_field_id(){ return field_id;}
    
    int get_equivalence_value(string field_value);
    
    string get_inv_equivalence_value(long field_value);
    
    char get_type(){ return type;}
    
    long get_value_transformed(string field_value);
    
    long set_value(string field_value);
    
};

#endif /* defined(____FieldEntry__) */
