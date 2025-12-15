#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

template < class Ty >
class Node {
private:

public:
    Ty val;
    Node *next;

    Node() : val{0}, next{nullptr} { }

    Node(Ty v) : val{v}, next{nullptr} { }

    // s-show size;
    string stringify(bool s=true) const;

    friend std::ostream& operator<<(std::ostream& os, const Node<Ty>* v);   // TODO

};

// make Node list from vector
template < class Ty >
// typename std::enable_if_t<std::is_same_v<Ty, std::vector<int>>::value,  Node<Ty[]>* >
Node<Ty>* makeNode(vector<Ty> vec){
    if (vec.size() == 0) return new Node<Ty>();
    Node<Ty> *head = new Node<Ty>(vec[0]);
    // head->val = vec[0];
    Node<Ty> *cur = head;
    for (auto i{1}; i < vec.size(); ++i){
        cur->next = new Node<Ty>(vec[i]);
        cur = cur->next;
    }
    return head;
}


//
template <class Ty>
    string Node<Ty>::stringify(bool s) const{
    auto len{1};
    string res{std::to_string(val) + ","};
    Node<Ty>* cur = next;
    for ( ; cur != nullptr; ++len){
        res += std::to_string(cur->val) + ",";
        // res += (res==""?"":",");
        // res += cur->val + '0';
        cur = cur->next;
    }
    // return "["+res+"]";
    return "["+res+"](" +( s ? to_string(len) : "")+")";

}

// friend functions
template <class Ty>     // TODO
std::ostream& operator<<(std::ostream& os, const Node<Ty>* v) {
    // cout << "here !!!" << endl;
    // os << "a";
    return os;
    // string res{"aaaaa"};
    // Node<Ty>* cur = v;
    // while (cur != nullptr){
    //     // res += std::to_string(v->val) + ", ";
    //     // res += (res==""?"":",");
    //     // res += cur->val + '0';
    // }
    // // res = "["+res+"]";

    // os << res << endl;
    // return os;
}

template <typename T>
void testNode_data(T data) {
    if constexpr (std::is_array_v<T>) {
        std::cout << "Processing raw array" << std::endl;
    } else if constexpr (std::is_same_v<T, std::vector<int>>) {
        std::cout << "Processing vector" << std::endl;
    } else {
        std::cout << "Processing other type" << std::endl;
    }
}



#endif // NODE_H
