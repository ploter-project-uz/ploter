package Ploter1;


import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.annotation.Target;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.regex.Pattern;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.filechooser.FileSystemView;

import com.pi4j.io.gpio.GpioController;
import com.pi4j.io.gpio.GpioFactory;
import com.pi4j.io.gpio.GpioPinDigitalInput;
import com.pi4j.io.gpio.GpioPinDigitalOutput;
import com.pi4j.io.gpio.PinPullResistance;
import com.pi4j.io.gpio.PinState;
import com.pi4j.io.gpio.RaspiPin;

public class InterpreterV2 extends JFrame implements Runnable {
	// final GpioController gpio = GpioFactory.getInstance();
	// final GpioPinDigitalOutput[] pinsOutput = {
	// gpio.provisionDigitalOutputPin(RaspiPin.GPIO_12, PinState.LOW),
	// gpio.provisionDigitalOutputPin(RaspiPin.GPIO_13, PinState.LOW),
	// gpio.provisionDigitalOutputPin(RaspiPin.GPIO_14, PinState.LOW),
	// gpio.provisionDigitalOutputPin(RaspiPin.GPIO_00, PinState.LOW),
	// gpio.provisionDigitalOutputPin(RaspiPin.GPIO_02, PinState.LOW),
	// gpio.provisionDigitalOutputPin(RaspiPin.GPIO_03, PinState.LOW)
	//
	// };
	// final GpioPinDigitalInput[] pinsInput = {
	// gpio.provisionDigitalInputPin(RaspiPin.GPIO_06,
	// PinPullResistance.PULL_DOWN)
	//
	// };
	// ServoMotor pen = new ServoMotor();
	// StepperMotor motorX = new StepperMotor();
	// StepperMotor motorY = new StepperMotor();
	/** The x. */
	private float xAxis = 0;

	/** The y. */
	private float yAxis = 0;

	/** The z. */
	private float zAxis = 0;

	private float pointI = 0;

	private float pointJ = 0;

	private static boolean breakProgram = false;

	Scanner fileScanner = null;
	JButton selectButton = new JButton("Open file");
	JButton runButton = new JButton("Run");
	JButton stopButton = new JButton("Stop");

	Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
	
	Box box = Box.createVerticalBox();
	
	Graphics g;

	private GpioPinDigitalInput[] pinsInput;

	private GpioPinDigitalOutput[] pinsOutput;

	final ArrayList<GCodeObject> gcodes = new ArrayList<GCodeObject>();
	
