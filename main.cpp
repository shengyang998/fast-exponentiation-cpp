#include<iostream>
#include<ctime>
#include<cmath>

#define ULL unsigned long long
#define LL long long
using namespace std;

// recursively 
double pow_rec(double a, int n){
  if (n==0) return 1;
  else if (n==1) return a;
  else {
    double t = pow_rec(a, n/2);
    return t * t * pow_rec(a, n % 2);
  }
}

// normal loop
double pow_loop(double a, int n){
  double ret = 1;
  while (n--){
    ret *= a;
  }
  return ret;
}

// loop with binary
template<class myT>
myT pow_loop_fast(myT base, int n){
  myT ret = 1;
  while (n){
    if (n & 1) // if it is an odd number // eq to (exp % 2) but 2 times faster
        ret *= base;
    base *= base; 
    n >>= 1;
  }
  return ret;
}

// std version of pow
// ...

// ipow
template<class T>
T ipow(T base, int exp)
{
    T result = 1;
    while (exp) {
        if (exp & 1) // eq to (exp % 2) but 2 times faster
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

// optimized ipow
template<class T>
T opt_ipow(T base, unsigned int exp);

int main(){
  long long k = 10000000; int i=0;
  double m = 2.0;
  int n = 128; 
  clock_t start_a, end_a, start_b, end_b, start_c, end_c, start_d, end_d, start_e, end_e, start_f, end_f;

  double a, b, c, d, e, f;

  start_a = clock();
  for (i=0; i<k; i++)
      a = pow_rec(m, n);
  end_a = clock();

  start_b = clock();
  for (i=0; i<k; i++)
      b = pow_loop(m, n);
  end_b = clock();

  start_c = clock();
  for (i=0; i<k; i++)
      c = pow_loop_fast(m, n);
  end_c = clock();

  start_d = clock();
  for (i=0; i<k; i++)
      d = ::std::pow(m, n);
  end_d = clock();
  
  start_e = clock();
  for (i=0; i<k; i++)
      e = ipow(m, n);
  end_e = clock();

  start_f = clock();
  for (i=0; i<k; i++)
      f = opt_ipow(m, n);
  end_f = clock();

  cout<<"recursive  : "<<a<<" with "<<(end_a-start_a)/double(k)<<" clocks per loop. "<<endl
      <<"normal loop: "<<b<<" with "<<(end_b-start_b)/double(k)<<" clocks per loop. "<<endl
      <<"fast loop  : "<<c<<" with "<<(end_c-start_c)/double(k)<<" clocks per loop. "<<endl
      <<"standard   : "<<d<<" with "<<(end_d-start_d)/double(k)<<" clocks per loop. "<<endl
      <<"ipow       : "<<e<<" with "<<(end_e-start_e)/double(k)<<" clocks per loop. "<<endl
      <<"opt ipow   : "<<f<<" with "<<(end_f-start_f)/double(k)<<" clocks per loop. "<<endl
      <<endl;
  return 0;
}

// optimized ipow
template<class T>
T opt_ipow(T base, unsigned int exp) {
    static const unsigned int highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 255, // anything past 63 is a guaranteed overflow with base > 1
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
    };

    T result = 1;

    switch (highest_bit_set[exp]) {
    case 255: // we use 255 as an overflow marker and return 0 on overflow/underflow
        if (base == 1)  return 1;
        if (base == -1) return 1 - 2 * (exp & 1);
        return 0;
    case 6:
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    case 5:
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    case 4:
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    case 3:
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    case 2:
        if (exp & 1) result *= base;
        exp >>= 1;
        base *= base;
    case 1:
        if (exp & 1) result *= base;
    default:
        return result;
    }
}
