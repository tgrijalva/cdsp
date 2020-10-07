#ifndef complex_compat_h
#define complex_compat_h

#ifdef __cplusplus

#include <cmath>
#include <complex>

typedef std::complex<float> float_complex;
typedef std::complex<double> double_complex;
typedef std::complex<long double> long_double_complex;

#else

#include <tgmath.h>

typedef float complex float_complex;
typedef double complex double_complex;
typedef long double complex long_double_complex;

#define float_complex(r,i) ((float)(r) + ((float)(i))*I)
#define double_complex(r,i) ((double)(r) + ((double)(i))*I)
#define long_double_complex(r,i) ((long double)(r) + ((long double)(i))*I)

#define real(x) creal(x)
#define imag(x) cimag(x)
#define abs(x) fabs(x)
#define arg(x) carg(x)

#endif  // #ifdef __cplusplus

#endif /* complex_compat_h */
