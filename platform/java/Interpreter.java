package Ploter1;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// TODO: Auto-generated Javadoc
/**
 * The Class Interpreter.
 */
public class Interpreter {

	/** The x. */
	private static double xAxis;

	/** The y. */
	private static double yAxis;

	/** The z. */
	private static double zAxis;

	/** The g. */
	private static GCode gcode = new GCode("", xAxis, yAxis, zAxis);

	/** The my pattern. */
	private static Pattern myPattern = Pattern
			.compile("G\\d+ ((X(\\d+|\\d+.\\d+) Y(\\d+|\\d+.\\d+))|Z([+-]?\\d+|\\d+.\\d+))");

	/**
	 * Inits the array.
	 * 
	 * @param gCodeArray
	 *            the g code array
	 * @return the array list
	 * @throws IOException
	 *             Signals that an I/O exception has occurred.
	 */
	public ArrayList<GCode> initArray(ArrayList<GCode> gCodeArray) throws IOException {
		Scanner fileScanner = new Scanner(new FileReader("src/gcode.txt"));
		String line;
		while (fileScanner.hasNextLine()) {
			line = fileScanner.nextLine();
			switch (line.substring(0, 2)) {
			case "G0":
			case "G00": {
				getOutData(line);
				gCodeArray.add(gcode.new G00(line.substring(0, 3), xAxis, yAxis, zAxis));
				break;
			}
			case "G1":
			case "G01":
				getOutData(line);
				gCodeArray.add(gcode.new G01(line.substring(0, 3), xAxis, yAxis, zAxis));
				break;
			default:
				break;

			}

		}

		return gCodeArray;

	}

	/**
	 * Gets the out data.
	 *
	 * @param line
	 *            the line
	 * @return the out data
	 */
	public void getOutData(String line) {
		Matcher myMatcher = myPattern.matcher(line);
		myMatcher.find();
		myMatcher.matches();
		myMatcher.matches();
		// *--- GROUP 3(X) 4(Y) 5(Z) --*//
		if (myMatcher.group(3) != null)
			xAxis = Double.parseDouble(myMatcher.group(3));
		else {
			xAxis = Double.NaN;
		}
		if (myMatcher.group(4) != null)
			yAxis = Double.parseDouble(myMatcher.group(4));
		else {
			yAxis = Double.NaN;
		}
		if (myMatcher.group(5) != null)
			zAxis = Double.parseDouble(myMatcher.group(5));
		else {
			zAxis = Double.NaN;
		}
	}

	/**
	 * The main method.
	 *
	 * @param args
	 *            the arguments
	 * @throws IOException
	 *             Signals that an I/O exception has occurred.
	 */
	public static void main(String[] args) throws IOException {
		final Interpreter inte = new Interpreter();
		final ArrayList<GCode> gcodes = new ArrayList<GCode>();
		inte.initArray(gcodes);
		System.out.println(gcodes.size());
		System.out.println(gcodes.toString());

	}
}
