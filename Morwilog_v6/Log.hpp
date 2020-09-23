//
//  Log.h
//  
//
//  Created by Julio Navarro Lara on 19/04/16.
//
//

#ifndef ____Log__
#define ____Log__

#include <stdio.h>
#include <vector>
#include <iostream>

#include <boost/functional/hash.hpp>

using namespace std;

class Log {
    
    vector<long> content;

public:
    
    Log();
    
    Log(vector<long> content);
    
    void add_field_value(int position, long value);
    
    void get_content(vector<long> & content);
    
    void get_hash(vector<int> const & fields_to_compare, size_t & hash);
    
    long get_value(int position);
    
    void change_value_0(long new_value);
    void change_value_1(long new_value);
};

#endif /* defined(____Log__) */