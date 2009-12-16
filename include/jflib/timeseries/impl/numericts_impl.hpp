
namespace jflib { namespace timeseries { namespace numeric { namespace {


	/////////////////////////////////////////////////////////////////////////////////////////
	//	1. number - tserie
	template<class tstype, template<class,class> class Op>
	class tsoperator<tstype, typename tstype::mapped_type, Op, tstype>: public tsOperImpl<tstype> {
	public:
		typedef tsOperImpl<tstype>					basetype;
		typedef typename tstype::key_type			key_type;
		typedef typename tstype::mapped_type		numtype;
		typedef typename tstype::const_iterator		const_iterator;
		typedef typename basetype::pairptr			pairptr;
		typedef Op<numtype,numtype>					optype;

		tsoperator(numtype lhs, const tstype& rhs):m_num(lhs),m_ts(rhs){}

		bool iterable() const {return true;}



		pairptr find(const key_type& key) const {
			const_iterator it = m_ts->find(key);
			if(it != m_ts->end())
				return m_pair->available(key,optype::apply(m_num,it->second));
			else
				return 0;
		}

		void fill(tstype& ts) const {
			for(const_iterator it=m_ts.begin(); it!=m_ts.end(); ++it)  {
				ts.insert(value_type(it->first,optype::apply(m_num,it->second)));
			}
		}

	protected:
		friend class tsoper;
		numtype		  m_num;
		tstype		  m_ts;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};

	/////////////////////////////////////////////////////////////////////////////////////////
	//	2. timeseries - number
	template<template<class,class> class Op>
	class tsoperator<tsoper::tstype,Op,double>: public tsOperImpl {
	public:
		typedef Op<numtype,numtype>		optype;
		tsoperator(const tstype& lhs, numtype rhs):m_num(rhs),m_ts(&lhs){}

		pairptr find(const key_type& key) const {
			const_iterator it = m_ts->find(key);
			if(it != m_ts->end())
				return m_pair->available(key,optype::apply(it->second,m_num));
			else
				return 0;
		}

		void fill(tstype& ts) const {
			for(const_iterator it=m_ts->begin(); it!=m_ts->end(); ++it)  {
				ts.insert(value_type(it->first,optype::apply(it->second,m_num)));
			}
		}

	protected:
		friend class tsoper;
		numtype		  m_num;
		const tstype* m_ts;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//	3. number - tsoper
	template<template<class,class> class Op>
	class tsoperator<double,Op,tsoper>: public tsOperImpl {
	public:
		typedef Op<numtype,numtype>		optype;
		tsoperator(numtype lhs, const tsoper& rhs):m_num(lhs),m_ts(rhs){}

		pairptr find(const key_type& key) const {
			pairptr it = m_ts.find(key);
			if(it)  {
				it->second = optype::apply(m_num,it->second);
				return it;
			}
			else
				return 0;
		}

		void fill(tstype& ts) const {
			m_ts.fill(ts);
			for(tstype::iterator it=ts.begin();it!=ts.end();++it) {
				it->second = optype::apply(m_num,it->second);
			}
		}

	protected:
		friend class tsoper;
		numtype	 m_num;
		tsoper	 m_ts;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//	4. tsoper - number
	template<template<class,class> class Op>
	class tsoperator<tsoper,Op,double>: public tsOperImpl {
	public:
		typedef Op<numtype,numtype>		optype;
		tsoperator(const tsoper& lhs, numtype rhs):m_num(rhs),m_ts(lhs){}

		pairptr find(const key_type& key) const {
			pairptr it = m_ts.find(key);
			if(it)  {
				it->second = optype::apply(it->second,m_num);
				return it;
			}
			else
				return 0;
		}

		void fill(tstype& ts) const {
			m_ts.fill(ts);
			for(tstype::iterator it=ts.begin();it!=ts.end();++it) {
				it->second = optype::apply(it->second,m_num);
			}
		}

	protected:
		friend class tsoper;
		numtype	 m_num;
		tsoper   m_ts;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};

	/////////////////////////////////////////////////////////////////////////////////////////
	//	5. tstype - tstype
	template<template<class,class> class Op>
	class tsoperator<tsoper::tstype,Op,tsoper::tstype>: public tsOperImpl {
	public:
		typedef Op<numtype,numtype>		optype;
		tsoperator(const tstype& elem1, const tstype& elem2):m_elem1(&elem1),m_elem2(&elem2){}

