#pragma once

#include <cassert>

#include "containers.hpp"

namespace AdmbLib {

int data_count(const dvector& observeds){
	int count = 0;
	for(int index=observeds.indexmin();index<=observeds.indexmax();index++){
		double observed = observeds(index);
		if(observed!=NA) count++;
	}
	return count;
}

dvariable data_scalar(const dvar_vector& expecteds, const dvector& observeds){
	RETURN_ARRAYS_INCREMENT();
	assert(expecteds.indexmin()==observeds.indexmin() and expecteds.indexmax()==observeds.indexmax());
	dvariable sum = 0;
	int count = 0;
	for(int index=observeds.indexmin();index<=observeds.indexmax();index++){
		double observed = observeds(index);
		if(observed!=NA){
			dvariable expected = expecteds(index);
			sum += log(observed/expected);
			count++;
		}
	}
	dvariable scalar = exp(sum/count);
	RETURN_ARRAYS_DECREMENT();
	return scalar;
}


}