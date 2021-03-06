#include <cmath>
#include "horner.hpp"
#include <algorithm>
/*
 #include <execution> // for paralle algor.
*/
//! My function for power
/*!
 Since std::pow() is very expensive I create my version for integer
 powers. 
 */
double integerPow(const double & x, int n)
{
  double res{x};
  for (int i=2;i!=n+1;++i)res*=x;
  return res;
}

double eval (std::vector<double> const & a, double const & x){  
  double sum = a[0];
  for (std::vector<double>::size_type k = 1; k<a.size(); ++k){ 
    sum += a[k]*integerPow(x,k);// Pow is VERY expensive
  }
  return sum;
}

double  horner(std::vector<double> const & a, double const & x){
  double u = a.back();// last value
  for (auto  i=a.crbegin()+1;i!=a.crend();++i)
    u = u*x + *i;
  return u;
}

//! Evaluates polynomial in a set of points
std::vector<double>
evaluatePoly(std::vector<double> const & points,
		  std::vector<double> const & a,
                  polyEval method)
{
  std::vector<double> result(points.size());
  auto compute=[&a,&method] (double const & x){return method(a,x);};
  std::transform(points.begin(),points.end(),result.begin(),compute);
  return result;
}

/* NOT WORKING UNTIL IMPLEMENTED IN THE COMPILER
//! Evaluates polynomial in a set of points (parallel version)
std::vector<double>
evaluatePoly_par(std::vector<double> const & points,
		  std::vector<double> const & a,
                  polyEval method)
{
  std::vector<double> result(points.size());
  auto compute=[&a,&method] (double const & x){return method(a,x);};
  std::transform(std::execution::par, points.begin(),points.end(),result.begin(),compute);
  return result;
}
*/

