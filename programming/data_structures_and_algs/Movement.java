public class Movement {
	public final static short DISPLACEMENT=1;
	public final static short ROTATION=2;
	private short type;
	private int magnitude;

	public Movement(short type, int magnitude) {
		this.type=type;
		this.magnitude=magnitude;
	}
	public String toSTRING() {
		if(type==DISPLACEMENT) {
			return "DSP "+ magnitude;
		}else if (type==ROTATION){
			return "ROT " + magnitude;
		}else {
			return "ERR";
		}
	}
	public String toString() {
		return toSTRING();
	}
	public short getType() {
		return this.type;
	}
	public int getMagnitude() {
		return this.magnitude;
	}
	public Movement reverse() {
		return new Movement(type,-magnitude);
	}
}
