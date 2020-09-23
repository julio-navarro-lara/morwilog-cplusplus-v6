//
//  InvDictionary.cpp
//  
//
//  Created by Julio Navarro Lara on 02/05/16.
//
//

#include "InvDictionary.hpp"

InvDictionary::InvDictionary(){
    
}

InvDictionary::InvDictionary(LogDictionary * dict){
    this->dict = dict;
}

void InvDictionary::get_inv_equivalence_field(int field_number, string & field_name){
    dict->get_inv_equivalence_field(field_number, field_name);
}

void InvDictionary::get_inv_equivalence_value(string field_name, long value_number, string & value_name){
    dict->get_inv_equivalence_value(field_name, value_number, value_name);
}
