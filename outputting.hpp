#pragma once

namespace AdmbLib {

double value(const double& number){
	return number;
}

template<
	class Matrix
>
double value(const Matrix& matrix,int row,int col){
	if(row>=matrix.rowmin() and row<=matrix.rowmax() and col>=matrix.colmin() and col<=matrix.colmax()) 
		return value(matrix(row,col));
	else return NA;
}

#define REPORT(name) report<<#name<<"\n"<<name<<"\n\n";


template<
	class Any
>
void output_headers(std::ofstream& file,const std::string& header,const Any& any){
	file<<header;
}

template<
	class Any,
	class... Args
>
void output_headers(std::ofstream& file,const std::string& header,const Any& ignore,Args... args){
	output_headers(file,header,ignore);
	file<<"\t";
	output_headers(file,args...);
}

template<
	class Any
>
void output_values(std::ofstream& file,const int& row,const int& col,const std::string& ignore,const Any& any){
	file<<value(any,row,col);
}

template<
	class Any,
	class... Args
>
void output_values(std::ofstream& file,const int& row,const int& col,const std::string& ignore,const Any& any,Args... args){
	output_values(file,row,col,ignore,any);
	file<<"\t";
	output_values(file,row,col,args...);
}

template<
	class... Args
>
void output(
	const std::string& filename,
	const std::string& rowname, int rowmin, int rowmax,
	const std::string& colname, int colmin, int colmax,
	Args... args
){
	std::ofstream file(filename.c_str());
	file<<rowname<<"\t"<<colname<<"\t";
	output_headers(file,args...);
	file<<std::endl;

	for(int row=rowmin; row<=rowmax; row++){
		for(int col=colmin; col<=colmax; col++){
			file<<row<<"\t"<<col<<"\t";
			output_values(file,row,col,args...);
			file<<std::endl;
		}
	}
}

template<
	class Matrix1,
	class Matrix2
>
void output(
	const std::string& filename,
	const std::string& rowname, 
	const std::string& colname,
	const std::string& value1name,
	const Matrix1& matrix1,
	const std::string& value2name,
	const Matrix2& matrix2
){
	int colmin = min(matrix1.colmin(),matrix2.colmin());
	int colmax = max(matrix1.colmax(),matrix2.colmax());
	int rowmin = min(matrix1.rowmin(),matrix2.rowmin());
	int rowmax = max(matrix1.rowmax(),matrix2.rowmax());
	output(filename,rowname,rowmin,rowmax,colname,colmin,colmax,value1name,matrix1,value2name,matrix2);
}

}
