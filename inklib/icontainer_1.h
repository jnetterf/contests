#ifndef ICONTAINER_H
#define ICONTAINER_H

#include <iostream>
#include <list>
#include <ext/rope>
#include <deque>

#include <assert.h>

/* GOAL: Highly efficient data storage, especially optimized for repeating data (i.e., font names don't change that often). */
template<typename  T> class IContainer {
    friend class IParagraph;

    typename std::list<T> s_data;
    std::list<int> s_dataOffsets;

    typename std::list<T>::iterator s_it, s_begin,s_end;
    std::list<int>::iterator s_dataOffsets_it;
    int s_posInOffset;

    std::list< typename std::list<T>::iterator > s_it_hold;
    std::list< std::list<int>::iterator > s_dataOffsets_it_hold;
    std::list< int > s_posInOffset_hold;

    bool s_locked;    // true if locked for read only.

public:
    IContainer() : s_it(s_data.begin()), s_begin(s_data.begin()), s_end(s_data.end()), s_dataOffsets_it(s_dataOffsets.begin()),
        s_posInOffset(0), s_locked(0) {}

    void cleanup() {
    }

    inline void insert(const T& t) {
        // BEFORE CURRENT

        if(prevValueExists()&&prevValue()==t) {
//            std::cerr<<"!@"<<(bool)(s_it==s_begin)<<"/"<<s_posInOffset;
            prev();
            ++(*s_dataOffsets_it);
            next();
            next();
            return;
        }
//        std::cerr<<"!OK";


        if(s_it!=s_end) {
            ++(*s_dataOffsets_it);
            setValue(t);
            next();
        } else {
            s_data.insert(s_it,t);
            s_dataOffsets.insert(s_dataOffsets_it,1);
        }

        s_begin=s_data.begin();
        s_end=s_data.end();
    }

    inline void setValue(const T& t) {
        assert(s_it!=s_end);

        // CASE 0:
        //[1]
        //[2]
        if(*s_dataOffsets_it==1) {
            *s_it=t;
        }

        // CASE 1:
        // 1 [1] 1
        // 1 [2] 1
        else if(s_posInOffset&&s_posInOffset+1!=(*s_dataOffsets_it)) {
            int sizeOne=s_posInOffset, sizeTwo=1,sizeThree=*s_dataOffsets_it-sizeOne-sizeTwo;
            assert(sizeOne>0);
            assert(sizeTwo>0);
            assert(sizeThree>0);

            T value=*s_it;

            //TWO
            *s_dataOffsets_it=sizeTwo;
            s_posInOffset=0;

            //ONE
            s_data.insert(s_it,value);
            s_dataOffsets.insert(s_dataOffsets_it,sizeOne);

            s_begin=s_data.begin(); s_end=s_data.end();

            //THREE
            ++s_it; ++s_dataOffsets_it;

            s_data.insert(s_it,value);
            s_dataOffsets.insert(s_dataOffsets_it,sizeThree);
            s_begin=s_data.begin(); s_end=s_data.end();

            --s_it; --s_dataOffsets_it;
            --s_it; --s_dataOffsets_it;
            *s_it=t;
        }

        // CASE 2:
        //[1] 1  1
        //[2] 1  1

        else if(!s_posInOffset) {
            --(*s_dataOffsets_it);
            s_data.insert(s_it,t);
            s_dataOffsets.insert(s_dataOffsets_it,1);
            s_begin=s_data.begin(); s_end=s_data.end();
            prev();
        }

        // CASE 3:
        // 1  1 [1]
        // 1  1 [2]

        else {
            assert(s_posInOffset+1==*s_dataOffsets_it);
            --(*s_dataOffsets_it);
            --s_posInOffset;
            next();
            s_data.insert(s_it,t);
            s_dataOffsets.insert(s_dataOffsets_it,1);
            s_begin=s_data.begin(); s_end=s_data.end();
            s_posInOffset=0;
            prev();
        }
    }

    inline const T& value() const { return *s_it; }
    inline bool prevValueExists() { return s_posInOffset||s_it!=s_begin; }
    inline const T& prevValue() { if(s_posInOffset) return *s_it; --s_it; return *(s_it++); }

    inline bool remove() {
        assert(s_it!=s_end);
        if(*s_dataOffsets_it) {
            --*s_dataOffsets_it;
        } else {
            s_it=s_data.erase(s_it);
            s_dataOffsets_it=s_dataOffsets.erase(s_dataOffsets_it);
            s_posInOffset=0;
        }

        s_begin=s_data.begin();
        s_end=s_data.end();
        return 1;
    }

    inline bool next() {
        if(++s_posInOffset==*s_dataOffsets_it) {
            if(s_it==s_end) {
                --s_posInOffset;
                std::cerr<<"Tried to go past end of list."<<std::endl;
                return 0;
            }
            s_posInOffset=0;
            ++s_dataOffsets_it;
            return(++s_it!=s_end);
        } else if(s_posInOffset>=*s_dataOffsets_it) {
            assert(0);
        }
        return 1;
    }
    inline void next_unsafe() {
        if(++s_posInOffset==*s_dataOffsets_it) {
            s_posInOffset=0;
//            std::list<int>::iterator b=s_dataOffsets.begin();
//            std::cerr<<*b;
            ++s_dataOffsets_it;
            ++s_it;
        }  else if(s_posInOffset>=*s_dataOffsets_it) {
//            int l=*s_dataOffsets_it;
//            std::cerr<<"WARN!"<<l;
//            std::list<int>::iterator b=s_dataOffsets.begin();
//            std::cerr<<*b;
            assert(0);
        }
    }
    inline bool prev() {
        if(s_it==s_end||!s_posInOffset--) {
            if(s_begin==s_it) {
                std::cerr<<"Tried to go past begining of list."<<std::endl;
                ++s_posInOffset;
                return 0;   //Nothing done.
            }
            s_posInOffset=*(--s_dataOffsets_it)-1;
            return (--s_it!=s_begin);
        }
        return 1;
    }

    // backs up the iterator and allows the container to be read from the begining.
    inline void push() {
        s_it_hold.push_back(s_it);
        s_dataOffsets_it_hold.push_back(s_dataOffsets_it);
        s_posInOffset_hold.push_back(s_posInOffset);
    }
    inline void pop() {
        s_it=s_it_hold.back(); s_it_hold.pop_back();
        s_dataOffsets_it=s_dataOffsets_it_hold.back(); s_dataOffsets_it_hold.pop_back();
        s_posInOffset=s_posInOffset_hold.back(); s_posInOffset_hold.pop_back();

        s_begin=s_data.begin(); s_end=s_data.end();
    }

    inline void lock() { assert(!s_locked); s_locked=1; push(); s_it=s_data.begin(); s_dataOffsets_it=s_dataOffsets.begin(); s_posInOffset=0; }
    inline void unlock() { assert(s_locked); s_locked=0; pop(); }

    inline bool locked() { return s_locked; }
};

