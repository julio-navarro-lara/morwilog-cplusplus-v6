//
//  FieldEntry.cpp
//  
//
//  Created by Julio Navarro Lara on 19/04/16.
//
//

#include "FieldEntry.hpp"

FieldEntry::FieldEntry(){

}

FieldEntry::FieldEntry(int value){
    this->field_id = value;
    this->next_value = 0;
}

string FieldEntry::convert_from_IP(long input){
    
    char preresult[INET_ADDRSTRLEN];
    struct sockaddr_in sa;
    sa.sin_addr.s_addr = (in_addr_t)input;
    
    inet_ntop(AF_INET, &(sa.sin_addr), preresult, INET_ADDRSTRLEN);
    
    string result(preresult);
    return result;
}

long FieldEntry::convert_to_IP(string input){
    struct sockaddr_in sa;
    long result = inet_pton(AF_INET, input.c_str(), &(sa.sin_addr));
    if(result != 0){
        result = sa.sin_addr.s_addr;
    }
    return result;
}

bool FieldEntry::is_integer(const string & s){
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    
    char * p;
    strtol(s.c_str(), &p, 10);
    
    return (*p == 0);
}

int FieldEntry::decide_value_number(string value){
    
    int value_number;
    if(values_equivalence.find(value) != values_equivalence.end()){
        //If it is found
        value_number = values_equivalence[value];
    }else{
        //New field
        values_equivalence[value] = next_value;
        inv_values_equivalence.push_back(value);
        value_number = next_value;
        next_value++;
    }
    return value_number;
}

int FieldEntry::get_equivalence_value(string field_value){
    if(type == NOMINAL_VALUE && values_equivalence.find(field_value) != values_equivalence.end()){
        return values_equivalence[field_value];
    }else{
        return -1;
    }
}

string FieldEntry::get_inv_equivalence_value(long field_value){
    if(field_value < inv_values_equivalence.size() && type == NOMINAL_VALUE){
        return inv_values_equivalence.at(field_value);
    }else if(type == IP_ADD_VALUE){
        return convert_from_IP(field_value);
    }else if(type == LONG_VALUE){
        return to_string(field_value);
    }else{
        return "NULL";
    }
}

long FieldEntry::get_value_transformed(string field_value){
    if(type == NOMINAL_VALUE && values_equivalence.find(field_value) != values_equivalence.end()){
        return values_equivalence[field_value];
    }else if(type == IP_ADD_VALUE){
        return convert_to_IP(field_value);
    }else if(type == LONG_VALUE){
        return stol(field_value);
    }else{
        return -1;
    }
}

long FieldEntry::set_value(string field_value){
    
    long value_number;
    
    long result = convert_to_IP(field_value);
    
    if(result != 0){
        type = IP_ADD_VALUE;
        value_number = result;
        
    }else if(is_integer(field_value)){
        type = LONG_VALUE;
        value_number = stol(field_value);
        
    }else{
        type = NOMINAL_VALUE;
        value_number = decide_value_number(field_value);
        
    }

    return value_number;
    
}
