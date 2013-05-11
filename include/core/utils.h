#ifndef UTILS_H
#define UTILS_H

template<typename T1, typename T2, typename T3>
struct triple
{
    T1 first;
    T2 second;
    T3 third;

    triple(T1 p1, T2 p2, T3 p3) : first(p1), second(p2), third(p3) {}
    inline bool operator==(const triple &other) { return first == other.first && second == other.second && third == other.third; }
    inline bool operator!=(const triple &other) { return !(*this == other); }
};

#endif
