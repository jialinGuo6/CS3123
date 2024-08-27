package subpackage_2;

public class ThreadArray implements Runnable{
	 
	 int start;
	 int end;
	 int[] array;
     private int sum;        // local sum of a thread
	 // Default constructor
	 public ThreadArray(){
	  
	 }
	 // The constructor accepts an array and the range of array.
	 public ThreadArray(int start,int end,int[] array){
	  this.start = start;
	  this.end = end;
	  this.array =array;
	 }
    // Method for summing arrays in threads
	public void run() {
	  this.sum = 0;
	  for(int i=start;i<end;i++){
	     this.sum += array[i]; 
	  }
	  System.out.println(Thread.currentThread()+" ==>  Sum: "+sum);
	  Test.Total = Test.Total + this.sum;
	 }
    // Safely get private local sum value
	public int getSum() {
		return sum;
	}

	public void setSum(int sum) {
		this.sum = sum;
	}

	public int getStart() {
		return start;
	}

	public void setStart(int start) {
		this.start = start;
	}

	public int getEnd() {
		return end;
	}

	public void setEnd(int end) {
		this.end = end;
	}

	public int[] getArray() {
		return array;
	}

	public void setArray(int[] array) {
		this.array = array;
	}
	 
	}