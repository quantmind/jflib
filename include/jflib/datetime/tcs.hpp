
#ifndef		__TRADING_CENTRES_HPP__
#define		__TRADING_CENTRES_HPP__


#include <jflib/jflib.hpp>

namespace jflib {


// Interface class for TradingCentre
template<class T>
class TradingCentreBase {
public:
	typedef T									date_type;
	typedef typename date_type::day_iterator	day_iterator;

    virtual ~TradingCentreBase(){}

    virtual bool isbizday(const date_type& date) const {QM_FAIL("not implemented");}

    virtual std::string code() const {return "";}
    virtual long        numbizdays(const date_type& start, const date_type& end) const;
    virtual date_type   nextbizday(const date_type& date, long days = 0) const;
    virtual date_type   prevbizday(const date_type& date, long days = 0) const;
    virtual unsigned    size() const {return 1;}
protected:
    TradingCentreBase(){}
};


template<class T>
class TradingCentre: public TradingCentreBase<T> {
public:
	typedef boost::shared_ptr<TradingCentre<T> >	ptr_type;

	static ptr_type make(const std::string& code) {return ptr_type(new TradingCentre(code));}

	std::string code() const {return m_code;}
protected:
	TradingCentre(const std::string& code):m_code(code){}
private:
	std::string	m_code;
};



template<class T>
class TradingCentres: public TradingCentreBase<T> {
public:
	typedef T	date_type;
	typedef TradingCentre<T>                		value_type;
	typedef boost::shared_ptr<value_type>			ptr_type;
	typedef std::vector<ptr_type>		    		container;
	typedef typename container::iterator      		iterator;
	typedef typename container::const_iterator		const_iterator;

	TradingCentres():m_tcs(new container){}
	TradingCentres(const std::string& codes):m_tcs(new container) {if(codes.length()) push_back(codes);}
	TradingCentres(const ptr_type& tc):m_tcs(new container) {push_back(tc);}
	TradingCentres(const TradingCentres& tc):m_tcs(tc.m_tcs){}

	void            push_back(const std::string& codes);
	void            push_back(const ptr_type& tc);
	void            push_back(const TradingCentres& tc);

    bool 		isbizday(const date_type& date) const;
    std::string code() const;
    unsigned    size() const {return m_tcs->size();}

    iterator	begin() {return m_tcs->begin();}
    iterator	end()   {return m_tcs->end();}
    const_iterator	begin() const {return m_tcs->begin();}
    const_iterator	end()   const {return m_tcs->end();}
private:
    boost::shared_ptr<container>	m_tcs;
};



template<class D>
inline long TradingCentreBase<D>::numbizdays(const D& start, const D& end) const   {
    if(end < start) return 0;
    day_iterator itr(start);
    long b = 0;
    for(; itr<=end; ++itr)
    	if(this->isbizday(*itr)) b++;
    return b;
}


template<class D>
inline D TradingCentreBase<D>::nextbizday(const D& date, long days) const  {
	if(days < 0)
		return this->prevbizday(date,-days);
	day_iterator itr(date);
	long d = 0;
	while(d <= days)  {
		if(this->isbizday(*itr)) d++;
		++itr;
	}
	return D(*(--itr));
}


template<class D>
inline D TradingCentreBase<D>::prevbizday(const D& date, long days) const    {
	if(days < 0)
		return this->nextbizday(date,-days);
	day_iterator itr(date);
	long d = 0;
	while(d <= days)  {
		if(this->isbizday(*itr)) d++;
		--itr;
	}
	return D(*(++itr));
}




template<class D>
inline std::string TradingCentres<D>::code() const {
	if(this->size() == 0) return "";
	const_iterator it = this->begin();
	std::string co = (*it)->code();
	++it;
	for(;it!=this->end();++it)
		co += "," + (*it)->code();
	return co;
}


template<class D>
inline void TradingCentres<D>::push_back(const typename TradingCentres<D>::ptr_type& tc)  {
	if(!tc) return;
    for(iterator it = this->begin();it!=this->end();++it)
    	if(*it == tc) return;
    m_tcs->push_back(tc);
}


template<class D>
inline void TradingCentres<D>::push_back(const TradingCentres<D>& tc)  {
	for(const_iterator it = tc.begin();it!=tc.end();++it)
		this->push_back(*it);
}

template<class D>
inline void TradingCentres<D>::push_back(const std::string& codes)  {
	stdstrings co = split(codes,",");
	for(stdstrings::iterator it=co.begin();it!=co.end();++it)  {
		//TC tc = tc::get(*it);
		//this->push_back(tc);
	}
}


template<class D>
inline bool TradingCentres<D>::isbizday(const D& date) const    {
	if(!this->size()) return !date.isweekend();
	for(const_iterator it=this->begin();it!=this->end();++it)
		if(!(*it)->isbizday(date)) return false;
    return true;
}






}

#endif	//	__TRADING_CENTRES_HPP__

