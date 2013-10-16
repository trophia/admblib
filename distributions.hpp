/**
 * @file distributions
 *
 * Functions related to probability distributions
 */

#pragma once

#include <cmath>

namespace AdmbLib {

/*
 * Some useful constants 
 */
const double pi = M_PI;
const double halfLog2Pi = 0.5*std::log(2*pi);

/**
 * Algebraic approximation to CDF of normal distribution
 *
 * Abramowitz and Stegun (1965). Accurate to 10e-5
 * 
 * @param  x   [description]
 * @param  mu  [description]
 * @param  std [description]
 * @return     [description]
 */
template<
	class X,
	class Mean,
	class Sd
>
dvariable normal_cdf(const X& x, const Mean& mean, const Sd& sd){
	RETURN_ARRAYS_INCREMENT();
   	const double pi = 3.141592653589793238462;
   	dvariable p;
    if(x-mean==0) p = 0.5;
	else {
		dvariable z = (x-mean)/sd;
      	dvariable t = 1 / (1 + 0.33267 * sqrt(z*z));
      	p = 0.4361836 * t - 0.120167 * pow(t,2) + 0.937298 * pow(t,3);
      	p = 1 - mfexp(-pow(z,2) / 2) / pow(2*pi,0.5) * p;
      	if (z < 0) p = 1 - p;
   		if (p < 0) p = 0;
	}
   	RETURN_ARRAYS_DECREMENT();
   	return p;
}

template<
	class From,
	class To,
	class Mean,
	class Sd
>
dvariable normal_integral(const To& from,const From& to,const Mean& mean,const Sd& sd){
	RETURN_ARRAYS_INCREMENT();
	dvariable integral = normal_cdf(to,mean,sd)-normal_cdf(from,mean,sd);
	RETURN_ARRAYS_DECREMENT();
	return integral;
}

dvariable normal_nll(const dvariable& x, const double& mu, const double& sigma){
	return log(sigma)+halfLog2Pi+square(x-mu)/(2*square(sigma));
}

dvariable lognormal_nll(const dvariable& x, const double& mu, const double& sigma){
	return log(x)+log(sigma)+halfLog2Pi+square(log(x)-mu)/(2*square(sigma));
}

dvariable lognormal_nll_mean_cv(const dvariable& x, const double& mean, const double& cv){
	double mean2 = square(mean);
	double var = square(mean*cv);
	return lognormal_nll(x,log(mean2/sqrt(var+mean2)),sqrt(log(1+var/mean2)));
}

}
