package subpackage_2;

import java.util.concurrent.Callable;

public class CallableThreadArray implements Callable<Integer> {

	int start;
	int end;
	int[] array;

	public CallableThreadArray() {

	}

	public CallableThreadArray(int start, int end, int[] array) {
		super();
		this.start = start;
		this.end = end;
		this.array = array;
	}

	@Override
	public Integer call() throws Exception {
		int sum = 0;
		for (int i = start; i < end; i++) {
			sum += array[i];
		}
		
		return sum;
	}
}