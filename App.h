#ifndef APP_H
#define APP_H
#include "src/Engine/Component.h"

class App : public Engine::Component
{
private:
    /* data */
public:
    App(/* args */);
    ~App();
    void run(Engine::Frame *super) {}
    void setUp(Engine::Frame *super) { puts("działa SetUp"); }
    void clean(Engine::Frame *super) { puts("działa clean"); }
};

App::App(/* args */)
{
}

App::~App()
{
}

#endif;