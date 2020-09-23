//
//  Log.cpp
//  
//
//  Created by Julio Navarro Lara on 19/04/16.
//
//

#include "Log.hpp"

Log::Log(){
    
}

Log::Log(vector<long> content){
    this->content = content;
}

void Log::add_field_value(int position, long value){
    
    if(content.size() <= position){
        content.resize(position+1);
    }
    
    content.at(position) = value;
    
}

void Log::get_content(vector<long> & content){
    content = this->content;
}


void Log::get_hash(vector<int> const & fields_to_compare, size_t & hash){
    hash = 0;
    
    for(auto it = fields_to_compare.begin(); it != fields_to_compare.end(); it++){
        boost::hash_combine(hash, content[*it]);
    }
}

long Log::get_value(int position){
    return content.at(position);
}

void Log::change_value_0(long new_value){
    content.at(0) = new_value;
}

void Log::change_value_1(long new_value){
    content.at(1) = new_value;
}