		pairptr find(const key_type& key) const {
			const_iterator il = m_elem1->find(key);
			const_iterator ir = m_elem2->find(key);
			if(il != m_elem1->end() && ir != m_elem2->end())
				return m_pair->available(key,optype::apply(il->second,ir->second));
			else
				return 0;
		}

		void fill(tstype& ts) const {
			const_iterator ir;
			for(const_iterator il=m_elem1->begin(); il!=m_elem1->end(); ++il)  {
				ir = m_elem2->find(il->first);
				if(ir != m_elem2->end())  {
					ts.insert(value_type(ir->first,optype::apply(il->second,ir->second)));
				}
			}
		}
	protected:
		friend class tsoper;
		const tstype* m_elem1;
		const tstype* m_elem2;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//	6. tstype - tsoper
	template<template<class,class> class Op>
	class tsoperator<tsoper::tstype,Op,tsoper>: public tsOperImpl {
	public:
		typedef Op<numtype,numtype>		optype;

		tsoperator(const tstype& elem1, const tsoper& elem2):m_elem1(&elem1),m_elem2(elem2){}

		pairptr find(const key_type& key) const {
			const_iterator it = m_elem1->find(key);
			if(it != m_elem1->end())  {
				pairptr pa = m_elem2.find(key);
				if(pa) {
					pa->second = optype::apply(it->second,pa->second);
					return pa;
				}
			}
			return 0;
		}

		void fill(tstype& ts) const {
			const_iterator ir;
			pairptr pa;
			for(const_iterator it=m_elem1->begin(); it!=m_elem1->end(); ++it)  {
				pa = m_elem2.find(it->first);
				if(pa)  {
					pa->second = optype::apply(it->second,pa->second);
					ts.insert(value_type(pa->first,pa->second));
				}
			}
		}
	protected:
		friend class tsoper;
		const tstype* m_elem1;
		tsoper m_elem2;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//	7. tsoper - tstype
	template<template<class,class> class Op>
	class tsoperator<tsoper,Op,tsoper::tstype>: public tsOperImpl {
	public:
		typedef Op<numtype,numtype>		optype;

		tsoperator(const tsoper& elem1, const tstype& elem2):m_elem1(&elem2),m_elem2(elem1){}

		pairptr find(const key_type& key) const {
			const_iterator it = m_elem1->find(key);
			if(it != m_elem1->end())  {
				pairptr pa = m_elem2.find(key);
				if(pa) {
					pa->second = optype::apply(pa->second,it->second);
					return pa;
				}
			}
			return 0;
		}

		void fill(tstype& ts) const {
			pairptr pa;
			for(const_iterator it=m_elem1->begin(); it!=m_elem1->end(); ++it)  {
				pa = m_elem2.find(it->first);
				if(pa)  {
					pa->second = optype::apply(pa->second,it->second);
					ts.insert(value_type(pa->first,pa->second));
				}
			}
		}
	protected:
		friend class tsoper;
		const tstype* m_elem1;
		tsoper m_elem2;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};

	/////////////////////////////////////////////////////////////////////////////////////////
	//	8. tsoper - tsoper
	// This is the most inefficient of operations since it requires a double search
	template<template<class,class> class Op>
	class tsoperator<tsoper,Op,tsoper>: public tsOperImpl {
	public:
		typedef Op<numtype,numtype>		optype;

		tsoperator(const tsoper& elem1, const tsoper& elem2):m_elem1(elem1),m_elem2(elem2){}

		pairptr find(const key_type& key) const {
			pairptr il = m_elem1.find(key);
			if(il)  {
				pairptr ir = m_elem2.find(key);
				if(ir)  {
					ir->second = optype::apply(il->second,ir->second);
					return ir;
				}
			}
			return 0;
		}

		void fill(tstype& ts) const {
			m_elem1.fill(ts);
			pairptr pa;
			for(iterator it = ts.begin(); it != ts.end(); ++it)  {
				pa = m_elem2.find(it->first);
				if(pa)
					it->second = optype::apply(it->second, pa->second);
				else  {
					ts.erase(it++);
				}
			}
		}
	protected:
		friend class tsoper;
		tsoper m_elem1;
		tsoper m_elem2;
	private:
		tsoperator(const tsoperator& rhs);
		tsoperator& operator = (const tsoperator& rhs);
	};

}}}}
