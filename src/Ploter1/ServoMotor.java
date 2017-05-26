package Ploter1;

import com.pi4j.wiringpi.*;
import com.pi4j.component.servo.*;
/**
 * This class manipulates a servo motor.
 * 
 * @author Fabio Hedayioglu
 * @author Ian Utting
 * @version 1.0
 */
public class ServoMotor
{
    //The motor position
    private int value;
    //The Pin number
    public int actualValue = value;
    private int PinNumber = 1;

    /**
     * Creates the Servo Motor at the default pin (GPIO 1)
     */
    public ServoMotor()
    {
        //Gpio.wiringPiSetup();
        //Set the PinNumber pin to be a PWM pin, with values changing from 0 to 1000 
        //this will give enough resolution to the servo motor
        SoftPwm.softPwmCreate(PinNumber,0,1000);
        
        //set initial position to the minimal.
        value = 0;
        //tell the servo motor to go to the zero position.
        //this will allow us to keep track of the position of the servo motor.
        //the initial postion of the motor is the value 5. the valid range of positions of the motor is
        //from 5 to 25.
        SoftPwm.softPwmWrite(PinNumber, value + 5);
        //allow sufficient time to the servo mottor to move to the position.
        sleepMillisec(1500);
        //stop sending orders to the motor.
        stop();
    }

    public void setPosition(int positionNumber)
    {
        if (positionNumber >= 0 && positionNumber <= 20)
        {
            //update the position;
            value = positionNumber;
            actualValue = value;
            //send the value to the motor.
            SoftPwm.softPwmWrite(PinNumber, value + 5);
            //give time to the motor to reach the position
            sleepMillisec(1500);
            //stop sending orders to the motor.
            stop();
        }
        
    }
    
    /**
     * turn servo off
     */
    private void stop(){
        //zero tells the motor to turn itself off and wait for more instructions.
        SoftPwm.softPwmWrite(PinNumber, 0);
    }
    
    /**
     * Get the Servo current position
     * @return the integer with the servo motor's current position.
     */
    public int getPosition(){
        //returns the current position;
        return value;
    }
    
    /**
     * Wait for a number of milliseconds
     * @param milisec the number of milliseconds to wait.
     */
    private void sleepMillisec(int millisec){
        try
        {
            Thread.sleep(millisec);
        }
        catch ( InterruptedException e)
        {
        }
    }
}
