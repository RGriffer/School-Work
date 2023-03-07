import java.util.Random;

public class Producer extends java.lang.Thread {
	//Necessary variables and object declaration
	Random randomWithSeed;
	private Bdbuffer buffer;
    private int numElements;
    private int seed;
    private String sum;
    private int id;

	public Producer(Bdbuffer buff, int count, int id, int seed) {
		//Assign values to the variables
		randomWithSeed = new Random(seed);
		this.buffer = buff;
        this.numElements = count;
        this.seed = seed;
        this.sum = "";
        this.id = id;
	}
	
	public char getNum(){
        char letter = (char)(this.randomWithSeed.nextInt(26) + 'a'); //generate random char
        return letter;
    }

	@Override
	public void run() {
		/* Your code goes in here
		*
		*
		*
		--->To generate a random character between 'a'(inclusive) and 'z'(inclusive) using the seeded random  number generator use the following code:
		--->          char letter = (char)(this.randomWithSeed.nextInt(26) + 'a');
		*
		*
		*
		*/
		while (this.numElements>0){
            String c = Character.toString(getNum());
            int index = buffer.insert(c);
            this.sum += c;
            System.out.format("\033[0;4mProducer:  %2d   inserted %s%4s index %2d at time\033[0;0m %s\n",this.id, c, "at", index, Invoker.getTime());
            this.numElements--;
        }
	}
	
	public String getCheckSum() {
        return this.sum;
    }
}
