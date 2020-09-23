//
//  morwilog_v6.hpp
//  Morwilog_v6
//
//  Created by Julio Navarro Lara on 11/06/2018.
//  Copyright © 2018 Julio Navarro Lara. All rights reserved.
//

#ifndef morwilog_v6_hpp
#define morwilog_v6_hpp



#include <string>
#include <vector>

#include "LogSummary.hpp"

LogSummary reading_logs(std::string filename);

int main_execution(std::vector<std::string> & header_results, std::vector<long> & results, int loghill_id, bool no_ph);

int morwilog_v6(void);

#endif /* morwilog_v6_hpp */
