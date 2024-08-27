package subpackage_2;

import java.util.Random;

public class Test {
	static int Total;
	static int threadid = 4;
	static int N = 8;

	public static int[] randArr() {
		Random r = new Random();
		int[] array = new int[N];
		for (int i = 0; i < array.length; i++) {
			array[i] = r.nextInt(10);
		}
		return array;
	}

	public static void printArr(int[] array) {
		for (int i = 0; i < array.length; i++) {
			System.out.print(array[i] + " ");
		}
		System.out.println();
	}
    
	public static void main(String[] args) throws InterruptedException {                       
		System.out.println("Main Thread Start "+ Thread.currentThread().getName());
		// get a array from randArr method that code on the above
		int[] array = randArr();
		printArr(array);
        // create four threads 
		ThreadArray t1 = new ThreadArray(0 * N/threadid,(0 + 1) * N/threadid,array);
		ThreadArray t2 = new ThreadArray(1 * N/threadid,(1 + 1) * N/threadid,array);
		ThreadArray t3 = new ThreadArray(2 * N/threadid,(2 + 1) * N/threadid,array);
		ThreadArray t4 = new ThreadArray(3 * N/threadid,(3 + 1) * N/threadid,array);
		Thread  thread_1 = new Thread(t1);
		Thread  thread_2 = new Thread(t2);
		Thread  thread_3 = new Thread(t3);
		Thread  thread_4 = new Thread(t4);
		
		thread_1.start();
		thread_2.start();
		thread_3.start();
		thread_4.start();
	    /* Consider main(root) thread has 4 sub-threads. Instead of 5 threads run together.
		 * Make sure all sub-threads, finish before main get all resluts form them. 
		 * use join() to avoid this case:    Sum: 12
		 *                                   Sum: 3
		 *                                   Total :15 ==> 12 + 3 + 0 + 0
		 *                                   Sum: 9	 
		 *                                   Sum: 17
		 */
		thread_1.join();
	    thread_2.join();
		thread_3.join();
		thread_4.join();
	

		System.out.println("Total :" +(t1.getSum()+t2.getSum()+t3.getSum()+t4.getSum()));
		System.out.println("Main Thread End");
		/* Main Thread Start main
		 * 5 8 0 8 9 8 1 8 
		 * Thread[Thread-0,5,main] ==>  Sum: 13
		 * Thread[Thread-2,5,main] ==>  Sum: 17
		 * Thread[Thread-1,5,main] ==>  Sum: 8
		 * Thread[Thread-3,5,main] ==>  Sum: 9
		 * Total :47
		 * Main Thread End
		 */
	}
}

/*
 * for (int t = 0; t < threadid; t++) { start = t * N/threadid; end = (t + 1) *
 * N / threadid; ThreadArray thread_task; System.out.println("# of thread id "+
 * t + ",range[ "+ start+", "+end+" )"); //new ThreadArray(start,
 * end,array).run(); System.out.print("Thread "+t+": "); thread_task = new
 * ThreadArray(start, end,array); thread_task.run();
 * 
 * }
 */
