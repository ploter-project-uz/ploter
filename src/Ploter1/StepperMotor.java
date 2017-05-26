package Ploter1;

 import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;

public  class StepperMotor {
    // instance variables - replace the example below with your own
    //~ final GpioController gpio = GpioFactory.getInstance();
    //~ final  GpioPinDigitalOutput[] pins = { gpio.provisionDigitalOutputPin(RaspiPin.GPIO_00, PinState.LOW),
            //~ gpio.provisionDigitalOutputPin(RaspiPin.GPIO_01, PinState.LOW),
            //~ gpio.provisionDigitalOutputPin(RaspiPin.GPIO_08, PinState.LOW) };   

    public StepperMotor() {

    }

    //~ public void moveLeft(int steps) throws InterruptedException {
        //~ pins[1].low();
        //~ pins[2].high();
        //~ for (int i = 0; i < steps; i++) {
            //~ pins[0].high();
            //~ java.lang.Thread.sleep(1, 0);
            //~ pins[0].low();
        //~ }
        //~ pins[2].low();
    //~ }

    //~ public void moveRight(int steps) throws InterruptedException {
        //~ pins[1].high();
        //~ pins[2].high();
        //~ for (int i = 0; i < steps; i++) {
            //~ pins[0].high();
            //~ java.lang.Thread.sleep(5, 0);
            //~ pins[0].low();
        //~ }
        //~ pins[2].low();
    //~ }

    public void doStep(int steps, boolean dir, GpioPinDigitalOutput pinDir, GpioPinDigitalOutput pinClk,GpioPinDigitalOutput pinEna) throws InterruptedException {
        if (dir)
            pinDir.high();
        else{
            pinDir.low();
        }
        pinEna.high();
        for (int i = 0; i < steps; i++) {
            pinClk.high();
            java.lang.Thread.sleep(1, 0);
            pinClk.low();
            java.lang.Thread.sleep(0, 20000);
            
        }
        pinEna.low();
        //gpio.shutdown();
        //gpio.unprovisionPin(pins);
        
    }
    //~ public void doStep2(int steps, int nanos) throws InterruptedException {
        //~ boolean dir = true;
        //~ if (dir)
            //~ pins[1].high();
        //~ else{
            //~ pins[1].low();
        //~ }
        //~ pins[2].high();
        //~ for (int i = 0; i < steps; i++) {
            //~ pins[0].high();
            //~ java.lang.Thread.sleep(0,nanos);
            //~ pins[0].low();
            //~ java.lang.Thread.sleep(0,20000);
            //~ //java.lang.Thread.sleep(0, 300000);
            //~ 
        //~ }
        //~ pins[2].low();
        //~ gpio.shutdown();
        //~ gpio.unprovisionPin(pins);
        
    }
    
    
       

    
