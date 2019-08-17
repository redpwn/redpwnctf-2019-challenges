import java.awt.Point;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class solve {
	
	static ArrayList<Integer>[] graph;
	static HashMap<Point, Integer> weights;
	
	public static void main(String[] args) throws FileNotFoundException {
		//long start = System.currentTimeMillis();
		
		Scanner in = new Scanner(new File(args[0]));
		PrintStream out = new PrintStream(new File(args[1]));
		
		int n = in.nextInt();
		int k = in.nextInt()-1;
		
		graph = new ArrayList[n];
		
		weights = new HashMap<Point, Integer>();
		
		for(int i = 0; i < n; i++) {
			graph[i] = new ArrayList<Integer>();
		}
		
		for(int i = 0; i < n-1; i++) {
			int a = in.nextInt()-1;
			int b = in.nextInt()-1;
			graph[a].add(b);
			graph[b].add(a);
			
			int x = in.nextInt();
			
			weights.put(new Point(a,b), x);
			weights.put(new Point(b,a), x);
		}
		
		int ans = solve(k, -1, 0).x;
		out.println(ans);
		
		in.close();
		out.close();
		
		//long end = System.currentTimeMillis();
		//System.out.println(end-start);
	}
	
	/*
	 * x = cop count
	 * y = shortest path to leaf
	 * */
	static Point solve(int cur, int parent, int depth) {
		
		if(graph[cur].size()==1) {
			return new Point(1, 0);
		}
		
		Point ret = new Point(0, Integer.MAX_VALUE);
		for(int child : graph[cur]) {
			if(child == parent) continue;
			
			int weight = weights.get(new Point(cur, child));
			Point t = solve(child, cur, depth + weight);
			if (t.y - weight <= depth) {
				ret.x++;
			} else {
				ret.x += t.x;
			}
			ret.y = Math.min(ret.y, t.y + weight);
		}
		
		return ret;
	}

}
