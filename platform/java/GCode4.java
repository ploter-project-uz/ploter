package Ploter1;



import java.awt.Graphics;

import javax.swing.JFrame;

import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.GpioPinDigitalOutput;

public class GCode4 extends JFrame {

	static GpioPinDigitalOutput[] pinsOutput = null;
	static GpioPinDigitalInput[] pinsInput = null;
	public String code;
	final float STEP_PER_INCH = 2;
	float x_units = STEP_PER_INCH;
	float y_units = STEP_PER_INCH;
	// int actualX, actualY;
	long max_delta;
	long delta_steps_x, delta_steps_y, delta_steps_z;
	boolean x_direction = true;
	boolean y_direction = true;
	public long current_steps_x = 0;
	public long current_steps_y = 0;
	public float current_units_x;
	public  float current_units_y;
	public  float current_units_z;
	public float target_units_x;
	public float target_units_y;
	public float target_units_z;
	float delta_units_x;
	float delta_units_y;
	long target_steps_y = 0, target_steps_x = 0;
	float cent_x, cent_y;
	double curve_section = 2;
	//
	public GCode4(String string, double xAxis, double yAxis, double zAxis, double pointI, double pointJ,
			GpioPinDigitalOutput[] pinsOutput, GpioPinDigitalInput[] pinsInput) {
		target_units_x = (long) xAxis;
		target_units_y = (long) yAxis;
		target_units_z = (long) zAxis;
		cent_x = (long) pointI;
		cent_y = (long) pointJ;
		code = string;
		this.pinsInput = pinsInput;
		this.pinsOutput = pinsOutput;
	}



	

		public void execute(String code, float x, float y,float z, float i, float j, Graphics g) throws InterruptedException {
			current_units_z = z;
			switch (code) {
			case "G00":
			case "G01":
			case "G0 ":
			case "G1 ":
			case "G1":
			case "G0":
				dda_move(x, y, g);
				break;
			case "G02":
			case "G2":
			case "G2 ":
				doCircle(x, y, i, j, g);
				// arc(x, y, i, j, g);
			}
			// dda_move(x,y,g);
		}

		@Override
		public String toString() {
			return code + " [x_units=" + x_units + ", y_units=" + y_units + ", delta_steps_x=" + delta_steps_x
					+ ", delta_steps_y=" + delta_steps_y + ", current_steps_x=" + current_steps_x + ", current_steps_y="
					+ current_steps_y + ", current_units_x=" + current_units_x + ", current_units_y=" + current_units_y
					+ ", current_units_z=" + current_units_z + ", target_units_x=" + target_units_x
					+ ", target_units_y=" + target_units_y + ", delta_units_y=" + delta_units_y + ", target_steps_y="
					+ target_steps_y + ", target_steps_x=" + target_steps_x + "]" + System.lineSeparator();
		}

