package Ploter1;

public class GCodeObject {
	@Override
	public String toString() {
		return "GCodeObject [xAxis=" + xAxis + ", yAxis=" + yAxis + ", zAxis=" + zAxis + ", pointI=" + pointI
				+ ", pointJ=" + pointJ + ", code=" + code + "]"+ System.lineSeparator();
	}
	public float xAxis;
	public float yAxis;
	public float zAxis;
	public float pointI;
	public float  pointJ;
	public String code;
	public GCodeObject(float xAxis, float yAxis, float zAxis, float pointI, float pointJ, String code) {
		super();
		this.xAxis = xAxis;
		this.yAxis = yAxis;
		this.zAxis = zAxis;
		this.pointI = pointI;
		this.pointJ = pointJ;
		this.code = code;
	}
	
	
	

}
