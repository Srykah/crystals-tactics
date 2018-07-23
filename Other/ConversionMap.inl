
template <typename M, typename N>
bool ConversionMap<M,N>::addPair(const M& m, const N& n)
{
    if (mMN.count(m) || mNM.count(n))
        return false;

    mMN.emplace(m,n);
    mNM.emplace(n,m);
}

template <typename M, typename N>
bool ConversionMap<M,N>::addPair(const M& m, const N& n)
{
    addPair(n,m);
}
