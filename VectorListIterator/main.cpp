#include <iostream>
#include <iterator>
#include <vector>
#include <list>

template<class T>
class VectorList {
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    template<class It>
    void append(It p, It q) {
        if (p != q)
            data_.push_back(VectT(p,q));
    }

    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const {
        size_t size = 0;
        for(auto it: data_) {
            size += it.size();
        }
        return size;
    }

    class const_iterator : public std::iterator <std::bidirectional_iterator_tag, value_type> {
    public:
        using lcIt = typename ListT::const_iterator;
        using vcIt = typename VectT::const_iterator;
        value_type* data_;
        lcIt listIt_;
        vcIt vecIt_;

        const_iterator () = default;
        const_iterator (const const_iterator&) = default;
        const_iterator (lcIt listIt, vcIt vecIt) :
            listIt_(listIt), vecIt_(vecIt) {
            data_ = const_cast<value_type*> (&*vecIt_);
        }

        const_iterator& operator-- () {
            if(listIt_->begin() == vecIt_) {
                --listIt_;
                vecIt_ = listIt_->end();
            }
            data_ = const_cast<value_type*> (&*--vecIt_);
            return *this;
        }

        const_iterator& operator++ () {
            if(--listIt_->end() == vecIt_) {
                ++listIt_;
                vecIt_ = listIt_->begin();
                data_ = const_cast<value_type*> (&*vecIt_);
                return *this;
            }
            data_ = const_cast<value_type*> (&*++vecIt_);
            return *this;
        }

        value_type& operator* () const { return *data_; }
        value_type* operator->() const { return  data_; }
        const_iterator& operator-- (int) { return --*this; }
        const_iterator& operator++ (int) { return ++*this; }
        bool operator == (const const_iterator cIt) { return cIt.data_ == data_ ? true : false; }

        bool operator !=(const const_iterator cIt) { return !(*this == cIt); }
    };

    class const_reverse_iterator : public std::iterator <std::bidirectional_iterator_tag, value_type> {
    public:
        using lcrIt = typename ListT::const_reverse_iterator;
        using vcrIt = typename VectT::const_reverse_iterator;
        value_type* data_;
        lcrIt lisCRtIt_;
        vcrIt vecCRIt_;

        const_reverse_iterator () = default;
        const_reverse_iterator (const const_reverse_iterator&) = default;
        const_reverse_iterator (lcrIt listCRIt, vcrIt vecCRIt) :
            lisCRtIt_(listCRIt), vecCRIt_(vecCRIt) {
            data_ = const_cast<value_type*> (&*vecCRIt_);
        }

        const_reverse_iterator& operator-- () {
            if(lisCRtIt_->rbegin() == vecCRIt_) {
                --lisCRtIt_;
                vecCRIt_ = lisCRtIt_->rend();
            }
            data_ = const_cast<value_type*> (&*--vecCRIt_);
            return *this;
        }

        const_reverse_iterator& operator++ () {
            if(--lisCRtIt_->rend() == vecCRIt_) {
                ++lisCRtIt_;
                vecCRIt_ = lisCRtIt_->rbegin();
                data_ = const_cast<value_type*> (&*vecCRIt_);
                return *this;
            }
            data_ = const_cast<value_type*> (&*++vecCRIt_);
            return *this;
        }

        value_type& operator* () const { return *data_; }
        value_type* operator->() const { return  data_; }
        const_reverse_iterator& operator-- (int) { return --*this; }
        const_reverse_iterator& operator++ (int) { return ++*this; }
        bool operator == (const const_reverse_iterator cIt) { return cIt.data_ == data_ ? true : false; }
        bool operator !=(const const_reverse_iterator cIt) { return !(*this == cIt); }
    };

    const_iterator begin() const { return const_iterator(data_.begin(), data_.begin()->begin()); }
    const_iterator end() const { return const_iterator(--data_.end(), (--data_.end())->end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(data_.rbegin(), data_.rbegin()->rbegin()) ; }
    const_reverse_iterator rend()   const { return const_reverse_iterator(--data_.rend(), (--data_.rend())->rend()) ; }

private:
    ListT data_;
};


int main() {
    VectorList<int> vlist;
    std::vector<int> v1 = {45,1,2,3};
    std::vector<int> v2 = {4,5,6,79};
    vlist.append(v1.begin(), v1.end());
    vlist.append(v2.begin(), v2.end());
    std::cout << *++++++++vlist.rbegin() << std::endl;
    std::cout << *----vlist.rend() << std::endl;
    return 0;
}
