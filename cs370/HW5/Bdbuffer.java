public class Bdbuffer {

    public String[] buffer; // buffer array
    private int size; // current # elements in array
    private int totalSize; // total initialized size of array
    private int start; // start index - where to pop from
    private int end; // end index - where to push to

    public Bdbuffer(int size){ // ctor
        this.buffer = new String[size];
        this.size = 0;
        this.totalSize = size;
        this.start=0;
        this.end=0;
    }

    public synchronized int insert(String val) { // insert value at end of queue, returns index it was added to
        while (this.isFull()) {
            try {
                wait(); // wait if full
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        int index = this.end; // store add index
        this.buffer[this.end] = val; // add at end index
        this.end += 1;
        if (this.end == this.totalSize) { // increase end and loop to zero if it goes to the end of the array
            this.end = 0;
        }
        this.size += 1; // increase size counter
        notify(); // notify the array is no longer empty
        return index;
    }

    public synchronized String[] remove() { // remove from front of queue, returns value and index it was at
        while (this.isEmpty()) {
            try {
                wait(); // wait if empty
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        String val = this.buffer[this.start];
        int index = this.start; // index it was at
        this.start += 1; // increase index where the next will pop from
        if (this.start == this.totalSize) { // loop back to zero if it reaches the end of the array
            this.start = 0;
        }
        this.size -= 1; // decrease size
        notify(); // notify that the array is no longer full
        return new String[] {val, String.valueOf(index)};

    }

    public synchronized boolean isFull(){ // check if array is full
        return this.totalSize == this.size;
    }

    public synchronized boolean isEmpty(){ // check if array is empty
        synchronized (this){
            return this.size==0;
        }
    }

}

