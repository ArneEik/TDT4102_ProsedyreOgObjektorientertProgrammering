#include "template.h"

template<typename T>
T bigger(T a, T b){
    return b<a ? a:b;
}

template<typename T>
void shuffel(vector<T>& vec){
    for (int i = 0; i <50; i++){
       int randInt1 = rand() % vec.size();
       int randInt2 = rand() % vec.size();
       if (randInt1 != randInt2){
        std::swap(vec[randInt1], vec[randInt2]);
       }
    }
}

void runTemplate()
{
    vector<string> stringVec = {"sopp","dfs","sag","suiii","saads"};
    for (auto string:stringVec){
        std::cout<<string<<", ";
    }std::cout<<std::endl;
    shuffel(stringVec);
    std::cout<<"stokker.."<<std::endl;
    for (auto string:stringVec){
        std::cout<<string<<", ";
    }std::cout<<std::endl;

}
