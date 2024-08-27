
public class Thread1 extends Thread{
	
	public void run(){ 
		/*
		 * try { sleep(1000); } catch (InterruptedException e) { // TODO Auto-generated
		 * catch block e.printStackTrace(); }
		 */
		for(int i =0 ;i<50;i++) {
			System.out.println("Thread 1    " + i);
		}
		
	}

}
// synchronized

// sleep(sleeptime); when finish sleep time will atuo start again, but can use interrupt() to end early.
// wait(); it needs a notify()/notifyAll() or signal() awake.
