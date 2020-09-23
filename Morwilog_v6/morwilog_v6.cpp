//
//  morwilog_v6.cpp
//  Morwilog_v6
//
//  Created by Julio Navarro Lara on 11/06/2018.
//  Copyright © 2018 Julio Navarro Lara. All rights reserved.
//

#include "morwilog_v6.hpp"

std::string FILENAME_LOGS = "input_darpa2000.log";

LogSummary reading_logs(std::string filename){
    cout << "Reading the log file..." << endl;
    
    clock_t begin = clock();
    
    LogSummary logs(FILENAME_LOGS);
    
    clock_t end = clock();
    double elapsed_secs_reading = double(end-begin) / CLOCKS_PER_SEC;
    cout << "Routine time: " << elapsed_secs_reading << endl;
    
    cout << "Log file read" << endl << endl;
    
    return logs;
}

int main_execution(std::vector<std::string> & header_results, std::vector<long> & results, int loghill_id, bool no_ph){
    reading_logs(FILENAME_LOGS);
    return 1;
}

int morwilog_v6(void){
    srand((int)time(NULL));
    int exit_value = -1;
    
    std::vector<long> results;
    std::vector<std::string> header_results;
    
    exit_value = main_execution(header_results,results,0, false);
    
    return exit_value;
}
