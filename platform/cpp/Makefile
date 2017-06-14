CC=g++
OBJ = main.o window.o command.o parser.o factory.o RepStepper.o LinearAxis.o stepperControl.o gcode.o current.o servoMotor.o

interpreter: $(OBJ)
	$(CC) -o $@ $^ `pkg-config gtkmm-3.0 --cflags --libs` -lwiringPi -std=c++11 -I.

main.o: Main.cpp 
	$(CC) Main.cpp -c -o main.o `pkg-config gtkmm-3.0 --cflags --libs`

window.o: Window.cpp 
	$(CC) Window.cpp -c -o window.o `pkg-config gtkmm-3.0 --cflags --libs`

command.o: Command.cpp
	$(CC) Command.cpp -c -o command.o `pkg-config gtkmm-3.0 --cflags --libs` 

parser.o: Parser.cpp
	$(CC) Parser.cpp -c -o parser.o

factory.o: Factory.cpp
	$(CC) Factory.cpp -c -o factory.o `pkg-config gtkmm-3.0 --cflags --libs`

repStepper.o: RepStepper.cpp
	$(CC) RepStepper.cpp -c -o repStepper.o

linearAxis.o: LinearAxis.cpp
	$(CC) LinearAxis.cpp -c -o linearAxis.o

stepperControl.o: StepperControl.cpp
	$(CC) StepperControl.cpp -c -o stepperControl.o

gcode.o: Gcode.cpp
	$(CC) Gcode.cpp -c -o gcode.o `pkg-config gtkmm-3.0 --cflags --libs`

current.o: Current.cpp
	$(CC) Current.cpp -c -o current.o

servoMotor.o: ServoMotor.cpp
	$(CC) ServoMotor.cpp -c -o servoMotor.o

clean:
	rm *.o
