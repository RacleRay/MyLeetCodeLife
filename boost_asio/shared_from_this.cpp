/*************************************************************************
    > File Name: shared_from_this.cpp
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time: 
 ************************************************************************/

#include <iostream>
#include <memory>

class Widget{
public:
    Widget(){
        std::cout << "Widget constructor run" << std::endl;
    }
    ~Widget(){
        std::cout << "Widget destructor run" << std::endl;
    }

    std::shared_ptr<Widget> GetSharedObject(){
        return std::shared_ptr<Widget>(this);
    }
};

class Widget2 : public std::enable_shared_from_this<Widget2>{
public:
    Widget2(){
        std::cout << "Widget constructor run" << std::endl;
    }
    ~Widget2(){
        std::cout << "Widget destructor run" << std::endl;
    }

    std::shared_ptr<Widget2> GetSharedObject(){
        return shared_from_this();
    }
};

int main()
{
    std::shared_ptr<Widget> p(new Widget());
    std::shared_ptr<Widget> q = p->GetSharedObject();

    // Error in next 2 lines. destructor invoked twice.
    std::cout << p.use_count() << std::endl; // 1
    std::cout << q.use_count() << std::endl; // 1


    std::shared_ptr<Widget2> p2(new Widget2());
    std::shared_ptr<Widget2> q2 = p2->GetSharedObject();

    std::cout << p2.use_count() << std::endl; // 2  +1 by shared_from_this()
    std::cout << q2.use_count() << std::endl; // 2

    return 0;
}
