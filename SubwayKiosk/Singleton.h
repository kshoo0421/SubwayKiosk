#ifndef SINGLETON_H
#define SINGLETON_H

/* 
[싱글톤 생성용 클래스]
싱글톤을 원하는 클래스가 있을 시 상속을
: public Singleton<클래스> {
friend class Singleton<클래스>;
private:
    클래스() = default; // 생성자는 private로 설정. 추가 설정 시 default 제거 후 사용
}
*/

template <typename T>
class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    static T& Instance() {
        static T instance;
        return instance;
    }
};
#endif