import java.util.LinkedList;
import java.util.Queue;

public class FordFulkerson {
	private WeightedDigraph g;
	private boolean visited[];
	private WeightedEdge edgeTo[];
	
	public FordFulkerson(WeightedDigraph g) {
		this.g = g;
		visited = new boolean[g.V()];
		edgeTo = new WeightedEdge[g.V()];
		
	}
	
	public void start(int src, int dst){
		while(BFS(g, src, dst)) {
			int minFlow = Integer.MAX_VALUE;
			int cp = dst;
			while(cp != src) {
				if (minFlow > edgeTo[cp].getW()) minFlow = edgeTo[cp].getW();
				cp = edgeTo[cp].from();
			}
			
			for (int v = dst; v != src; v = edgeTo[v].from()) {
                edgeTo[v].addResidualFlowTo(v, minFlow); 
            }
		}
	}
	
	private boolean BFS(WeightedDigraph g, int src, int dst) {
		Queue<Integer> q = new LinkedList<Integer>();
		boolean[] visited = new boolean[g.V()];
		
		q.add(src);
		edgeTo[src] = null;
		
		while(!q.isEmpty()) {
			int cp = q.poll();
			
			if(!visited[cp]) {
				visited[cp] = true;
				
				if(cp == dst) return true;
				
				for(WeightedEdge e : g.adj(cp)) {
					if(!visited[e.to()]) {
						q.add(e.to());
						edgeTo[e.to()] = e;
					}
				}
			}
		}
		
		return false;
	}
}