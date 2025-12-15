#ifndef VKSTD_H
#define VKSTD_H
#include <string>
#include <type_traits>

using std::string;

namespace vkstd {

template< typename >
inline constexpr bool vk_false_v{ false };

template< typename T > // is value_type CHAR
using IsVec1dimChar = std::enable_if_t<
    (  std::is_integral_v<typename std::remove_reference_t<T>::value_type>
     && std::is_same_v<typename std::remove_reference_t<T>::value_type, char> )
    , bool >;
// using IsVec1dimChar = std::enable_if_t<std::is_same_v<T, std::vector<char>>, bool >;

template< typename T > // is value_type STRING
using IsVec1dimStr = std::enable_if_t<std::is_same_v<typename std::remove_reference_t<T>::value_type, std::string>, bool >;

// template< typename T > // is value_type STRING
// using IsVec1dimStr = std::enable_if_t<std::is_same_v<T, std::vector<std::string>>, bool >;

template< typename T >  // is value_type numeric
using IsVec1dimNum_old = std::enable_if_t<
    (std::is_same_v<T, std::vector<int>> || std::is_same_v<T, std::vector<unsigned int>>
     || std::is_same_v<T, std::vector<long>>
     || std::is_same_v<T, std::vector<long long>>
     || std::is_same_v<T, std::vector<double>>
     || std::is_same_v<T, std::vector<float>>)
    , bool >;

template< typename T >  // is value_type numeric EXCEPT CHAR
using IsVec1dimNum = std::enable_if_t<
    (  std::is_integral_v<typename std::remove_reference_t<T>::value_type>
         && !std::is_same_v<typename std::remove_reference_t<T>::value_type, char> )
    , bool>;


template < class T, IsVec1dimNum<T> = true >
string toString(T&& data, int lim =-1) {
    static_assert(!std::is_array_v<T> == true, "Unsupported type");
    string res{""};
    auto count{0};
    for( const auto &v : data){
        ++count;
        res += (res.empty() ? "" : ", ") + std::to_string(v);
        if ( !(lim < 0) && count > lim) {
            res += ", ...";
            break;
        }
    }
    res = "["+res+"](" + std::to_string(std::size(data))+")";
    return res;
}

template < class T, IsVec1dimStr<T> = true >
string toString(T&& data, int lim =-1) {
    static_assert(!std::is_array_v<T> == true, "Unsupported type");
    string res{""};
    auto count = 0;
    for(const auto &v : data){
        ++count;
        res += (res.empty() ? "" : ", ")
               + (v.empty() ? "[E]"
                            : (v.size() < lim ? v
                                              : (v.substr(0,lim) + ".../" + to_string(v.size()))));
        if ( !(lim < 0) && count > 10) {
            res += ", ...";
            break;
        }
    }
    res = "["+res+"](" + std::to_string(std::size(data))+")";
    return res;
}

template < class T, IsVec1dimChar<T> = true >
string toString(T&& data, int lim =-1) {
    static_assert(!std::is_array_v<T> == true, "Unsupported type");
    string res{""};
    auto count = 0;
    for(const auto &v : data){
        ++count;
        res += (res.empty() ? "" : ", ") + std::string(1,v);
        if ( !(lim < 0) && count > 10) {
            res += ", ...";
            break;
        }
    }
    res = "["+res+"](" + std::to_string(std::size(data))+")";
    return res;
}

/*
template <class T>
string toString(const T& data, int lim =10) {
    string res{""};
    if constexpr (std::is_array_v<T>) {
        std::cout << "Processing raw array" << std::endl;
    } else if constexpr (std::is_same_v<T, std::vector<int>>
                         || std::is_same_v<T, std::vector<long>>
                         || std::is_same_v<T, std::vector<long long>>
                         || std::is_same_v<T, std::vector<double>>
                         || std::is_same_v<T, std::vector<float>> ) {
    // } else if constexpr (std::is_integral<T>::value == true){
        // } else if constexpr (std::is_integral_v<T> == true){
        // std::cout << "Processing vector<int>" << std::endl;
        string rslt = "";
        auto count{0};
        for( const auto &v : data){
            ++count;
            rslt += (rslt.empty() ? "" : ", ") + std::to_string(v);
            if (count > lim) {
                rslt += ", ...";
                break;
            }
        }
        res = "["+rslt+"](" + std::to_string(std::size(data))+")";
    } else if constexpr (std::is_same_v<T, std::vector<string>>) {
        // std::cout << "Processing vector<string>" << std::endl;
        string rslt = "";
        auto count = 0;
        for(const auto &v : data){
            ++count;
            rslt += (rslt.empty() ? "" : ", ")
                    + (v.empty() ? "[E]"
                                 : (v.size() < lim ? v
                                                  : (v.substr(0,lim) + ".../" + to_string(v.size()))));
            if (count > 10) {
                rslt += ", ...";
                break;
            }
        }
        res = "["+rslt+"](" + to_string(std::size(data))+")";
    } else {
        static_assert( vk_false_v<T>, "Unsupported type" );
        std::cout << "Processing other type" << std::endl;
    }
    cout << "std::is_integral_v<T>=" << std::is_integral_v<typename std::vector<T>::value_type> << endl;
    typename std::vector<T>::value_type vt;
    // cout  << " vec type " << std::to_string(vt) << endl;
    cout << typeid(T).name() << endl;
    cout << typeid(typename std::decay<T>::type::value_type).name() << endl;
    cout << typeid(typename std::remove_reference<T>::type::value_type).name() << "\n";
    if (std::is_same_v<typename std::remove_reference<T>::type::value_type, long long>) cout << "value_type YES same" << endl;
    else cout << "value_type NOT same" << endl;

    // cout << "toString " << std::vector<T>::value_type << endl;
    return res;
}
*/


template < class T, typename It = typename T::iterator >
T&& reverse( T&& data
            , It st = {}
            , It fi = {} ) {

    static_assert(!std::is_array_v<T> == true, "Unsupported type");

    if ( st == It{}) st = data.begin();
    if ( fi == It{}) fi = data.end();

    if (std::distance( st, fi) < 0) std::swap(st,fi);
    std::advance(fi,-1);
    // std::cout << "reverse " << std::distance( st, fi) << endl;
    for ( ; std::distance(st,fi) > 1; std::advance(st,1), std::advance(fi,-1))
        std::iter_swap (st, fi);

    return std::forward<T>(data);
}


template < class T >
T&& rotate( T&& data, unsigned int n ) {
    static_assert(!std::is_array_v<T> == true, "Unsupported type");
    if (n == 0) return std::forward<T>(data);
    n = n % std::size(data);

    vkstd::reverse(std::move(data));
    if (n > 1) vkstd::reverse(std::move(data), std::begin(data), std::next(std::begin(data), n));
    vkstd::reverse(std::move(data), std::next(std::begin(data), n));

    return std::forward<T>(data);
}


// bubble sort container
template < class T >
T&& sortBubble( T&& data ) {
    static_assert(!std::is_array_v<T> == true, "Unsupported type");
    auto len{std::size(data)};
    if (len < 2) return std::forward<T>(data);

    // forward iterator
    auto r{data.end()};
    std::advance(r,-1);
    for ( ; r != data.begin() ; std::advance(r,-1)){
        // cout << "len=" <<len << " dist="<< std::distance(data.begin(),r) << endl;
        for (auto i{data.begin()}; i != r; std::advance(i,1)) {
            if (*std::next(i,1) < *i)  std::iter_swap (i, std::next(i,1));
        }
    }

    return std::forward<T>(data);
}

// selection sort container
template < class T >
T&& sortSelection( T&& data ) {
    static_assert(!std::is_array_v<T> == true, "Unsupported type");
    auto len{std::size(data)};
    if (len < 2) return std::forward<T>(data);

    for (auto i = data.begin(); i != data.end(); std::advance(i,1)) {
        auto m = i;
        for (auto j = std::next(i,1); j != data.end(); std::advance(j,1)){
            if (*j < *m) { m = j; }
        }
        if (m != i){ std::iter_swap(i, m); }
        // if (m != i){ std::swap(*i, *m); }
    }
    return std::forward<T>(data);
}

}

#endif // VKSTD_H
