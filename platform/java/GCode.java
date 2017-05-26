package Ploter1;

public class GCode {
	public String gcode;
	public double X;
	public double Y;
	public double Z;
	public GCode(String gcode, double X, double Y,double Z) {
		this.X = X;
		this.Y = Y;
		this.Z = Z;
		this.gcode = gcode;
	}

	public void execute() {

	}

	public String getCode() {
		return gcode;
	}

	public void setCode(String code) {
		this.gcode = code;
	}

	public double getX() {
		return X;
	}

	public void setX(double x) {
		X = x;
	}

	public double getY() {
		return Y;
	}

	public void setY(double y) {
		Y = y;
	}

	public class G00 extends GCode {

		public G00(String gcode, double X, double Y, double z) {
			super(gcode, X, Y, z);

		}

		@Override
		public String toString() {
			return "G00 [gcode=" + gcode  + ", X=" + X + ", Y=" + Y
					+ ", Z=" + Z + "] "+System.lineSeparator();
		}

		@Override
		public void execute() {
			// TODO Auto-generated method stub
			super.execute();
		}
		

	}

	public class G01 extends GCode {

		public G01(String gcode, double X, double Y,double zAxis) {
			super(gcode, X, Y, zAxis);
		}
		public String toString() {
			return "G01 [gcode=" + gcode + "X=" + X + ", Y=" + Y
					+ ", Z=" + Z + "] "+System.lineSeparator();
		}
		public void execute() {
			// TODO Auto-generated method stub
			super.execute();
		}
	}
}