		public void dda_move(float target_units_x, float target_units_y, Graphics g) throws InterruptedException {
			calculate_deltas();
		//	 g.drawLine(100, 100, 200,200);
			 g.drawLine(100, 500, 800, 400);
		//	 g.drawLine(50, 400, 5, 5);
		//	 g.drawLine(50, 200, 5, 5);
			



			// figure out our deltas
			max_delta = Math.max(delta_steps_x, delta_steps_y);

			max_delta = Math.max(delta_steps_z, max_delta);

			// init stuff.
			long x_counter = -max_delta / 2;
			long y_counter = -max_delta / 2;
			// long z_counter = -max_delta/2;

			// our step flags
			boolean x_can_step = true;
			boolean y_can_step = true;

			boolean direX = (current_units_x < target_units_x);
			boolean direY = (current_units_y < target_units_y);
			// int current_units_x=0, current_units_y=0;
			// if (micro_delay >= 16383)
			// milli_delay = micro_delay / 1000;
			// else
			// milli_delay = 0;

			// do our DDA line!
			//if (current_units_z>= 0)
				
			do {
				x_can_step = can_step(current_steps_x, target_steps_x, x_direction);
				// System.out.println(x_can_step);
				y_can_step = can_step(current_steps_y, target_steps_y, y_direction);
				// z_can_step = can_step(Z_MIN_PIN, Z_MAX_PIN, current_steps.z,
				// target_steps.z, z_direction);
//				if(CollisionDetector.detectCollisopn(pinsInput)){
//                    break;
//                }
//                
			
					if (x_can_step) {
						//Thread.sleep(2);
						x_counter += delta_steps_x;
						// System.out.println("XXXXXXXXXXX COUNTER "
						// +x_counter);
						if (x_counter > 0) {
							// do_step(X_STEP_PIN);
							// motorX.doStep(1,direX, pinsOutput[0],
							// pinsOutput[1],
							// pinsOutput[2]);
							// current_units_x++;
							x_counter -= max_delta;
							if (x_direction) {
								current_steps_x++;
								if (current_units_z < 0)
									g.drawLine((int) (current_units_x * STEP_PER_INCH + 200),
											(int) (-current_units_y * STEP_PER_INCH +700),
											(int) (target_units_x * STEP_PER_INCH + 200),
											(int) (-target_units_y * STEP_PER_INCH + 700));
								// g.drawLine((int) (current_steps_x + 300),
								// (int)
								// (current_steps_y + 300),
								// (int) (current_steps_x + 300), (int)
								// (current_steps_y + 300));
							}

							else {
								current_steps_x--;
								if (current_units_z < 0)
									g.drawLine((int) (current_units_x * STEP_PER_INCH + 200),
											(int) (-current_units_y * STEP_PER_INCH +700),
											(int) (target_units_x * STEP_PER_INCH + 200),
											(int) (-target_units_y * STEP_PER_INCH + 700));
								// g.drawLine((int) (current_steps_x + 300),
								// (int)
								// (current_steps_y + 300),
								// (int) (current_steps_x + 300), (int)
								// (current_steps_y + 300));
							}
						}
					}

				if (y_can_step) {
				//	Thread.sleep(2);
				//	System.out.println("DIRE Y " + direY);
					y_counter += delta_steps_y;

					if (y_counter > 0) {

						// motorY.doStep(1, direX, pins[3], pins[4], pins[5]);
						// do_step(Y_STEP_PIN);
						// current_units_y++;
						y_counter -= max_delta;

						if (y_direction) {
							current_steps_y++;
							if (current_units_z < 0)
								g.drawLine((int) (current_units_x * STEP_PER_INCH + 200),
										(int) (-current_units_y * STEP_PER_INCH +700),
										(int) (target_units_x * STEP_PER_INCH + 200),
										(int) (-target_units_y * STEP_PER_INCH +700));
							// g.drawLine((int) (current_steps_x + 300), (int)
							// (current_steps_y + 300),
							// (int) (current_steps_x + 300), (int)
							// (current_steps_y + 300));
						} else {
							current_steps_y--;
							if (current_units_z < 0)
								g.drawLine((int) (current_units_x * STEP_PER_INCH + 200),
										(int) (-current_units_y * STEP_PER_INCH +700),
										(int) (target_units_x * STEP_PER_INCH + 200),
										(int) (-target_units_y * STEP_PER_INCH + 700));
							// g.drawLine((int) (current_steps_x + 300), (int)
							// (current_steps_y + 300),
							// (int) (current_steps_x + 300), (int)
							// (current_steps_y + 300));
							//

						}
					}
				}

				// wait for next step.
				// if (milli_delay > 0)
				// delay(milli_delay);
				// else
				// delayMicroseconds(micro_delay);
			} while (x_can_step || y_can_step);

			// set our points to be the same
			current_units_x = target_units_x;

			current_units_y = target_units_y;
			//current_units_z = target_units_z;
			System.out.println("Current_x :" + current_units_x + " current y " + current_units_y + "current z " + current_units_z);
			System.out.println("Target_x :" + target_units_x + " Target_y " + target_units_y);
			// calculate_deltas();
		}

		private void calculate_deltas() {
			// figure our deltas.
			delta_units_x = Math.abs(target_units_x - current_units_x);
			System.out.println(Math.abs(target_units_x - current_units_x) + "ABS");
			delta_units_y = Math.abs(target_units_y - current_units_y);
			// delta_units_z = abs(target_units.z - current_units.z);

			// set our steps current, target, and delta
			current_steps_x = to_steps(x_units, current_units_x);
			current_steps_y = to_steps(y_units, current_units_y);
			// current_steps_z = to_steps(z_units, current_units_z);

			target_steps_x = to_steps(x_units, target_units_x);
			target_steps_y = to_steps(y_units, target_units_y);
			// target_steps_z = to_steps(z_units, target_units_z);

			delta_steps_x = Math.abs(target_steps_x - current_steps_x);
			delta_steps_y = Math.abs(target_steps_y - current_steps_y);
			// delta_steps_z = abs(target_steps.z - current_steps.z);

			// what is our direction
			x_direction = (target_units_x >= current_units_x);
			y_direction = (target_units_y >= current_units_y);
			// z_direction = (target_units.z >= current_units.z);

			// set our direction pins as well
			// digitalWrite(X_DIR_PIN, x_direction);
			// digitalWrite(Y_DIR_PIN, y_direction);
			// digitalWrite(Z_DIR_PIN, z_direction);

		}

		public boolean can_step(long current, long target, boolean direction) {
			// stop us if we're on target
			// System.out.println("TARGER"+ target + " CURRENT " + current );
			if (target == current)
				return false;
			else
				// stop us if we're at home and still going
				// else if (!direction)
				// return false;
				// stop us if we're at max and still going
				// else if (direction)
				// return false;

				// default to being able to step

				return true;
		}

		long to_steps(float steps_per_unit, float units) {
			return (long) (steps_per_unit * units);
		}

