#ifndef WINDOW_HPP
#define WINDOW_HPP

#include<gtkmm.h>

#include<vector>

#include<memory>

class Command;

class Window : public Gtk::Window 
{
protected:
    
  Gtk::Window *m_window;
  Gtk::TextView *m_textView;
  Gtk::FileChooserButton *m_file;
  Gtk::Button *m_button_run;
  Gtk::Button *m_button_simulate;
  Gtk::Label *m_label;
  
  Glib::RefPtr<Gtk::Builder> m_builder;
  Glib::RefPtr<Gtk::TextBuffer> m_bufor;
  
  void openFile();
  void simulate(Glib::ustring data);
  void run();
  bool draw();
  
public:
  
  Window( BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
  

  class DrawingArea : public Gtk::DrawingArea
  {
  protected:
    //static int current_x; static int current_y;
    int currentX;
    int currentY;
    
    std::vector<std::shared_ptr<Command> > commands;

    bool on_draw( const Cairo::RefPtr<Cairo::Context>& cr);
    
  public:  
    DrawingArea( BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder): Gtk::DrawingArea(cobject) {}
    bool force_redraw( std::vector<std::shared_ptr<Command> > &vCommands);
  
  };
  
  
private:
  
  DrawingArea *m_area;
  
};

#endif
