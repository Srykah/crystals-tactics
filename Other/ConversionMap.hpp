#ifndef CONVERSIONMAP_HPP_INCLUDED
#define CONVERSIONMAP_HPP_INCLUDED

#include <unordered_map>

template <typename M, typename N>
class ConversionMap
{
public:
    ConversionMap();
    ~ConversionMap() = default;

    bool addPair(const M& m, const N& n);
    bool addPair(const N& n, const M& m);

    M& operator [](const N& key) {
        return mNM[key];
    }

    const M& operator [](const N& key) const {
        return mNM[key];
    }

    N& operator [](const M& key) {
        return mMN[key];
    }

    const N& operator [](const M& key) const {
        return mMN[key];
    }

private:
    std::unordered_map<M,N> mMN;
    std::unordered_map<N,M> mNM;
};

#include "ConversionMap.inl"

#endif // CONVERSIONMAP_HPP_INCLUDED
