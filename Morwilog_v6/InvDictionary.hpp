//
//  InvDictionary.h
//  
//
//  Created by Julio Navarro Lara on 02/05/16.
//
//

#ifndef ____InvDictionary__
#define ____InvDictionary__

#include <stdio.h>

#include "LogDictionary.hpp"

class InvDictionary{
    
    LogDictionary * dict;
    
public:
    
    InvDictionary();
    
    InvDictionary(LogDictionary * dict);
    
    void get_inv_equivalence_field(int field_number, string & field_name);
    
    void get_inv_equivalence_value(string field_name, long value_number, string & value_name);
    
};

#endif /* defined(____InvDictionary__) */
