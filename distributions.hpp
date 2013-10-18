/**
 * @file distributions
 *
 * Functions related to probability distributions
 */

#pragma once

#include <cmath>

#include "traits.hpp"
#include "containers.hpp"

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

namespace Implementation {

	dvariable normal_nll_base(
		const dvariable& x, 
		const dvariable& mu, 
		const dvariable& sigma
	){
		return log(sigma)+halfLog2Pi+square(x-mu)/(2*square(sigma));
	}

	dvariable lognormal_nll_base(
		const dvariable& x, 
		const dvariable& mu, 
		const dvariable& sigma
	){
		return log(x)+log(sigma)+halfLog2Pi+square(log(x)-mu)/(2*square(sigma));
	}

	dvariable lognormal_nll_mean_cv_base(
		const dvariable& x,
		const dvariable& mean,
		const dvariable& cv
	){
		dvariable mean2 = square(mean);
		dvariable var = square(mean*cv);
		dvariable mu = log(mean2/sqrt(var+mean2));
		dvariable sigma = sqrt(log(1+var/mean2));
		return lognormal_nll_base(x,mu,sigma);
	}

	template<
		class X,
		class Mu,
		class Sigma
	>
	dvariable normal_nll(
		const std::false_type&, const X& x,
		const std::false_type&, const Mu& mu,
		const std::false_type&, const Sigma& sigma
	){
		return normal_nll_base(x,mu,sigma);
	}

	template<
		class X,
		class Mu,
		class Sigma
	>
	dvariable normal_nll(
		const std::true_type&, const X& x,
		const std::false_type&, const Mu& mu,
		const std::false_type&, const Sigma& sigma
	){
		return sum_items(x,normal_nll_base,mu,sigma);
	}

	template<
		class X,
		class Mu,
		class Sigma
	>
	dvariable normal_nll(
		const std::true_type&, const X& x,
		const std::true_type&, const Mu& mu,
		const std::false_type&, const Sigma& sigma
	){
		return sum_pairs(x,mu,normal_nll_base,sigma);
	}

	template<
		class X,
		class Mean,
		class Cv
	>
	dvariable lognormal_nll_mean_cv(
		const std::false_type&, const X& x,
		const std::false_type&, const Mean& mean,
		const std::false_type&, const Cv& cv
	){
		return lognormal_nll_mean_cv_base(x,mean,cv);
	}

	template<
		class X,
		class Mean,
		class Cv
	>
	dvariable lognormal_nll_mean_cv(
		const std::true_type&, const X& x,
		const std::false_type&, const Mean& mean,
		const std::false_type&, const Cv& cv
	){
		return sum_items(x,lognormal_nll_mean_cv_base,mean,cv);
	}

	template<
		class X,
		class Mean,
		class Cv
	>
	dvariable lognormal_nll_mean_cv(
		const std::true_type&, const X& x,
		const std::true_type&, const Mean& mean,
		const std::false_type&, const Cv& cv
	){
		return sum_pairs(x,mean,lognormal_nll_mean_cv_base,cv);
	}
}

template<
	class X,
	class Mean,
	class Cv
>
dvariable normal_nll(const X& x, const Mean& mean, const Cv& cv){
	return Implementation::normal_nll(
		IsContainer<X>(), x,
		IsContainer<Mean>(), mean,
		IsContainer<Cv>(), cv
	);
}

template<
	class X,
	class Mean,
	class Cv
>
dvariable lognormal_nll_mean_cv(const X& x, const Mean& mean, const Cv& cv){
	return Implementation::lognormal_nll_mean_cv(
		IsContainer<X>(), x,
		IsContainer<Mean>(), mean,
		IsContainer<Cv>(), cv
	);
}

}
