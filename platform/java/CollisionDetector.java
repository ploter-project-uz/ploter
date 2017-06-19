package Ploter1;


import com.pi4j.io.gpio.*;
import com.pi4j.io.gpio.event.GpioPinListenerDigital;
import com.pi4j.io.gpio.event.GpioPinDigitalStateChangeEvent;
public class CollisionDetector
{
    // instance variables - replace the example below with your own
    private int x;
    static  boolean setReturn;
    /**
     * Constructor for objects of class CollisionDetector
     */
    public CollisionDetector()
    {
        
    }

    
    public static boolean detectCollisopn(GpioPinDigitalInput[] pinsInput)
    {
      
       pinsInput[0].addListener(new GpioPinListenerDigital(){
           @Override
           public void handleGpioPinDigitalStateChangeEvent(GpioPinDigitalStateChangeEvent event){
             // System.out.println("GPIO "+ event.getPin() + " = " + event.getState() ); 
            if(event.getState()==PinState.HIGH){
                 setReturn = true;
        }else
         {
             setReturn = false;
            }}      
    });
      return setReturn;
}
}