#ifndef IMETATEXT_H
#define IMETATEXT_H

#include <QObject>
#include <QDebug>
#include <vector>
#include <algorithm>
#include <typeinfo>

template <class T> class IMetaText
{
    friend class ISelection;
    template<class XV, class U> friend class MetaFontTrace;
    template<class U> friend class MetaLocalTrace;
    friend class PainterPenTrace;
    friend class PainterBrushTrace;

    template <class U> struct Element
    {
        int offset;
        U value;
        Element(const int& coffset,const U& cvalue) : offset(coffset), value(cvalue) {}
    };
    std::vector< Element<T> > s_elements;
public:
    IMetaText() {}
    void set(int begin, int end, const T&value) //SLOW
    {
        int pos=0;
        bool begun=0;
        for(uint i=0;i<s_elements.size();i++) {
            if(pos<begin&&pos+s_elements[i].offset>=begin&&pos<end&&pos+s_elements[i].offset>end) {
                begun=1;
                int newSize1=end-begin;
                int newSize2=pos+s_elements[i].offset-end;
                int oldSize=begin-pos;
                s_elements[i].offset=oldSize;
                s_elements.insert(s_elements.begin()+i+1,Element<T>(newSize1,value));
                s_elements.insert(s_elements.begin()+i+2,Element<T>(newSize2,s_elements[i].value));
            } else if(pos<begin&&pos+s_elements[i].offset>begin) {
                begun=1;
                int newSize=pos+s_elements[i].offset-begin;
                int oldSize=s_elements[i].offset-newSize;
                s_elements[i].offset=oldSize;
                s_elements.insert(s_elements.begin()+i+1,Element<T>(newSize,value));
            } else if(pos<end&&pos+s_elements[i].offset>end) {
                int newSize=pos+s_elements[i].offset-end;
                int oldSize=s_elements[i].offset-newSize;
                s_elements[i].offset=oldSize;
                s_elements.insert(s_elements.begin()+i+1,Element<T>(newSize,s_elements[i].value));
                s_elements[i].value=value;
            } else if(pos>=begin&&end>=pos+s_elements[i].offset) {
                s_elements[i].value=value;
            }

            pos+=s_elements[i].offset;
        }
        if(!begun) {
            s_elements.push_back(Element<T>(end-begin,value));
        } else if(end>=pos) {
            s_elements.push_back(Element<T>(end-pos,value));
        }
        cleanup();
    }

    T mode(int begin, int end) const //SLOW
    {
        if(begin==end) return get(begin);

        QMap<T,int> modeMap;

        int pos=0;
        bool begun=0;
        for(uint i=0;i<s_elements.size();i++) {
            if(pos<begin&&pos+s_elements[i].offset>=begin&&pos<end&&pos+s_elements[i].offset>end) {
                begun=1;
                modeMap[s_elements[i].value]+=end-begin;
            } else if(pos<=begin&&pos+s_elements[i].offset>begin) {
                begun=1;
                modeMap[s_elements[i].value]+=pos+s_elements[i].offset-begin;
            } else if(pos>=begin&&end>=pos+s_elements[i].offset) {
                begun=1;
                modeMap[s_elements[i].value]+=s_elements[i].offset;
            }

            pos+=s_elements[i].offset;
        }
        if(!begun) {
            Q_ASSERT(0);
        }

        T best;
        int maxim=0;
        for(int i=0;i<modeMap.size();i++) {
            if(modeMap.values()[i]>maxim) {
                maxim=modeMap.values()[i];
                best=modeMap.keys()[i];
            }
        }
        return best;
    }
    const T& get(int p) const //SLOW!!!
    {
        int posSoFar=-1;

        for(uint i=0;i<s_elements.size();i++)
        {
            if(p>posSoFar&&p-1<=posSoFar+s_elements[i].offset) {
                return s_elements[i].value;
            }
            posSoFar+=s_elements[i].offset;
        }
        Q_ASSERT(0);    //!!
        return *(new T);
    }
    void cleanup()
    {
        for(uint i=0;i<s_elements.size();i++)
        {
            if(s_elements[i].offset<=0)
            {
                if(s_elements.size()>1) {
                    s_elements.erase(s_elements.begin()+i);
                    i--;
                } else {
                    s_elements[i].offset=1;
                }
            }
            else if(i&&s_elements[i].value==s_elements[i-1].value)
            {
                s_elements[i-1].offset+=s_elements[i].offset;
                s_elements.erase(s_elements.begin()+i);
                i--;
            }
        }
    }
    void extend(int i,int len)
    {
        int posSoFar=-1;

        for(uint j=0;j<s_elements.size();j++)
        {
            if(i>=posSoFar && i-1<=posSoFar+s_elements[j].offset) {
                s_elements[j].offset+=len;
                return;
            }
            posSoFar+=s_elements[j].offset;
        }
        Q_ASSERT(0);    //!!
    }
    void contract(int i,int len)
    {
        int posSoFar=-1;

        i--;
        for(uint j=0;j<s_elements.size();j++)
        {
            if(i+1>posSoFar&&i<posSoFar+s_elements[j].offset) {//<=pos?
                int notClean=len-s_elements[j].offset;
                s_elements[j].offset-=len;
                cleanup();
                if(notClean>0) contract(posSoFar+1,notClean);
                return;
            }
            posSoFar+=s_elements[j].offset;
        }
        Q_ASSERT(0);    //!!
    }
};

#endif // IMETATEXT_H
