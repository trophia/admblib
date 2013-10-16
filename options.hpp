#pragma once

#include <algorithm>
#include <string>

namespace AdmbLib {

/**
 * Check if the program was called with a particular option e.g. -ainp
 * 
 * @param  option An option string without dashes (e.g. "ainp")
 * @return        True if called with option
 */
bool option(const std::string& option){
	return std::count_if(ad_comm::argv,ad_comm::argv+ad_comm::argc,[option](const char* arg){
		return arg==("-"+option);
	});
}

/**
 * Get the index of an option
 * 
 * @param  option An option string without dashes (e.g. "ainp")
 * @return        An index >=0 if exists or -1 if it does not 
 */
int option_index(const std::string& option){
	for(int index=0;index<ad_comm::argc;index++){
		std::string arg = ad_comm::argv[index];
		if(arg==("-"+option)) return index;
	}
	return -1;
}

/**
 * Get the value following an option e.g. -year 2013
 * 
 * @param  option An option string without dashes (e.g. "year")
 * @return        The option value converted to a double
 */
double option_number(const std::string& option){
	int index = option_index(option);
	if(index>0 and ad_comm::argc>index){
		return std::atof(ad_comm::argv[index+1]);
	}
	return NA;
}

}