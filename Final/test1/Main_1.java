import java.util.concurrent.ExecutionException;
import java.util.concurrent.FutureTask;

/*Java provides three ways to create threads:

By implementing the Runnable interface;
By inheriting from the Thread class itself;
Use ExecutorService, Callable, and Future to implement multithreading with returned results. */
public class Main_1 {
    // The root thread Main
    // Java
	// time segment 0.02s
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Main Thread Start");
		
		//extends Thread interface
		Thread1 t1 = new Thread1();
		//t1.setDaemon(true);
		t1.start();
		//implements Runnable interface
		Thread  t2 = new Thread(new Thread2());
		t2.start();
		
		//implements Callable interface
		FutureTask<Integer> ft = new FutureTask<>(new Callablethread());  
		Thread t3 = new Thread(ft,"Thread3");  
		t3.start();
        try {
			System.out.println("Thread3 Callable's run() can return value："+ft.get());
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ExecutionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}  
		System.out.println("Main Thread End");


	}

}
