import java.util.concurrent.Callable;

public class Callablethread implements Callable<Integer> {
	@Override  
    public Integer call() throws Exception  
    {   
		int sum=0;
        int i = 0;  
        for(;i<50;i++)  
        {  
            sum=i+sum;  
          //  System.out.println("Thread  3   " + i);
        }  
        return sum;  
    }  
}
// Thread.currentThread().getName()