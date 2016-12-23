
import java.util.Scanner;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;

public class ServoPen {

	final GpioController gpio = GpioFactory.getInstance();

	GpioPinDigitalOutput myServo = gpio.provisionDigitalOutputPin(RaspiPin.GPIO_01, // PIN
			// NUMBER
			"My LED", // PIN FRIENDLY NAME (optional)
			PinState.LOW);

//	public ServoPen() throws InterruptedException {
//		for (int i = 0; i < 100; i++) {
//			myServo.high();
//			java.lang.Thread.sleep(0, 1500);
//			myServo.low();
//		}
//	}

	private int position = 0;

	public void penUp() throws InterruptedException {
		for (int i = 0; i < 100; i++) {
			myServo.high();
			java.lang.Thread.sleep(0, 1000);
			myServo.low();
			java.lang.Thread.sleep(0, 20000);

		}
	}

	public void penDown() throws InterruptedException {
		for (int i = 0; i < 100; i++) {
			myServo.high();
			java.lang.Thread.sleep(0, 2000);
			myServo.low();
			java.lang.Thread.sleep(0, 20000);
		}
	}

	public static void main(String[] args) throws InterruptedException {
		ServoPen pen = new ServoPen();
		while (true) {
			System.out.print("Enter something:");
			String input = System.console().readLine();
			char c = input.charAt(0);
			if (c == 'u') {
				pen.penUp();
			} else if (c == 'd')
			//	pen.penDown();
			System.out.println(input);
		}

	}
}
