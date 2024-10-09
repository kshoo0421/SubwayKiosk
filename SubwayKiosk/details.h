#ifndef DETAILS_H
#define DETAILS_H
#include "Singleton.h"
#include <string>
using namespace std;

//메뉴 상세 정보
class Details : public Singleton<Details>{
private:
    int* kcal; //열량
    float* protein; //단백질(g)
    float* saturatedFatty; //포화지방(g)
    float* sugar; //당류(g)
    int* natrium; //나트륨(mg)
    string* expln; //메뉴 설명

    Details();

public :
   // Details(int, float, float, float, int, string);

    Details getDetails(int n);
};

#endif // DETAILS_H
