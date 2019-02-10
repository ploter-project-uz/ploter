#include "Window.hpp"
#include "Command.hpp"
#include "Parser.hpp"
#include "Factory.hpp"
#include "StepperControl.hpp"
#include "Current.hpp"

#include<fstream>

#include<string>

#include<vector>

#include<sstream>

#include<iostream>

#define COMMENT (';')
#define SERVO_PIN 26

#define X_STEP_PIN 2
#define X_DIR_PIN 0
#define X_MIN_PIN 25
#define X_MAX_PIN 4//26
#define X_ENABLE_PIN 3

#define Y_STEP_PIN 13
#define Y_DIR_PIN 12
#define Y_MIN_PIN 5
#define Y_MAX_PIN 6
#define Y_ENABLE_PIN 14

#define X_MOTOR_STEPS 1600
#define Y_MOTOR_STEPS 1600


Window::Window(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Window(cobject), m_builder(refGlade)
{
  
  refGlade->get_widget("window1", m_window);
  refGlade->get_widget("textview1", m_textView);
  refGlade->get_widget("filechooserbutton1", m_file);
  refGlade->get_widget("button1", m_button_run);
  refGlade->get_widget("label2", m_label);
  refGlade->get_widget("button2", m_button_simulate);
  refGlade->get_widget_derived("drawingarea1", m_area);

  m_window->set_default_size(800,600);
  
  m_bufor = Gtk::TextBuffer::create();
  m_textView -> set_buffer(m_bufor);
  
  m_file->signal_current_folder_changed().connect( sigc::mem_fun(*this, &Window::openFile));
  m_button_simulate->signal_clicked().connect( sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Window::simulate), "s"));
  m_button_run->signal_clicked().connect( sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &Window::simulate), "r"));
}


void Window::openFile()
{
  
  std::string name;
  std::ifstream fin;
  
  name = m_file -> get_filename();
  fin.open(name);
  
  if(!fin) {
    m_label -> set_text("Can not open file!");
  }
  
  std::string text( (std::istreambuf_iterator<char>(fin) ),
		    (std::istreambuf_iterator<char>() ) );

  m_bufor -> set_text(text);
  m_textView -> set_buffer(m_bufor);
  
}


void Window::simulate(Glib::ustring data)
{

  int lineNumber = 1;
  int commandNumber = 0;
  
  std::string text = m_bufor -> get_text();
  std::istringstream iss(text);
  std::string line;
  
  Command::vector_SPtr vCommands;

  Current cordinate;
  
  StepperControl *stepper = new StepperControl('x', X_MOTOR_STEPS, X_DIR_PIN, X_STEP_PIN, X_MIN_PIN, X_MAX_PIN, X_ENABLE_PIN,
					       'y', Y_MOTOR_STEPS, Y_DIR_PIN, Y_STEP_PIN, Y_MIN_PIN, Y_MAX_PIN, Y_ENABLE_PIN, SERVO_PIN);
  
  while(getline(iss, line)) {

    Parser tokenizer;
    
    try {
      tokenizer.parse(line, lineNumber);
    }
    catch(std::string error) {
      m_label -> set_text(error);
      return;
    }
    catch(int emptyLine) {
      lineNumber++;
      continue;
    }

    try {
      vCommands.push_back(Factory::getCommand(tokenizer.token[0], lineNumber));
    }
    catch(std::string unknown) {
      m_label -> set_text(unknown);
      return;
    }

    try {
      vCommands[commandNumber]->validate(tokenizer.token, lineNumber);
    }
    catch(std::string unknown) {
      m_label -> set_text(unknown);
      return;
    }
    catch(std::string required) {
      m_label -> set_text(required);
      return;
    }
    
    vCommands[commandNumber]->createCommand(tokenizer.token, &cordinate);
    
    try {
      vCommands[commandNumber]->checkParameters(&cordinate, lineNumber);
    }
    catch(std::string maxX) {
      m_label -> set_text(maxX);
      return;
    }
    catch(std::string maxY) {
      m_label -> set_text(maxY);
      return;
    }

    lineNumber++;
    commandNumber++;
  }
  
  m_label -> set_text("wszystko OK");

  cordinate.reset();
  
  if(data == "s") {
    for(Command::SPtr& command: vCommands) {
      command->execute(stepper, &cordinate);
    }
  }
  
  else if(data == "r") {
    m_area -> force_redraw(vCommands);
  }
  
  
}


bool Window::DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
  
  cr->save();
  cr->set_source_rgb(0.8,0,0);
  cr->set_line_width(2.0);
  
  Gtk::Allocation allocation = get_allocation();
  
  int width = allocation.get_width();
  int height = allocation.get_height();
  
  int x = width / 2;
  int y = height / 2;
  
  this->currentX = x;
  this->currentY = y;
  
  cr->move_to(x,y);
    
  for(Command::SPtr& command: commands) {
    command->draw(cr, width, height);
  }
  
  cr->restore();
  cr->stroke();
 
  return true;
}

bool Window::DrawingArea::force_redraw(std::vector<std::shared_ptr<Command>> &vCommands)
{
  auto win = get_window();
  
  if(win) {
    queue_draw();
  }
  
  return true;
}

