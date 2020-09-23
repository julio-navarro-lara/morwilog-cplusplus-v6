//
//  Classifier.cpp
//  
//
//  Created by Julio Navarro Lara on 22/04/16.
//
//

#include "Classifier.hpp"

Classifier::Classifier(int field_to_classify, int position_timestamp, long maximum_time, double proportion_erased){
    
    this->field_to_classify = field_to_classify;
    this->proportion_erased = proportion_erased;
    this->position_timestamp = position_timestamp;
    this->maximum_time = maximum_time;
    
    this->debug_size = 0;
}

void Classifier::erase_not_needed(int length, vector<int> & log_vector){
    int choice;
    //WARNING: THIS COULD CHANGE according to this, we will have trees wider or narrower
    //int limit = log_vector.size() * proportion_erased;
    int limit = log_vector.size() % length;
    //Wath out!! The length of the vector is being reduced during loop execution
    for(int i = 0; i < limit; i++){
        choice = rand() % log_vector.size();
        log_vector.erase(log_vector.begin() + choice);
    }
}

void Classifier::get_sequences_random(int length, vector<int> & log_vector, vector<vector<int>> & separated_log_vector){
    
    int limit = 1 +(log_vector.size() % (5*length));
    int choice_0;
    vector<int> tmp;
    for(int i = 0; i < limit; i++){
        
        choice_0 = rand() % (log_vector.size()-length);
        
        for(int j = choice_0; j < choice_0+length; j++){
            tmp.push_back(log_vector.at(j));
        }
        
        separated_log_vector.push_back(tmp);
        
        tmp.clear();
    }
    
}


void Classifier::get_sequences_separated(int length, vector<int> & log_vector, vector<vector<int>> & separated_log_vector){
    vector<int>::const_iterator pointer = log_vector.begin();
    vector<int> tmp(length);
    while(pointer != log_vector.end()){
        tmp = *new vector<int>(pointer, pointer + length);
        separated_log_vector.push_back(tmp);
        pointer += length;
    }
}

void Classifier::classify_log(Log & log, int log_position){
    
    long value_class = log.get_value(field_to_classify);
    
    if(classification.find(value_class) == classification.end()){
        classification[value_class].push_back({log_position});
        last_timestamps[value_class] = log.get_value(position_timestamp);
        
        debug_size++;
    }else{
        //We need to check the time of last element
        
        auto last_set = classification[value_class].end()-1;
        
        if(log.get_value(position_timestamp)-last_timestamps[value_class]<maximum_time){
            //IF the difference in time is less than the maximum, we append it to the last list
            last_set->push_back(log_position);
        }else{
            //IF it is higher, we create a new set
            classification[value_class].push_back({log_position});
            
            debug_size++;
        }
        
        last_timestamps[value_class] = log.get_value(position_timestamp);
        
    }
}

//Me make a local copy so the elements in "classification" are not erased
void Classifier::extract_random_sequences(int length, vector<vector<int>> & result){
    
    size_t number_of_logs;
    
    map<long, vector<vector<int>>> classif = classification;
    
    for(map<long, vector<vector<int>>>::iterator it = classif.begin(); it != classif.end(); it++){
        for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
            number_of_logs = it2->size();
            if(number_of_logs == length){
                result.push_back(*it2);
            } else if(number_of_logs > length){
                //erase_not_needed(length, it->second);
                //get_sequences_separated(length, it->second, result);
                get_sequences_random(length, *it2, result);
            }
        }
        
    }
    
}

void Classifier::get_iterator_begin(map<long,vector<vector<int>>>::iterator & it, vector<vector<int>>::iterator & subit){
    it = classification.begin();
    subit = it->second.begin();
    
}

void Classifier::get_iterator_end(map<long,vector<vector<int>>>::iterator & it, vector<vector<int>>::iterator & subit){
    it = classification.end();
    subit = classification.begin()->second.end();
}

size_t Classifier::get_max_size_vector(map<long, size_t> & result_size){
    size_t result = 0;
    for(auto it = classification.begin(); it != classification.end(); it++){
        result_size[it->first] = it->second.size();
        if(it->second.size() > result){
            result = it->second.size();
        }
    }
    return result;
}


ClassifierIterator::ClassifierIterator(Classifier * cla){
    cla->get_iterator_begin(it, subit);
    cla->get_iterator_begin(the_begin, the_subbegin);
    cla->get_iterator_end(the_end, the_subend);
    max_size_vector = cla->get_max_size_vector(max_size_vector_map);
    size_counter = 0;
    
}

bool ClassifierIterator::get_next(vector<int> & selected_logs){
    
    if(size_counter >= max_size_vector){
        selected_logs = {};
        return false;
    }else{
        
        if(size_counter < max_size_vector_map[it->first]){
            subit = it->second.begin()+size_counter;
            the_subend = it->second.end();
        
            selected_logs = *subit;
            
            it++;
            
            if(it == the_end){
                //If we arrive to the end, another loop with size_counter++
                it = the_begin;
                size_counter++;
            }
        
            return true;
        }else{
            while(size_counter >= max_size_vector_map[it->first]){
                
                it++;
                
                if(it == the_end){
                    //If we arrive to the end, another loop with size_counter++
                    it = the_begin;
                    size_counter++;
                    if(size_counter >= max_size_vector){
                        selected_logs = {};
                        return false;
                    }
                }
                
            }
            
            subit = it->second.begin()+size_counter;
            the_subend = it->second.end();
            
            selected_logs = *subit;
            
            it++;
            
            if(it == the_end){
                //If we arrive to the end, another loop with size_counter++
                it = the_begin;
                size_counter++;
            }

            
            return true;
            

        }
        
    }
    
//    if(it == the_end){
//        selected_logs = {};
//        return false;
//    }else{
//        selected_logs = *subit;
//        subit++;
//        if(subit == the_subend){
//            it++;
//            if(it != the_end){
//                subit = it->second.begin();
//                the_subend = it->second.end();
//            }
//        }
//        return true;
//    }
}


