package kickflick.device;

public class accelerometer {
	private short Id_;
	private personality Personality_;
	private byte State_;
	private short xIntensity_;
	private short yIntensity_;
	private short zIntensity_;

	// Constructors
	public accelerometer(short Id,
						 personality Personality,
						 byte State,
						 short xIntensity,
						 )
	{
		this.Id_ = Id;
		this.Personality_ = personality;
		this.State_ = state;
		this.xIntensity_ = xIntensity;
		this.yIntensity_ = yIntensity;
		this.zIntensity_ = zIntensity; 
	}

	public accelerometer(short Id)
	{
		this.Id_ = Id;
		
		personality defaultPersonality;		
		this.Personality_ = defaultPersonality;
		this.State_ = 0;
		this.xIntensity = 0;
		this.yIntensity = 0;
		this.zIntensity = 0;
	}
	
	// Setter
	public void set_Personality(personality Personality) {
		this.Personality_ = Personality;
	}  

	public void set_State(byte State) {
		this.State_ = State;
	}

	public void set_xIntensity(short xIntensity) {
		this.xIntensity_ = xIntensity; 
	}
	
	public void set_yIntensity(short yIntensity) {
		this.yIntensity = yIntensity;
	}	

	public void set_zIntensity(short zIntensity) {
		this.zIntensity = zIntensity;
	}

	// Getter
	public short get_Id() {
		return this.Id_;
	}
 
	public personality get_Personality() {
		return this.Personality_;
	}

	public byte get_State() {
		return this.State_;
	}

	public short get_xIntensity() {
		return this.xIntensity_;
	}

	public short get_yIntensity() {
		return this.yIntensity_;
	}

	public short get_zIntensity() {
		return this.zIntensity_;
	}
}
