#pragma once

#include "na.hpp"

namespace AdmbLib {

template<
	class Container,
	typename Func,
	typename... Args
>
dvariable sum_items(
	const Container& container,
	Func func,
	Args... args
){
	RETURN_ARRAYS_INCREMENT();
	dvariable sum = 0;
	for(int index=container.indexmin();index<=container.indexmax();index++){
		auto& value = container[index];
		if(value!=NA){
			sum += func(value,args...);
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return sum;
}


template<
	class Container1,
	class Container2,
	typename Func,
	typename... Args
>
dvariable sum_pairs(
	const Container1& container1, 
	const Container2& container2,
	Func func,
	Args... args
){
	RETURN_ARRAYS_INCREMENT();
	assert(container1.indexmin()==container2.indexmin() and container2.indexmax()==container2.indexmax());
	dvariable sum = 0;
	for(int index=container1.indexmin();index<=container1.indexmax();index++){
		auto& value1 = container1[index];
		auto& value2 = container2[index];
		if(value1!=NA and value2!=NA){
			sum += func(value1,value2,args...);
		}
	}
	RETURN_ARRAYS_DECREMENT();
	return sum;
}

}
