//
//  LogSummary.cpp
//  Morwilog_v6
//
//  Created by Julio Navarro Lara on 12/06/2018.
//  Copyright © 2018 Julio Navarro Lara. All rights reserved.
//

#include "LogSummary.hpp"

LogSummary::LogSummary(string filename_logs): log_dict(0), cl(FIELD_TO_CLASSIFY, POSITION_TIMESTAMP, MAX_TIME_SEARCH, PROPORTION_ERASE){
    
    parse_from_file(filename_logs);
    
    log_dict.get_equivalence_field("attack", POSITION_OF_ATTACK);
    log_dict.get_equivalence_field("timestamp", POSITION_OF_TIMESTAMP);
    
}

LogSummary::LogSummary(string filename_logs, string filename_info): log_dict(0), cl(FIELD_TO_CLASSIFY, POSITION_TIMESTAMP, MAX_TIME_SEARCH, PROPORTION_ERASE){
    
    
}

int LogSummary::add_log(vector<string> logline, Log & log){
    
    for(auto it = logline.begin()+1; it != logline.end()-1; it += 2){
        
        vector<long> field_value = log_dict.new_entry(*it, *(it+1));
        
        log.add_field_value((int)field_value.at(0), field_value.at(1));
    }
    
    log_list.push_back(log);
    
    return (int)(log_list.size()-1);
}

int LogSummary::change_log(vector<string> logline, int position){
    
    Log log;
    
    for(auto it = logline.begin(); it != logline.end(); it += 2){
        
        vector<long> field_value = log_dict.new_entry(*it, *(it+1));
        
        log.add_field_value((int)field_value.at(0), field_value.at(1));
    }
    
    log_list.at(position) = log;
    
    return 0;
}


void LogSummary::add_log(vector<long> logline){
    Log log(logline);
    
    log_list.push_back(log);
}

bool LogSummary::is_an_attack(int log_position){
    if(log_list.at(log_position).get_value(POSITION_OF_ATTACK) == 0){
        return false;
    }else{
        return true;
    }
}

bool LogSummary::is_integer(const string & s){
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    
    char * p;
    strtol(s.c_str(), &p, 10);
    
    return (*p == 0);
}

int LogSummary::parse_from_file(string filename){
    vector<string> vs;
    
    uintmax_t line = wc(filename.c_str(), vs);
    
    std::cout << "Line : " << line << " - vec size : " << vs.size() << std::endl;
    
    //*
    std::vector<std::string> v_split;
    
    Log log;
    int position;
    // More optimised (but need g++4.9 and maybe more) with  : std::vector<std::string_view> vsv;
    for(size_t i=0; i<vs.size(); i+=1){
        v_split.clear();
        test_custom(vs[i], "#=", v_split);
        
        position = add_log(v_split, log);
        
        cl.classify_log(log, position);
        
    }
    std::cout << "Nb item after split : "<< v_split.size() << std::endl;
    //    std::cout << vs[0] << std::endl;
    //    for(size_t a=0; a<v_split.size(); a+=1){
    //        std::cout << " " << v_split[a];
    //    }
    //    std::cout << std::endl;
    
    return (int)line;
    
}

// This functions work with a single log line
// It returns its fields arranged in a map
void LogSummary::satf_to_map (string logline, std::vector<string>& log_map){
    
    istringstream ss(logline);
    string element1;
    string element2;
    getline(ss,element1,'#');
    getline(ss,element1,'#');
    //two_string tmp;
    while(getline(ss, element1, '=')){
        
        if(getline(ss, element2, '#')){;
            //cout << element1 << "    ";
            //cout << element2 << endl;
            
            //tmp.field=element1;
            //tmp.value=element2;
            log_map.push_back(element1);
            log_map.push_back(element2);
        }
    }
}

//This was made in logline inside regex_match on satf_to_map.
std::string LogSummary::space2underscore(std::string text) {
    for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
        if(*it == ' ') {
            *it = '_';
        }
    }
    return text;
}

bool LogSummary::check_time(int log_position_first, int log_position_second, long time_period_to_check){
    long time_first = get_value(log_position_first, POSITION_OF_TIMESTAMP);
    long time_second = get_value(log_position_second, POSITION_OF_TIMESTAMP);
    
    if(time_second-time_first > time_period_to_check){
        return false;
    }else{
        return true;
    }
}

void LogSummary::extract_random_sequences(int length, vector<vector<int>> & result){
    cl.extract_random_sequences(length, result);
}


int LogSummary::get_field_number(string field_name){
    
    int field_number;
    
    log_dict.get_equivalence_field(field_name, field_number);
    
    return field_number;
}

long LogSummary::get_attack_value(int log_position){
    return get_value(log_position, POSITION_OF_ATTACK);
}


char LogSummary::get_field_equivalence(string field_name, string field_value, int & field_number, long & value_number){
    
    char result;
    
    log_dict.get_equivalence_value(field_name, field_value, field_number, value_number, result);
    
    return result;
}


void LogSummary::get_hash(int log_position, vector<int> const & fields_to_compare, size_t & hash){
    log_list.at(log_position).get_hash(fields_to_compare, hash);
}

void LogSummary::get_inv_dict(InvDictionary & inv_dict){
    inv_dict = * new InvDictionary(&log_dict);
}

bool LogSummary::get_log_value(int log_position, vector<long> & result){
    if(log_position < log_list.size()){
        log_list.at(log_position).get_content(result);
        return true;
    }else{
        result = {};
        return false;
    }
}

