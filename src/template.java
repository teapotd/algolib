import java.io.*;
import java.util.*;

public class Task extends PrintWriter {
	BufferedReader reader = new BufferedReader(
			new InputStreamReader(System.in), 32768);
	StringTokenizer tok;

	public static void main(String[] a) {
		try (Task t = new Task()) { t.solve(); }
	}

	Task() { super(System.out); }

	String scan() {
		while (tok == null || !tok.hasMoreTokens())
			try {
				tok = new StringTokenizer(
					reader.readLine());
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		return tok.nextToken();
	}

	int scanInt() {
		return Integer.parseInt(scan());
	}

	void solve() {
		int n = scanInt();
		printf("hello %d", n);
	}
}
