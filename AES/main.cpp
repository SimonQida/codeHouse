#include<iostream>
#include<gtkmm.h>

int main()
{
    auto app =
        Gtk::Application::create(argc, argv,
                "org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(200, 200);

    return app->run(window);
}
