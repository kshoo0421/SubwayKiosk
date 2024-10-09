#ifndef DETAILS_H
#define DETAILS_H
#include <string>

class Details{
private:
    int kcal; //열량
    float protein; //단백질(g)
    float saturatedFatty; //포화지방(g)
    float sugar; //당류(g)
    int natrium; //나트륨(mg)
    std::string expln; //메뉴 설명

public :
    Details();
    ~Details();
    Details(int,float,float, float, int,std::string);
};

#endif // DETAILS_H
