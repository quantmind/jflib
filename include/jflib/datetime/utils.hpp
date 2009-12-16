

#ifndef __DATETIME_UTILS_JFLIB_HPP__
#define __DATETIME_UTILS_JFLIB_HPP__



namespace jflib  {


inline long counting30360(unsigned d1, unsigned d2,
 						  unsigned m1, unsigned m2,
 						  unsigned y1, unsigned y2)  {
 	return 360*(y2 - y1) + 30*(m2 - m1) + (d2 - d1);
}

template<class D>
inline double ActActYears(const D& dte) 	{
	unsigned  y = dte.year();
	unsigned  r = y % 4;
	double    a = r > 0 ? 1.0 : 0.0;
	return y + double(D::daydiff(D(y,1,1),dte)) / (365.0 + a);
}


}


#endif // __DATETIME_UTILS_JFLIB_HPP__

