import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStream;

public class Main {
	public static void main(String[] args) {
		try (PrintWriter out =
		     new PrintWriter(System.out)) {
			new Task().solve(
				new InputReader(System.in), out);
		}
	}

	static class InputReader {
		BufferedReader r;
		StringTokenizer t = null;

		public InputReader(InputStream s) {
			r = new BufferedReader(
				new InputStreamReader(s), 32768);
		}

		public String next() {
			while (t == null || !t.hasMoreTokens())
				try {
					t = new StringTokenizer(
						r.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			return t.nextToken();
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}
	}

	static class Task {
		public void solve(InputReader in,
		                  PrintWriter out) {
			int n = in.nextInt();
			out.printf("hello %d", n);
		}
	}
}
