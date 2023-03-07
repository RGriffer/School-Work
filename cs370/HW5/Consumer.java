public class Consumer extends Thread{

    private Bdbuffer buffer;
    private int numElements;
    private int ID;
    private String sum;

    public Consumer(Bdbuffer b, int numElements, int ID){
        this.buffer = b;
        this.numElements = numElements; // number elements to consume
        this.ID = ID; // consumer ID
        this.sum = "";
    }

    public void run(){ // runs when .start() is called
        while(this.numElements>0){
            String[] removed = this.buffer.remove(); //removes from queue, gets value and index
            String val = removed[0];
            String index = removed[1];
            this.sum += val;
            System.out.format("Consumer: %3d   consumed %s %4s index %s at time %s\n", this.ID, val, "from", index, Invoker.getTime());
            this.numElements--;
        }
    }

    public String getCheckSum(){
        return this.sum;
    }



}
