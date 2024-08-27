package subpackage3;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class TestParallelStream {

	public static List<String> getAlphaList() {
		List<String> alpha = new ArrayList<String>();
		int n = 97;
		while (n <= 122) {
			char c = (char) n;
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
		
		// 1. parallel() method on stream interface;
		/*** sequential ****/
		Stream.of(" AAA ", " 222 ", " CCC ", " DDD ", " 555 ").forEach(System.out::print);
		/*** parallel ****/
		Stream.of(" AAA ", " 222 ", " CCC ", " DDD ", " 555 ").parallel().forEach(e -> System.out.print("" + e));
		Arrays.asList(" AAA ", " 222 ", " CCC ", " DDD ", " 555 ").stream().parallel().forEach(System.out::print);
		/***************************************/
		// 2. use parallelStream() method on collection interface
		/*** sequential ****/
		Arrays.asList(" EEE ", " 111 ", " FFF ", " GGG ", " 333 ").forEach(System.out::print);
		IntStream.range(0, 10).forEach(System.out::println);
		/*** parallel ****/
		Arrays.asList(" EEE ", " 444 ", " FFF ", " GGG ", " 666 ").parallelStream().forEach(System.out::print);
		IntStream.range(0, 10).parallel().forEach(System.out::println);

		System.out.println();
		/***************************************/
		// getAlphaList() return a list of characters 
		// both can use stream() and parallelStream() to print
		/*** sequential ****/;
		getAlphaList().stream().forEach(e -> System.out.print(" " + e));
		/*** parallel ****/
		getAlphaList().parallelStream().forEach(e -> System.out.print(" " + e));

		
		System.out.println();
		
		/***************************************/
		// given many methods to perform arithmetic operations.
		// can use .reduce() to get sum, max ,min etc.
		// also can just use .min(), .max(), .sum() method
		int sumInt = Stream.of(1, 2, 3, 4, 5, 6, 7, 8, 9, 10).parallel().reduce(0, Integer::sum);
		System.out.print("\nisParallel(): " + Stream.of(1, 2, 3, 4, 5, 6, 7, 8, 9, 10).parallel().isParallel());
		System.out.println("\ntest the reduce to sum a parallel stream(1,2,3,4,5,6,7,8,9,10): " + sumInt);
		
		/***************************************/
		// Example of sum numbers as array/List.
		System.out.print("\nShow how sum a array or a list:");
		int[] arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		List<Integer> integerList = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
		// getList is a array created above
		// examples of sum use list
		int sumInt1 = integerList.parallelStream().reduce(0, Integer::sum);             // integerList declare on main method
		int sumInt2 = getList(1000).parallelStream().reduce(0, Integer::sum);           // return a list by getList() method
		System.out.println("\nsum integerList: " + sumInt1);
		System.out.println("\nsum getList(1000): " + sumInt2);

		// examples of sum use array
		int sumInt4 = Arrays.stream(arr).parallel().sum();                              // arr declare on main method
		int sumInt3 = Arrays.stream(getArray(1000)).parallel().reduce(0, Integer::sum); // return a array by getArray() method
		System.out.println("\nsum getArray(1000): " + sumInt3);
		System.out.println("\nsum arr: " + sumInt4);
	}
}
