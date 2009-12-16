
#include <jflib/python/pyconfig.hpp>
#include <jflib/random/all.hpp>
#include <boost/math/distributions/normal.hpp>


namespace jflib { namespace python {

namespace py = boost::python;
namespace jm = jflib::math;

typedef jm::random<boost::math::normal_distribution<double> > random;

void random_wrap() {

}




}}
