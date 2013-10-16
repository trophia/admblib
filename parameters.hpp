#pragma once

namespace AdmbLib {

// Parameter options
const int ParOptions = 4;
	const int ParOptionPhase = 1;
	const int ParOptionMin = 2;
	const int ParOptionMax = 3;
	const int ParOptionDefault = 4;

#define PAR_OPTIONS_INIT \
	int phase; \
	double min; \
	double max; \
	double defau;

#define PAR_OPTIONS(par) \
	phase = parOptions[ParOptionPhase]; \
	min = parOptions[ParOptionMin]; \
	max = parOptions[ParOptionMax]; \
	defau = parOptions[ParOptionDefault];

// Prior options
const int PriorOptions = 3;
	const int PriorOptionType = 1;
	const int PriorOptionPar1 = 2;
	const int PriorOptionPar2 = 3;

dvariable prior_like(const dvariable& value, const dvector& options){
	RETURN_ARRAYS_INCREMENT();
	const double pi = 3.14159265358979;
	const double halfLog2pi = 0.5*log(2*pi);
	dvariable nll;
	int type = options[PriorOptionType];
	double par1 = options[PriorOptionPar1];
	double par2 = options[PriorOptionPar2];
	switch (type){
		case 0: //none
			nll = 0;
			break;
		case 1: //normal
			nll = square(par1-value)/(2*square(par2)) + log(par2)
			  + halfLog2pi;
			break;
		case 2: //lognormal
			nll = square(log(par1)-log(value)+0.5*square(par2))/(2*square(par2))
				     + log(value) + log(par2) + halfLog2pi;
			break;
		case 3: //robust normal
			nll = -log(mfexp(-1*square((par1)-(value))/(2*square(par2)))+0.01)
				     + log(par2) + halfLog2pi;
			break;
		case 4: //robust lognormal
			nll=-log(mfexp(-1*square(log(par1)-log(value)+0.5*square(par2))
				     /(2*square(par2)))+0.01) + log(value) + log(par2) + halfLog2pi;
			break;
	}
	RETURN_ARRAYS_DECREMENT();
	return nll;
}

}