/*Goal: Efficient container without repitition, same API as IContainer*/
template<typename  T> class IUniqueContainer {
    friend class IParagraph;

    typename std::list<T> s_data;
    typename std::list<T>::iterator s_it, s_begin,s_end;

    int s_count;

    std::list< typename std::list<T>::iterator > s_it_hold;
    bool s_locked;    // true if locked for read only.

public:
    IUniqueContainer() : s_it(s_data.begin()), s_begin(s_data.begin()), s_end(s_data.end()), s_count(0), s_locked(0) {}

    inline void gotoStart() {
        assert(!s_locked);
        s_it=s_begin;
    }

    inline void insert(const T& t) {
        assert(!s_locked);
        ++s_count;
        s_data.insert(s_it,t);
        s_begin=s_data.begin();
        s_end=s_data.end();
        return;
    }

    inline void setValue(const T& t) {
        assert(!s_locked);

        (*s_it)=t;
    }

    inline const T& value() const { return *s_it; }
//    inline T& reference() { assert(!s_locked); return *s_it; }
    inline bool prevValueExists() { return s_it!=s_begin; }
    inline const T& prevValue() { --s_it; return *(s_it++); }

    inline bool remove() {
        assert(!s_locked);

        --s_count;
        s_it=s_data.erase(s_it);
        return 1;
    }

    inline bool next() {

        return(++s_it!=s_end);
    }
    inline void next_unsafe() {

        ++s_it;
    }
    inline bool prev() {

        return s_it--!=s_begin;
    }

    // backs up the iterator and allows the container to be read from the begining.
    inline void push() {

        s_it_hold.push_back(s_it);
    }
    inline void pop() {

        s_it=s_it_hold.back(); s_it_hold.pop_back();
        s_begin=s_data.begin(); s_end=s_data.end();
    }

    inline void lock() {

        assert(!s_locked);
        s_locked=1;
        push();
        s_it=s_data.begin();
    }

    inline void unlock() {


        assert(s_locked);
        s_locked=0;
        pop();
    }

    inline bool locked() { return s_locked; }
};

/*Goal: Uses the SGI-based rope */
template<typename  T> class IRopeContainer {
    friend class IParagraph;

    typename __gnu_cxx::rope<T> s_data;
    int s_i;

    int s_count;

    std::list< int > s_i_hold;
    bool s_locked;    // true if locked for read only.

public:
    IRopeContainer() : s_i(0), s_count(0), s_locked(0) {}

    inline void gotoStart() {
        assert(!s_locked);
        s_i=0;
    }

    inline void insert(const T& t) {
        assert(!s_locked);
        ++s_count;
        s_data.insert(++s_i,t);
        return;
    }

    inline void setValue(const T& t) {
        assert(!s_locked);

        s_data.replace(s_i,t);
    }

    inline T value() const { return s_data[s_i]; }
    inline bool prevValueExists() { return s_i; }
    inline const T& prevValue() { return s_data[s_i-1]; }

    inline bool remove() {
        assert(!s_locked);

        --s_count;
        s_data.erase(s_i--);
        return 1;
    }

    inline bool next() {
        return(++s_i!=s_count);
    }
    inline void next_unsafe() {

        ++s_i;
    }
    inline bool prev() {

        return s_i--;
    }

    // backs up the iterator and allows the container to be read from the begining.
    inline void push() {
        s_i_hold.push_back(s_i);
    }
    inline void pop() {
        s_i=s_i_hold.back(); s_i_hold.pop_back();
    }

    inline void lock() {
        assert(!s_locked);
        s_locked=1;
        push();
    }

    inline void unlock() {
        assert(s_locked);
        s_locked=0;
        pop();
    }

    inline bool locked() { return s_locked; }
};

#endif // ICONTAINER_H