	GCode4 gcode = new GCode4("", xAxis, yAxis, zAxis, pointI, pointJ, pinsOutput, pinsInput);
	public InterpreterV2() {
		// Gpio.wiringPiSetup();
		this.setTitle("Interpreter ");
		
		this.setPreferredSize(new Dimension(900, 900));
		this.pack();
		this.setVisible(true);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setResizable(false);
		this.selectButton.setPreferredSize(new Dimension(100, 100));
		this.add(selectButton);
		this.add(box, BorderLayout.EAST);
		box.add(Box.createVerticalStrut(5));
		box.add(selectButton);
		box.add(Box.createVerticalStrut(10));
		box.add(runButton);
		box.add(stopButton);
		box.setBorder(BorderFactory.createTitledBorder("Menu"));
		Toolkit.getDefaultToolkit().setDynamicLayout(false);
		selectButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				choseFile();
			}
		});
		runButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				breakProgram = false;
				if (fileScanner == null)
					choseFile();
				else
					run();
			}
		});
		stopButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				breakProgram = true;
			}
		});

	}

	public void choseFile() {
		JFileChooser jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
		int returnValue = jfc.showOpenDialog(null);
		// int returnValue = jfc.showSaveDialog(null);

		if (returnValue == JFileChooser.APPROVE_OPTION) {
			File selectedFile = jfc.getSelectedFile();
			FileInputStream inputStream = null;
			Scanner sc = null;
			System.out.println(selectedFile.getAbsolutePath());
			try {
				inputStream = new FileInputStream(selectedFile.getAbsolutePath());
			    sc = new Scanner(inputStream, "UTF-8");
				//fileScanner = new Scanner(new FileReader(selectedFile));
			    fileScanner = sc;
			} catch (FileNotFoundException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}

	public void run1(Graphics grap) throws InterruptedException, IOException, ParseException {
		
		//grap.drawLine(100, 100, 200, 200);
		this.initArray(gcodes);
		Thread t = new Thread(new Runnable() {
			@Override
			public void run() {
				int i = 0;
				for (GCodeObject gc : gcodes) {
					
					i++;
					if (breakProgram)
						break;
					try {
					//	System.out.println(g.code + g.xAxis);
						
						gcode.execute(gc.code, gc.xAxis, gc.yAxis,gc.zAxis, gc.pointI, gc.pointJ, g);
						//System.out.println("TEST"+ gc.code + gc.xAxis);
					//	g.toString();
					//	gcode.toString();
						// gcode.execute(code, target_units_x2, target_units_y2,
						// cent_x2, cent_y2, graphics);
						// g.execute(g.code, g.target_units_x, g.target_units_y,
						// g.cent_x, g.cent_y, grap);
					//	gcode.toString();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					System.out.println(i);
				}
			};

		});
		t.start();
	}

	public ArrayList<GCodeObject> initArray(ArrayList<GCodeObject> gCodeArray) throws IOException, ParseException {
		// Scanner fileScanner = new Scanner(new FileReader("src/logo
		// uzBigv2.cnc"));
		String line;
		Scanner sc;
		while (fileScanner.hasNextLine()) {
			line = fileScanner.nextLine();
			line = line.replaceFirst("N\\d+ ", "");
			sc = new Scanner(line);

			switch (sc.next()) {

			case "G0":
			case "G00":
			case "G1":
			case "G01":
			case"G1 ":
			case"G0 ":
			
				getOutData2(line);
				gCodeArray.add(new GCodeObject(xAxis, yAxis, zAxis, pointI, pointJ, "G00"));
				// gCodeArray.add(gcode.new G00(line.substring(0, 3), xAxis,
				// yAxis, zAxis, pointI, pointJ));

				break;
			case"G2 ":
			case "G2":
			case "G02":
				getOutData2(line);
				gCodeArray.add(new GCodeObject(xAxis, yAxis, zAxis, pointI, pointJ, "G02"));
				// gCodeArray.add(gcode.new G00(line.substring(0, 3), xAxis,
				// yAxis, zAxis, pointI, pointJ));
			case"G3 ":
			case "G03":
			case "G3":
				getOutData2(line);
				gCodeArray.add(new GCodeObject(xAxis, yAxis, zAxis, pointI, pointJ, "G03"));
				// gCodeArray.add(gcode.new G00(line.substring(0, 3), xAxis,
				// yAxis, zAxis, pointI, pointJ));
				break;
			default:
				break;

			}
			sc.close();
		}
		fileScanner.close();
		return gCodeArray;

	}

	public void getOutData2(String line) throws ParseException {

		StringTokenizer st = new StringTokenizer(line);
		ArrayList<String> tokens = new ArrayList<String>();
		while (st.hasMoreTokens()) {
			tokens.add(st.nextToken());
		}
		tokens.remove(0);

		NumberFormat f = NumberFormat.getInstance(Locale.FRANCE);

		boolean parsed = false;
		for (int i1 = 0; i1 < tokens.size(); i1++) {

			switch (tokens.get(i1).charAt(0)) {
			case 'Z':
			case 'z':
				try {
					zAxis = f.parse(tokens.get(i1).substring(1)).floatValue();
				} finally {
					if (!parsed)
						zAxis = Float.parseFloat(tokens.get(i1).substring(1));
				}

				break;
			case 'X':
			case 'x':
				try {
					xAxis = f.parse(tokens.get(i1).substring(1)).floatValue();
					parsed = true;
				} finally {
					if (!parsed)
						xAxis = Float.parseFloat(tokens.get(i1).substring(1));
				}
				break;
			case 'Y':
			case 'y':
				try {
					yAxis = f.parse(tokens.get(i1).substring(1)).floatValue();
					parsed = true;
				} finally {
					if (!parsed)
						yAxis = Float.parseFloat(tokens.get(i1).substring(1));
				}
				break;
			case 'I':
			case 'i':
				try {
					pointI = f.parse(tokens.get(i1).substring(1)).floatValue();
					parsed = true;
				} finally {
					if (!parsed)
						pointI = Float.parseFloat(tokens.get(i1).substring(1));
				}
				break;
			case 'J':
			case 'j':
				try {
					pointJ = f.parse(tokens.get(i1).substring(1)).floatValue();
					parsed = true;
				} finally {
					if (!parsed)
						pointJ = Float.parseFloat(tokens.get(i1).substring(1));
				}
				break;
			default:
				break;

			}
		}
		// break;
	}

	public static void main(String[] args) throws IOException, InterruptedException, ParseException {

		final InterpreterV2 inte = new InterpreterV2();
		inte.g = inte.getGraphics();
		// inte.setDefaultCloseOperation(operation);
		// final ArrayList<GCode4> gcodes = new ArrayList<GCode4>();
		// inte.initArray(gcodes);
		// for (GCode4 g : gcodes) {
		// // System.out.println(g.toString());
		// // gcode4 g.execute(g.code, g.target_units_x, g.target_units_y,
		// // g.cent_x, g.cent_y, inte.getGraphics());
		// // g.execute(g.X, g.Y, inte.getGraphics());
		// // g.execute(g.code, g.target_units_x, g.target_units_y, g.cent_x,
		// // g.cent_y, inte.getGraphics());
		// g.execute(g.code, g.target_units_x, g.target_units_y, g.cent_x,
		// g.cent_y, inte.getGraphics());
		// // g.execute(g.X, g.Y, inte.getGraphics());
		// }

		// gcodes.get(0).execute(gcodes.get(0).X, gcodes.get(0).Y,
		// inte.getGraphics());
		// System.out.println(gcodes.size());
		// System.out.println(gcodes.toString());
		// System.out.println(gcodes.get(0).actualX + " " +
		// gcodes.get(0).actualY);
		// gcode.
		// gcode.motorX.gpio.shutdown();
		// gcode.motorX.gpio.unprovisionPin(gcode.motorX.pins);

	}

	@Override
	public void run() {

		try {
			run1(this.getGraphics());
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}