long LogSummary::get_value(int log_position, int field_number){
    return log_list.at(log_position).get_value(field_number);
}

void LogSummary::print_logs(string filename_logs){
    
    map<int,string> field_names;
    string field_name;
    string value_name;
    string logline;
    
    vector<long> content;
    
    ofstream output_file;
    
    output_file.open(filename_logs);
    
    for(auto it = log_list.begin(); it != log_list.end(); it++){
        
        logline = "#S#";
        
        
        
        it->get_content(content);
        
        for(int i = 0; i < content.size(); i++){
            if(field_names.find(i)==field_names.end()){
                log_dict.get_inv_equivalence_field(i, field_name);
                field_names[i] = field_name;
            }else{
                field_name = field_names[i];
            }
            
            log_dict.get_inv_equivalence_value(field_name, content.at(i), value_name);
            
            logline += field_name + "=" + value_name + "#";
            
        }
        
        logline += "E#";
        
        output_file << logline << endl;
        
        
    }
    
    output_file.close();
    
}

void LogSummary::print_logs(string filename_logs, int max_num_logs){
    
    map<int,string> field_names;
    string field_name;
    string value_name;
    string logline;
    
    vector<long> content;
    
    ofstream output_file;
    
    output_file.open(filename_logs);
    
    for(int i = 0; i < max_num_logs; i++){
        
        logline = "#S#";
        
        log_list.at(i).get_content(content);
        
        for(int i = 0; i < content.size(); i++){
            if(field_names.find(i)==field_names.end()){
                log_dict.get_inv_equivalence_field(i, field_name);
                field_names[i] = field_name;
            }else{
                field_name = field_names[i];
            }
            
            log_dict.get_inv_equivalence_value(field_name, content.at(i), value_name);
            
            logline += field_name + "=" + value_name + "#";
            
        }
        
        logline += "E#";
        
        output_file << logline << endl;
        
        
    }
    
    output_file.close();
    
}

void LogSummary::reset_all_attacks_value(long value){
    
    for(int log_position = 0; log_position < log_list.size(); log_position++){
        log_list.at(log_position).add_field_value(get_field_number("attack"), value);
    }
    
}


bool LogSummary::sequence_is_an_attack(vector<int> const & sequence){
    
    long attack_value = get_value(sequence.at(0), POSITION_OF_ATTACK);
    long new_attack_value = 0;
    
    if(attack_value == 0){
        return false;
    }
    
    for(int i = 1; i<sequence.size(); i++){
        new_attack_value = get_value(sequence.at(i), POSITION_OF_ATTACK);
        if(new_attack_value != attack_value){
            return false;
        }
        attack_value = new_attack_value;
    }
    
    return true;
}

void LogSummary::set_attack_value(int log_position, long value){
    
    log_list.at(log_position).add_field_value(get_field_number("attack"), value);
    
}


template<typename C>
void LogSummary::test_custom(std::string const& s, char const* d, C& ret)
{
    C output;
    
    std::bitset<255> delims;
    while( *d )
    {
        unsigned char code = *d++;
        delims[code] = true;
    }
    typedef std::string::const_iterator iter;
    iter beg;
    bool in_token = false;
    for( iter it = s.begin(), end = s.end(); it != end; ++it )
    {
        if( delims[*it] )
        {
            if( in_token )
            {
                output.push_back(typename C::value_type(beg, it));
                in_token = false;
            }
        }
        else if( !in_token )
        {
            beg = it;
            in_token = true;
        }
    }
    if( in_token )
        output.push_back(typename C::value_type(beg, s.end()));
    output.swap(ret);
}

uintmax_t LogSummary::wc(char const *fname, std::vector<std::string>& v_string)
{
#define BUFFER_SIZE 21000
#define READ_SIZE   20000
#define SAVE_SIZE  1000
    int fd = open(fname, O_RDONLY);
    if(fd == -1){
        std::cerr <<"fd error" << std::endl;
        exit(-1);
    }
    
    /* Advise the kernel of our access pattern.  */
    //posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL
    
    
    char buf[BUFFER_SIZE + 1];
    uintmax_t lines = 0;
    char* start;
    char* p;
    size_t offset=0;
    char* fo;
    while(size_t bytes_read = read(fd, &buf[offset], READ_SIZE))
    {
        if(bytes_read == (size_t)-1){
            std::cerr << "Read failed" << std::endl;
            exit(-1);
        }
        if (!bytes_read)
            break;
        
        start=buf;
        fo=buf+offset+bytes_read;
        for(p = buf; p<fo && (p = (char*) memchr(p, '\n', (fo) - p)); ++p){
            ++lines;
            v_string.push_back(std::string(start, p-start));
            p+=1;
            fo=buf+offset+bytes_read;
            start=p;
        }
        
#define SIZE_REPORT ((buf+offset+bytes_read)-start)
        offset=SIZE_REPORT;
        memcpy(buf, start, offset);
    }
    
    return lines;
}

int LogSummary::sort_logs_by_timestamp(){
    
    sort(log_list.begin(), log_list.end(), less_than_key());
    
    for(long i = 0; i < log_list.size(); i++){
        log_list.at(i).change_value_0(i);
    }
    
    return 0;
}


int LogSummary::change_timestamp(long timestamp, int position){
    
    log_list.at(position).change_value_1(timestamp);
    
    return 0;
}

LogSubsetIterator::LogSubsetIterator(LogSummary * logs): clas_it(&logs->cl){
}

bool LogSubsetIterator::get_next(vector<int> & selected_logs){
    return clas_it.get_next(selected_logs);
}
