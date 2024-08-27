package subpackage3;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class Test3 {
	
	public static List<String> getAlphaList(){
		List<String> alpha = new ArrayList<String>();
		int n=97;
		while(n<=122){
			char c = (char)n;
			alpha.add(String.valueOf(c));
			n++;
		}
		
		return alpha;
	}

	public static int[] getArray(int N) {
		Random r = new Random();
		int[] array = new int[N];
		for (int i = 0; i < array.length; i++) {
			array[i] = r.nextInt(10);
		}
		return array;
	}
	
	public static List<Integer> getList(int N) {
		Random r = new Random();
		List<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i < N; i++) {
			list.add(r.nextInt(10));
		}
		return list;
	}
	
	public static void main(String[] args) {		
		ForkJoinPool corePools = ForkJoinPool.commonPool();
		
		System.out.println(corePools.getParallelism());    //11
		
		//1. parallel() method on stream interface;
		//Stream stream1 = Stream.of("AAA","222","CCC","DDD","555");
		//BaseStream ParallelStream1 = stream1.parallel();
		/***************************************/
		System.out.println("-------------------stream interface parallel()------------------\n");
		
		System.out.print("----sequential----");
		Stream.of(" AAA "," 222 "," CCC "," DDD "," 555 ").forEach(System.out::print);
		System.out.print("\n----parallel------");
		Stream.of(" AAA "," 222 "," CCC "," DDD "," 555 ").parallel().forEach(e -> System.out.print("" +e));
		System.out.print("\n                 ");
		Stream.of(1,2,3,4,5,6,7,8,9).parallel().forEach(e -> System.out.print("  " +e));

		/***************************************/
		System.out.print("\n\n----------------collection interface parallelStream()-----------------");

		//2. use parallelStream() method on collection interface
		System.out.print("\n----parallel------");
		Arrays.asList(" AAA "," 222 "," CCC "," DDD "," 555 ").parallelStream().forEach(System.out::print);
		
		System.out.println("\n\n---sequential-0-to-9---");
		
		IntStream.range(0, 10).forEach(System.out::println);
		System.out.println("----parallel-0-to-9----");
		IntStream.range(0, 10).parallel().forEach(System.out::println);
		
		
		System.out.println("\n----sequential----");		
		getAlphaList().stream().forEach(e -> System.out.print(" " +e));
		System.out.println("\n----parallel-----");
		getAlphaList().parallelStream().forEach(e -> System.out.print(" " +e));
		
		/***************************************/
		System.out.print("\n\n----------------example of sum numbers(array/List)-----------------");
		// Given many methods to perform arithmetic operations. 
		// can use reduce, get sum, max ,min and so on.
		// also can use .min(), .max(), .sum() method
		int sumInt = Stream.of(1,2,3,4,5,6,7,8,9,10).parallel().reduce(0, Integer::sum);
		System.out.println("\ntest the reduce to sum sequential a stream(1,2,3,4,5,6,7,8,9,10): "+sumInt);
		System.out.print("\nShow how sum a array or a list:");
		int[] arr = {1,2,3,4,5,6,7,8,9,10};
		List<Integer> integerList = Arrays.asList(1,2,3,4,5,6,7,8,9,10);
		// getList is a array created above
		// examples of sum use list  
		int sumInt1 = integerList.parallelStream().reduce(0, Integer::sum);           // integerList declare on main
		int sumInt2 = getList(1000).parallelStream().reduce(0, Integer::sum);         // return a list by a method getList()
		System.out.print("\nisParallel(): "+ integerList.parallelStream().isParallel());
		System.out.println("\nsum integerList: "+sumInt1);
		System.out.print("\nisParallel(): "+ getList(1000).parallelStream().isParallel());
		System.out.println("\nsum getList(1000): "+sumInt2);
		
		// examples of sum use array
		int sumInt4= Arrays.stream(arr).parallel().sum();                             // arr declare on main
        int sumInt3= Arrays.stream(getArray(1000)).parallel().reduce(0, Integer::sum);// return a array by a method getArray()
		System.out.print("\nisParallel(): "+ Arrays.stream(getArray(1000)).parallel().isParallel());
        System.out.println("\nsum getArray(1000): "+sumInt3);
		System.out.print("\nisParallel(): "+ Arrays.stream(arr).parallel().isParallel());
		System.out.println("\nsum array: "+sumInt4);
	}
}
