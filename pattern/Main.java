package com.example.main;
import java.io.*;
import java.util.*;

public class Main {
    //static final String TASKNAME = new String("a");

    public static void main(String[] args) throws IOException {
        //InputReader in = new InputReader(new FileInputStream(new File(TASKNAME + ".in")));
        //PrintWriter out = new PrintWriter(TASKNAME + ".out");
        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);

        Task solver = new Task();
        solver.solve(in, out);
        out.close();
    }
}

class Task {
    public void solve(InputReader in, PrintWriter out) {
        
    }
}

class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream), 32768);
        tokenizer = null;
    }

    public boolean isNext() {
        if (tokenizer == null || !tokenizer.hasMoreTokens()) {
            String line;
            try {
                if ((line = reader.readLine()) == null)
                    return false;
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            tokenizer = new StringTokenizer(line);
        }
        return true;
    }

    public String next() {
        isNext();
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public long nextLong() {
        return Long.parseLong(next());
    }
}