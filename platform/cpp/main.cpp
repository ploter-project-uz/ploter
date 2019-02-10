#include "Window.hpp"


int main(int argc, char *argv[])
{
  
  Gtk::Main kit(argc, argv);
  Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("Builder.ui");
  Window *okno = 0;
  
  builder -> get_widget_derived("window1", okno);
  
  kit.run(*okno);
  
}




