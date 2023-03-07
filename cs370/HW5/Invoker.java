import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.util.Arrays;

class Invoker {
	public static void main(String[] args) {
		int seed = Integer.parseInt(args[0]);
		Random rand = new Random(seed);
		int bufferSize = rand.nextInt(11-5) + 5;
        int numElements = rand.nextInt(21-10) + 10;
        int numConsumers = rand.nextInt(6-2) + 2;
        int numProducers = rand.nextInt(6-2) + 2;
        int id = 0;
        System.out.println("[Invoker] Buffer Size: " + bufferSize);
        System.out.println("[Invoker] Total Items: " + numElements);
        System.out.println("[Invoker] No. of Producers: " + numProducers);
        System.out.println("[Invoker] No. of Consumers: " + numConsumers);

        Producer[] producers = new Producer[numProducers];
        Consumer[] consumers = new Consumer[numConsumers];
        
        Bdbuffer b = new Bdbuffer(bufferSize); // create buffer
        //Producer p = new Producer(b, numElements, id, seed); // create producer
        //p.start();
        for(int i=0; i<numProducers; i++){
            producers[i] = new Producer(b, numElements/numProducers, i+1, seed);
            producers[i].start();
        }
        /*for(int i=0; i<numProducers; i++){
            try {
                producers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }*/
        
        for(int i=0; i<numConsumers; i++){
            consumers[i] = new Consumer(b, numElements/numConsumers, i+1);
            consumers[i].start();
        }
        for(int i=0; i<numConsumers; i++){
            try {
                consumers[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        String pSum = "";
        String cSum = "";
        for(int i=0; i<numConsumers; i++){
            cSum += consumers[i].getCheckSum();
        }
        for(int i=0; i<numProducers; i++){
            pSum += consumers[i].getCheckSum();
        }
        char temp[] = cSum.toCharArray();
        Arrays.sort(temp);
        cSum = new String(temp);
        System.out.format("The sorted Produced and Consumed strings are the same as shown: %s\n", cSum);
    }
	

	//Call this function from your producer or your consumer to get the time stamp to be displayed
	public static String getTime() {
		Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
		Instant time = Instant.now(offsetClock);
		String timeString = time.toString();
		timeString = timeString.replace('T', ' ');
		timeString = timeString.replace('Z', ' ');
		return(timeString);
	}
}
