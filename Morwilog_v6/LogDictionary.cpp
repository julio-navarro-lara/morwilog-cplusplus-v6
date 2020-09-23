//
//  LogDictionary.cpp
//  
//
//  Created by Julio Navarro Lara on 19/04/16.
//
//

#include "LogDictionary.hpp"

LogDictionary::LogDictionary(int start_field){
    next_field = start_field;
    if(start_field > 0){
        inv_field_equivalence = *new vector<string>(start_field, 0);
    }
}

int LogDictionary::process_field_name(string field_name){
    int field_number;
    
    if(field_equivalence.find(field_name) != field_equivalence.end()){
        //If it is found
        field_number = field_equivalence[field_name].get_field_id();
        
    }else{
        //New field
        field_equivalence[field_name] = FieldEntry(next_field);
        //For the reverse dictionary:
        inv_field_equivalence.push_back(field_name);
        field_number = next_field;
        next_field++;
    }
    
    return field_number;
}

long LogDictionary::process_field_value(string field_name, string field_value){
    long value_number;
    
    value_number = field_equivalence[field_name].set_value(field_value);
    
    return value_number;
}

void LogDictionary::get_equivalence_field(string field_name, int & field_number){
    if(field_equivalence.find(field_name) != field_equivalence.end()){
        field_number = field_equivalence[field_name].get_field_id();
    }else{
        field_number = -1;
    }
}

void LogDictionary::get_equivalence_value(string field_name, string field_value, int & field_number, long & value_number, char & type){
    if(field_equivalence.find(field_name) != field_equivalence.end()){
        FieldEntry* entry = &field_equivalence[field_name];
        
        field_number = entry->get_field_id();
        
        type = entry->get_type();
        
        value_number = entry->get_value_transformed(field_value);
        
    }else{
        field_number = -1;
        value_number = -1;
    }
}

void LogDictionary::get_inv_equivalence_field(int field_number, string & field_name){
    field_name = inv_field_equivalence.at(field_number);
}

void LogDictionary::get_inv_equivalence_value(string field_name, long value_number, string & value_name){
    
    value_name = field_equivalence[field_name].get_inv_equivalence_value(value_number);
}

vector<long> LogDictionary::new_entry(string field_name, string field_value){
    
    vector<long> result(2);
    
    result.at(0) = process_field_name(field_name);
    result.at(1) = process_field_value(field_name, field_value);
    
    return result;
}


