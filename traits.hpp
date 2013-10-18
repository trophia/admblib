#pragma once

#include <type_traits>

namespace AdmbLib {

class Trait {
public:
    typedef char (&yes)[1];
    typedef char (&no)[2];
};

template <typename Type>
class HasIndex : public Trait {
public:
    template<typename A, A, A> struct Match;
    template <typename A> static yes deduce(Match<int (A::*)() const,&A::indexmin,&A::indexmax>*);
    template <typename A> static no deduce(...);
    static const bool value = sizeof(deduce<Type>(0)) == sizeof(yes);
};

template <typename Type>
struct IsContainer : std::integral_constant<bool,
    std::is_class<Type>::value and 
    HasIndex<Type>::value
>{};

}