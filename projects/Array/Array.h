
#ifndef Array_h
#define Array_h
#include <ostream>
#include <stdexcept>


template<typename T, size_t S>
class Array{
	private:
		T tab[S];
		size_t s;

	public:

		Array();

		template<typename N, size_t SZ>
		Array(const Array<N,SZ>& );

		template<typename N, size_t SZ>
		Array(const N(&values)[SZ]);

		Array<T,S>& operator=(const Array<T,S>& );
		//~Array();
		const size_t size() const;
		bool empty() const;
		T& operator[](size_t i);
		const T& operator[](size_t i) const;
		T& at(size_t i);
		const T& at(size_t i) const;
		T& front() const;
		T& back() const;
		void fill(const T& val, size_t n);
		void swap(Array& o);
		void setTab(size_t i, T& val) { tab[i] = val; }
		template<typename N, size_t SZ>
		friend std::ostream& operator<<(std::ostream& os, const Array<N,SZ>& );


        template <typename U>
        class iterator {
                        private:
                            U* pos;
                        public:
                            iterator(U* element) { pos = element; } //vérifiée
                            iterator& operator++() { pos++; return *this; } //vérifiée
                            iterator& operator--() { pos--; return *this; } //vérifiée
                            iterator& operator+(size_t i){ pos += i; return *this; } //vérifiée
                            iterator& operator-(size_t i){ pos -= i; return *this; } //vérifiée
                            U& operator*() { return *pos; } //vérifiée
                            U& operator[](size_t i) { return pos[i]; } //vérifiée
                            const U& operator[](size_t i) const { return pos[i]; } //vérifiée
                            iterator operator++(int)
                                    {
                                    iterator tmp{*this};
                                    operator++();
                                    return tmp;
                                    }
                            iterator operator--(int)
                                    {
                                    iterator tmp{*this};
                                    operator--();
                                    return tmp;
                                    }
                            friend bool operator==(const iterator&a, const iterator& b)
                                    {
                                    return a.pos == b.pos;
                                    }
                            friend bool operator!=(const iterator&a, const iterator& b)
                                    {
                                    return a.pos != b.pos;
                                    }
                            friend size_t operator-(const iterator&a, const iterator& b){
                                    return a.pos - b.pos;
                                    }

        };
        typedef iterator<const T> const_array_iterator;
		typedef iterator<T> array_iterator;
		array_iterator begin() { return array_iterator(tab); }
		const_array_iterator cbegin() const{ return const_array_iterator(tab); }
		array_iterator end() { return array_iterator(tab+s); }
		const_array_iterator cend() const { return const_array_iterator(tab+s); }


        template <size_t S2> //vérifiée
        void fusion(const Array<T,S2>& Arr)
            {
				if(S-s<S2) 
					throw std::out_of_range("Not enough space to fusion");
				for(int i=0; i<Arr.size(); ++i)
					tab[s+i] = Arr[i];
				s += Arr.size();

            }

       template<size_t S2> 
	   void subset(const Array<T,S2>& Arr, size_t pos, size_t n)
        {
            if((S2 < n ) || (S < n)) throw std::out_of_range("subset goes out of range");
            for (int i = 0; i<n ; i++)
                tab[i] = Arr[pos+i];
			s = n;
        }



};

template<typename T, size_t S> //vérifiée
Array<T, S>::Array(){
		s = 0;
}

/*template<typename T, size_t S>
template<typename N, size_t SZ>
Array<T,S>::Array(const N(&values)[SZ]){
	s = (SZ < S) ? SZ : S;
	for(size_t i=0; i<s; ++i)
		tab[i] = values[i];
}*/

template<typename T, size_t S>
template<typename N, size_t SZ>
Array<T,S>::Array(const Array<N, SZ>& values){
	s = (SZ < S) ? SZ : S;
	for(size_t i=0; i<s; ++i)
		tab[i] = values[i];
}

/*template<typename T, size_t S> //vérifiée
Array<T,S>::~Array(){
	delete[] tab;
	s=0;
	tab = nullptr;
}*/



/* template<typename T, size_t S>  //vérifiée
Array<T,S>::Array(const Array& o){
//	if(s != o.s) throw std::out_of_range();
	for(int i=0; i<s; ++i)
		tab[i] = o.tab[i];
}*/

template<typename T, size_t S> //vérifiée
const size_t Array<T,S>::size() const {
	return s;
}


template<typename T, size_t S> //vérifiée
bool Array<T,S>::empty() const {
	return s==0;
}

template<typename T, size_t S> //vérifiée
T& Array<T,S>::operator[](size_t i){
	return tab[i];
}

template<typename T, size_t S> //vérifiée
const T& Array<T,S>::operator[](size_t i) const {
	return tab[i];
}

template<typename T, size_t S> //vérifiée
T& Array<T,S>::at(size_t i){
	if(s <= i)
		throw std::out_of_range();
	return tab[i];
}

template<typename T, size_t S> //vérifiée
const T& Array<T,S>::at(size_t i) const{
	if(s <= i)
		throw std::out_of_range();
	return tab[i];
}

template<typename T, size_t S> //vérifiée
T& Array<T,S>::front() const {
	return tab[0];
}

template<typename T, size_t S> //vérifiée
T& Array<T,S>::back() const {
	return tab[s-1];
}

template<typename T, size_t S> //vérifiée
void Array<T, S>::fill(const T& val, size_t n){
	if(S < n) throw std::out_of_range("out of range");	
	for(size_t i=0; i<n; ++i)
		tab[i] = val;
	s = n;	
}

template<typename T, size_t S> //vérifiée
void Array<T, S>::swap(Array& o){

	T* tmp = tab;
	tab = o.tab;
	o.tab = tmp;
}

template<typename T, size_t S>
Array<T,S>& Array<T,S>::operator=(const Array<T,S>& o)
{
    if(this == &o) return *this;
    else{
        for (size_t i = 0 ; i < s; i++)
                tab[i] = o.tab[i];
				return *this;
    }
}

/*template<typename T, size_t S>
std::ostream& operator<<(std::ostream& os, const Array<T,S>& Arr){
	os << "[";
	for(size_t i; i<Arr.size(); ++i){
		if(i!=0) os << ", ";
		os << Arr[i];
	}
	os << "]";
	return os;
}*/
#endif
