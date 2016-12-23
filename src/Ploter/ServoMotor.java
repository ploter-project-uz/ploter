package Ploter;

import com.pi4j.wiringpi.*;

public class ServoMotor {
	private int value;
	private int PinNumber = 1;

	public ServoMotor() {
		Gpio.wiringPiSetup();
		SoftPwm.softPwmCreate(PinNumber, 0, 1000);
		value = 0;
		SoftPwm.softPwmWrite(PinNumber, value + 5);
		sleepMillisec(1500);
		stop();
	}

	public void penUp() {
		setPosition(10);
	}

	public void penDown() {
		setPosition(0);
	}

	public void setPosition(int positionNumber) {
		if (positionNumber >= 0 && positionNumber <= 20) {
			value = positionNumber;
			SoftPwm.softPwmWrite(PinNumber, value + 5);
			sleepMillisec(1500);
			stop();
		}

	}

	private void stop() {
		SoftPwm.softPwmWrite(PinNumber, 0);
	}

	public int getPosition() {
		return value;
	}

	private void sleepMillisec(int millisec) {
		try {
			Thread.sleep(millisec);
		} catch (InterruptedException e) {
		}
	}
}
