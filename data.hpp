#pragma once

#include <cassert>

#include "distributions.hpp"

namespace AdmbLib {

const double NA = -999.999;

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

dvariable data_like(const dvar_vector& expecteds, const dvector& observeds, const double& cv){
	RETURN_ARRAYS_INCREMENT();
	assert(expecteds.indexmin()==observeds.indexmin() and expecteds.indexmax()==observeds.indexmax());
	dvariable nll = 0;
	for(int index=observeds.indexmin();index<=observeds.indexmax();index++){
		double observed = observeds(index);
		if(observed!=NA){
			dvariable expected = expecteds(index);
			nll += lognormal_nll_mean_cv(expected,observed,cv);
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return nll;
}

}