		public void doCircle(float target_units_x, float target_units_y, float cent_x, float cent_y, Graphics g)
				throws InterruptedException {
			// FloatPoint cent;

			// Centre coordinates are always relative
			// cent.x = search_string('I', instruction, size) + current_units.x;
			// cent.y = search_string('J', instruction, size) + current_units.y;
			float angleA, angleB, angle, radius, length, aX, aY, bX, bY;
			cent_x += current_units_x;
			cent_y += current_units_y;

			aX = (current_units_x - cent_x);
			aY = (current_units_y - cent_y);
			bX = (target_units_x - cent_x);
			bY = (target_units_y - cent_y); // ??????????
			// System.out.println("Curremnt_x C "+ current_units_x+ " current y
			// C" + current_units_y);
			 if (code == "G02") { // Clockwise
			angleA = (float) Math.atan2(bY, bX);
			angleB = (float) Math.atan2(aY, aX);
			 } else { // Counterclockwise
			 angleA = (float) Math.atan2(aY, aX);
			 angleB = (float) Math.atan2(bY, bX);
			 }

			// Make sure angleB is always greater than angleA
			// and if not add 2PI so that it is (this also takes
			// care of the special case of angleA == angleB,
			// ie we want a complete circle)
			if (angleB <= angleA)
				angleB += 2 * Math.PI;
			angle = angleB - angleA;

			radius = (float) Math.sqrt(aX * aX + aY * aY);
			length = radius * angle;
			int steps, s, step;
			steps = (int) Math.ceil(length / curve_section);
			System.out.println("length" + length);
			System.out.println("STEPS " + steps);
			/// FloatPoint newPoint;
			long newPoint_x, newPoint_y;
			for (s = 1; s <= steps; s++) {
				step = ( code == "G03") ? s : steps - s; // Work backwards for
															// CW
				newPoint_x = (long) (cent_x + radius * Math.cos(angleA + angle * ((float) step / steps)));
				newPoint_y = (long) (cent_y + radius * Math.sin(angleA + angle * ((float) step / steps)));
				set_target(newPoint_x, newPoint_y);
				// target_units_x= newPoint_x;
				// target_units_y = newPoint_y;
				// Need to calculate rate for each section of curve
				// if (feedrate > 0)
				// feedrate_micros = calculate_feedrate_delay(feedrate);
				// else
				// feedrate_micros = getMaxSpeed();

				// Make step
				dda_move(newPoint_x, newPoint_y, g);

			}

		}

		void set_target(float x, float y) {
			target_units_x = x;
			target_units_y = y;
			// target_units_z = z;

			calculate_deltas();
		}

		double atan3(double dy, double dx) {
			double a = Math.atan2(dy, dx);
			if (a < 0)
				a = (Math.PI * 2.0) + a;
			return a;
		}

		public void arc(double destinationX, double destinationY, double I, double J, Graphics g)
				throws InterruptedException {
			// This method assumes the limits have already been checked.
			// This method assumes the start and end radius match (both points
			// are same distance from center)
			// This method assumes arcs are not >180 degrees (PI radians)
			// This method assumes all movement is at a constant Z height
			// cx/cy - center of circle
			// x/y - end position
			// dir - ARC_CW or ARC_CCW to control direction of arc
			// (posx,posy,posz) is the starting position
			// line() is our existing command to draw a straight line using
			// Bresenham's algorithm.

			// get radius
			// get radius
			I += current_units_x;
			J += current_units_y;
			int dir = 0;
			float dx = (float) (current_units_x - I);
			float dy = (float) (current_units_y - J);

			float radius = (float) Math.sqrt(dx * dx + dy * dy);
			System.out.println("RADIUS " + radius);
			// find angle of arc (sweep)
			double angle1 = atan3(dy, dx);
			double angle2 = atan3(destinationY - J, destinationX - I);
			double theta = angle2 - angle1;

			if (dir > 0 && theta < 0)
				angle2 += 2 * Math.PI;
			else if (dir < 0 && theta > 0)
				angle1 += 2 * Math.PI;

			theta = angle2 - angle1;

			// get length of arc
			// float circ=PI*2.0*radius;
			// float len=theta*circ/(PI*2.0);
			// simplifies to
			double len = Math.abs(theta) * radius;

			int i, segments = (int) Math.ceil(len * curve_section);

			float nx = 0, ny = 0, angle3, scale;

			for (i = 0; i < segments; ++i) {

				// interpolate around the arc
				scale = (float) (((double) i) / ((double) segments));

				angle3 = (float) ((theta * scale) + angle1);
				nx = (float) (I + Math.cos(angle3) * radius);
				ny = (float) (J + Math.sin(angle3) * radius);
				// send it to the planner
				// G00.execute(destinationY, destinationY, g);
				// line(nx, ny, g);
				dda_move(nx, ny, g);
				System.out.println(current_units_x + " " + current_units_y);
				// g.drawLine(currentX+300, currentY+300, currentX+300,
				// currentY+300);
				// gcode.execute(nx, ny, g);
				// line(nx,ny,g);
			}
			// gcode.execute(currentX, currentY, g);
			// line(x, y);
			// current_units_x = (int) nx;
			// current_units_y = (int) ny;
			// g.drawLine(currentX, currentY, currentX, currentY);
		}

	

}