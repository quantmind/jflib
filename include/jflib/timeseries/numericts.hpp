///////////////////////////////////////////////////////////////////////////////
//

#ifndef __NUMERIC_TIMESERIES_MAP_HPP_
#define __NUMERIC_TIMESERIES_MAP_HPP_

#include <jflib/timeseries/timeseries_map.hpp>
#include <jflib/datetime/date.hpp>


namespace jflib { namespace timeseries { namespace numeric {

	template<class> class tsoper;
	template<class> class NewPair;

	/** \breif Base class for timeseries operators
	 *  \ingroup timeseries
	 *
	 *	This class define the interfaces for handling timeseries operators
	 */
	template<class TS>
	class tsOperBase {
	public:
		typedef TS													tstype;
		typedef typename tstype::key_type							key_type;
		typedef typename tstype::mapped_type						numtype;
		typedef typename tstype::value_type							value_type;
		typedef typename tstype::const_iterator						const_iterator;
		typedef typename tstype::iterator							iterator;
		typedef NewPair<tstype>										pairtype;
		typedef pairtype*											pairptr;

		virtual ~tsOperBase(){}

		virtual pairptr find(const key_type& key) const = 0;

	protected:
		virtual void fill(tstype& ts) const = 0;
    };

	template<class TS>
	class NewPair  {
	public:
		typedef TS								tstype;
		typedef typename tstype::key_type 		key_type;
		typedef typename tstype::mapped_type  	numtype;

		NewPair(){}
		NewPair* available(const key_type& key, numtype v)  {
			first  = key;
			second = v;
			return this;
		}
		key_type	first;
		numtype     second;
	private:
		NewPair(const NewPair& rhs);
		NewPair& operator = (const NewPair& rhs);
	};


	namespace {


		template<class TS>
		class tsOperImpl: public tsOperBase<TS>  {
		public:
			typedef tsOperBase<TS>					tsoperbase;
			typedef typename tsoperbase::pairtype	pairtype;
			typedef typename tsoperbase::pairptr	pairptr;
			tsOperImpl():m_pair(new pairtype){}
			~tsOperImpl() {delete m_pair;}
		protected:
			mutable pairptr m_pair;
		};

		template<class TS, class L, template<class,class> class Op, class R> class tsoperator;

	}


	/** \brief Timeseries operator class
	 *
	 */
	template<class TS>
	class tsoper: public tsOperBase<TS>  {
    public:
		typedef TS								tstype;
		typedef tsOperBase<tstype>				tsoperbase;
		typedef boost::shared_ptr<tsoperbase>	operptr;
		typedef typename tsoperbase::key_type	key_type;
		typedef typename tsoperbase::pairtype	pairtype;
		typedef typename tsoperbase::pairptr	pairptr;

		tsoper(const tsoper& rhs):m_oper(rhs.m_oper),m_eval(rhs.m_eval){}

		tsoper& operator = (const tsoper& rhs) {m_oper = rhs.m_oper; return *this;}

		/// \brief Template constructor
		template<class L, template<class,class> class Op, class R>
		static tsoper make(const L& lhs, const R& rhs) {
			typedef tsoperator<tstype,L,Op,R> tsimpl;
			operptr oper(new tsimpl(lhs,rhs));
			tsoper ts(oper);
			return ts;
		}

		pairptr find(const key_type& key) const {
			return m_oper->find(key);
		}

		const tstype& apply() const {
			if(m_eval) {
				return m_ts;
			}
			else {
				tsoper& op = this->noConst();
				op.fill(op.m_ts);
				op.m_eval = true;
				return m_ts;
			}
		}

	protected:
		tsoper();
		explicit tsoper(const operptr& oper):m_oper(oper){}
		operptr		m_oper;
		tstype		m_ts;
		bool		m_eval;

		tsoper& 	noConst() const { return const_cast<tsoper&>(*this); }
		void fill(tstype& ts) const {m_oper->fill(ts);}
	};

}}}

#include <jflib/timeseries/impl/numericts_impl.hpp>

#endif	//	__NUMERIC_TIMESERIES_MAP_HPP_
