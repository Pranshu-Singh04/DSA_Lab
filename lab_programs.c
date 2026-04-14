/*
 * ============================================================
 *  LAB 6 - GREEDY METHOD
 * ============================================================
 *
 * AIM: Write programs to implement sorting a given list of
 *      elements in ascending order using the following sorting
 *      methods: Heapsort - max heap.
 *
 *      Problem to implement Knapsack problem and Huffman
 *      encoding using the Greedy Method.
 *
 * ============================================================
 *  KNAPSACK PROBLEM
 * ============================================================
 *
 * PRINCIPLE (Fractional Knapsack - Greedy Approach):
 *   - Each item has a value and a weight.
 *   - Compute value/weight ratio for each item.
 *   - Sort items in descending order of ratio.
 *   - Greedily pick items with the highest ratio first.
 *   - If the item fits completely, take it fully.
 *   - If not, take the fraction that fits.
 *   - This gives the optimal solution for the fractional
 *     knapsack problem.
 */

#include <stdio.h>

/* --- Knapsack Problem --- */

struct Item {
    int value, weight;
    float ratio;
};

/* Bubble sort items in descending order of ratio */
void sort(struct Item arr[], int n) {
    int i, j;
    struct Item temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].ratio < arr[j + 1].ratio) {
                temp     = arr[j];
                arr[j]   = arr[j + 1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    float capacity, total_value = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item arr[n];

    /* Input value and weight for each item */
    for (int i = 0; i < n; i++) {
        printf("Enter value & weight of item %d: ", i + 1);
        scanf("%d %d", &arr[i].value, &arr[i].weight);
        /* Compute value-to-weight ratio */
        arr[i].ratio = (float) arr[i].value / arr[i].weight;
    }

    printf("Enter capacity of knapsack: ");
    scanf("%f", &capacity);

    sort(arr, n);

    /*
     * Greedy selection:
     *   - If capacity >= item weight, take the whole item.
     *   - Otherwise, take the fraction: ratio * remaining capacity,
     *     then break (knapsack is full).
     */
    for (int i = 0; i < n; i++) {
        if (capacity >= arr[i].weight) {
            total_value += arr[i].value;    /* take full item */
            capacity    -= arr[i].weight;
        } else {
            total_value += arr[i].ratio * capacity;  /* take fraction */
            break;
        }
    }

    printf("Maximum Value = %.2f\n", total_value);
    return 0;
}


/*
 * ============================================================
 *  HUFFMAN CODING  (Python pseudocode transcribed to C-style
 *  comments because the notebook used Python)
 * ============================================================
 *
 * PRINCIPLE (Huffman Encoding - Greedy):
 *   - Build a frequency table for each character.
 *   - Use a min-heap (priority queue) to always merge the two
 *     nodes with the smallest frequencies.
 *   - Assign '0' to every left branch and '1' to every right
 *     branch while traversing the Huffman tree.
 *   - Characters that appear more frequently get shorter codes.
 *   - This produces a prefix-free, optimal variable-length code.
 *
 * Python version (from notebook):
 *
 *   import heapq
 *   freq = {'a': 5, 'b': 9, 'c': 2, 'd': 16, 'e': 16, 'f': 45}
 *   heap = [[wt, [ch, ""]] for ch, wt in freq.items()]
 *   heapq.heapify(heap)
 *   while len(heap) > 1:
 *       l = heapq.heappop(heap)
 *       r = heapq.heappop(heap)
 *       for pair in l[1:]:
 *           pair[1] = '0' + pair[1]
 *       for pair in r[1:]:
 *           pair[1] = '1' + pair[1]
 *       heapq.heappush(heap, [l[0] + r[0]] + l[1:] + r[1:])
 *   huffman = sorted(heap[0][1:], key=lambda x: len(x[1]))
 *   for ch, code in huffman:
 *       print(ch, " ", code)
 */


/*
 * ============================================================
 *  LAB 7 - GREEDY METHODS (GRAPHS)
 * ============================================================
 *
 * AIM: Implementation of the shortest path problem using
 *      the Greedy Method.
 *
 * ============================================================
 *  DIJKSTRA'S ALGORITHM
 * ============================================================
 *
 * PRINCIPLE:
 *   - Finds the single-source shortest path in a weighted graph
 *     with non-negative edge weights.
 *   - Maintain a dist[] array initialised to INF; dist[src] = 0.
 *   - At each step, pick the unvisited vertex u with minimum
 *     distance (greedy choice).
 *   - Relax all neighbours v of u:
 *       if dist[u] + graph[u][v] < dist[v]  →  dist[v] = dist[u] + graph[u][v]
 *   - Mark u as visited and repeat until all vertices are done.
 *   - Time complexity: O(V^2) with adjacency matrix.
 */

#include <stdio.h>
#define V  4
#define ZINF 9999   /* "infinity" sentinel */

int main_dijkstra() {   /* renamed to avoid duplicate main */

    /* Adjacency matrix for the graph */
    int graph[V][V] = {
        {0, 5, 0, 10},
        {0, 0, 3, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };

    int dist[V], visited[V] = {0};

    /* Initialise distances */
    for (int i = 0; i < V; i++)
        dist[i] = ZINF;
    dist[0] = 0;   /* source = vertex 0 */

    /* Main loop: V-1 iterations */
    for (int i = 0; i < V - 1; i++) {
        int min = ZINF, u;

        /* Pick unvisited vertex with minimum distance */
        for (int j = 0; j < V; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u   = j;
            }
        }
        visited[u] = 1;

        /* Relax neighbours of u */
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    /* Print shortest distances */
    for (int i = 0; i < V; i++)
        printf("%d\n", dist[i]);

    return 0;
}


/*
 * ============================================================
 *  FLOYD-WARSHALL ALGORITHM
 * ============================================================
 *
 * PRINCIPLE:
 *   - Finds ALL-PAIRS shortest paths in a weighted graph.
 *   - Uses dynamic programming / relaxation through each
 *     intermediate vertex k:
 *       dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
 *   - Works with negative weights (but not negative cycles).
 *   - Time complexity: O(V^3).
 */

#include <stdio.h>
#define V  4
#define INF 9999

int main_floyd() {   /* renamed to avoid duplicate main */

    int dist[V][V] = {
        {0,   5,  INF,  10},
        {INF, 0,   3,  INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    /* Relax through each intermediate vertex k */
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    /* Print all-pairs shortest path matrix */
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}


/*
 * ============================================================
 *  LAB 8 - GREEDY METHOD (SPANNING TREES)
 * ============================================================
 *
 * AIM: Implementation of Prim's and Kruskal's algorithms for
 *      finding the Minimum Spanning Tree (MST).
 *
 * ============================================================
 *  PRIM'S ALGORITHM
 * ============================================================
 *
 * PRINCIPLE:
 *   - Start from any source vertex.
 *   - Maintain a visited set; at each step greedily pick the
 *     minimum-weight edge connecting a visited vertex to an
 *     unvisited vertex.
 *   - Add that unvisited vertex to the MST.
 *   - Repeat until all V vertices are included.
 *   - Uses a min-heap (priority queue) for efficiency: O(E log V).
 *
 * Python version (from notebook):
 *
 *   import heapq
 *   graph = {
 *       0: [(1,2),(3,6)],
 *       1: [(0,2),(2,3),(3,8),(4,5)],
 *       2: [(1,3),(4,7)],
 *       3: [(0,6),(1,8),(4,9)],  -- (approximate from notebook)
 *   }
 *   visited = set()
 *   min_heap = [(0, 0)]
 *   cost = 0
 *   while min_heap:
 *       w, u = heapq.heappop(min_heap)
 *       if u not in visited:
 *           visited = visited.add(u)
 *           cost += w
 *           for v, wt in graph[u]:
 *               if v not in visited:
 *                   heapq.heappush(min_heap, (wt, v))
 *   print("MST cost =", cost)
 */


/*
 * ============================================================
 *  KRUSKAL'S ALGORITHM
 * ============================================================
 *
 * PRINCIPLE:
 *   - Sort all edges by weight in ascending order.
 *   - Use a Union-Find (Disjoint Set Union) structure.
 *   - Greedily pick the smallest edge; add it to MST only if
 *     it does NOT form a cycle (i.e., its endpoints belong to
 *     different components).
 *   - Stop when MST has V-1 edges.
 *   - Time complexity: O(E log E).
 *
 * Key Union-Find operations:
 *   find(n)  : returns root/representative of n's set.
 *   union(x,y): merges the sets containing x and y.
 */

#include <stdio.h>

/* Sample edge list from notebook */
/* edges = [(2,0,1),(6,0,3),(3,1,2),(8,1,3),(5,1,4),(7,2,4)] */
/* format: (cost, u, v) */

int parent[10];

/* Find with path compression */
int find(int n) {
    if (parent[n] == n)
        return n;
    return parent[n] = find(parent[n]);
}

/* Union by representative */
void unite(int u, int v) {
    parent[find(u)] = find(v);
}

int main_kruskal() {   /* renamed to avoid duplicate main */

    /* edges: {cost, u, v} - sorted by cost */
    int edges[][3] = {
        {2,0,1},{3,1,2},{5,1,4},
        {6,0,3},{7,2,4},{8,1,3},{8,1,3},{6,5,4}
    };
    int num_edges = 8;

    /* Initialise each vertex as its own parent */
    for (int i = 0; i < 6; i++)
        parent[i] = i;

    int mst_cost = 0;

    /* Iterate through sorted edges */
    for (int i = 0; i < num_edges; i++) {
        int cost = edges[i][0];
        int u    = edges[i][1];
        int v    = edges[i][2];

        /* Add edge only if it doesn't form a cycle */
        if (find(u) != find(v)) {
            unite(u, v);
            mst_cost += cost;
            printf("MST cost += %d\n", cost);
        }
    }

    printf("MST cost = %d\n", mst_cost);
    return 0;
}


/*
 * ============================================================
 *  LAB 10 - DYNAMIC PROGRAMMING
 * ============================================================
 *
 * AIM: Implementation of the Longest Common Subsequence (LCS)
 *      problem using Dynamic Programming.
 *
 * PRINCIPLE:
 *   - Given two strings s1 and s2, find the length of the
 *     longest subsequence common to both.
 *   - A subsequence is NOT required to be contiguous.
 *   - Build a 2D DP table dp[i][j]:
 *       if s1[i-1] == s2[j-1]:
 *           dp[i][j] = dp[i-1][j-1] + 1
 *       else:
 *           dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *   - Backtrack through the table to reconstruct the LCS.
 *   - Time complexity: O(m*n), Space: O(m*n).
 *
 * Python version (from notebook):
 *
 *   s1 = "ABCBDAB"
 *   s2 = "BDCAB"
 *   m, n = len(s1), len(s2)
 *   dp = [[0] * (n+1) for _ in range(m+1)]
 *   for i in range(1, m+1):
 *       for j in range(1, n+1):
 *           if s1[i-1] == s2[j-1]:
 *               dp[i][j] = dp[i-1][j-1] + 1
 *           else:
 *               dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *   i, j = m, n
 *   lcs = ""
 *   while i > 0 and j > 0:
 *       if s1[i-1] == s2[j-1]:
 *           lcs = s1[i-1] + lcs
 *           i -= 1
 *           j -= 1
 *       elif dp[i-1][j] > dp[i][j-1]:
 *           i -= 1
 *       else:
 *           j -= 1
 *   print("length:", dp[m][n])
 *   print("LCS:", lcs)
 */

#include <stdio.h>
#include <string.h>

#define MAXN 100

int max(int a, int b) { return a > b ? a : b; }

int main_lcs() {
    char s1[] = "ABCBDAB";
    char s2[] = "BDCAB";
    int m = strlen(s1), n = strlen(s2);
    int dp[MAXN][MAXN];

    /* Fill DP table */
    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int j = 0; j <= n; j++) dp[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    /* Backtrack to find LCS string */
    int i = m, j = n;
    char lcs[MAXN];
    int idx = 0;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            lcs[idx++] = s1[i-1];
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    lcs[idx] = '\0';

    /* Reverse the LCS string */
    for (int a = 0, b = idx-1; a < b; a++, b--) {
        char tmp = lcs[a]; lcs[a] = lcs[b]; lcs[b] = tmp;
    }

    printf("length: %d\n", dp[m][n]);
    printf("LCS: %s\n", lcs);
    return 0;
}


/*
 * ============================================================
 *  LAB 11 - DYNAMIC PROGRAMMING
 * ============================================================
 *
 * AIM: Implementation of Matrix Chain Multiplication and
 *      0/1 Knapsack problem using Dynamic Programming.
 *
 * ============================================================
 *  MATRIX CHAIN MULTIPLICATION
 * ============================================================
 *
 * PRINCIPLE:
 *   - Given a chain of matrices A1, A2, ..., An, find the
 *     optimal parenthesisation that minimises the number of
 *     scalar multiplications.
 *   - Let dp[i][j] = minimum cost to multiply matrices i..j.
 *   - For each chain length l from 2 to n:
 *       for each starting index i:
 *           j = i + l - 1
 *           for each split k in [i, j-1]:
 *               cost = dp[i][k] + dp[k+1][j]
 *                    + arr[i-1]*arr[k]*arr[j]
 *               dp[i][j] = min(dp[i][j], cost)
 *   - Time complexity: O(n^3).
 *
 * Python version (from notebook):
 *
 *   arr = [10, 30, 5, 60]
 *   n = len(arr)
 *   dp = [[0]*n for _ in range(n)]
 *   for l in range(2, n):           # chain length
 *       for i in range(1, n-l+1):
 *           j = i + l - 1
 *           dp[i][j] = float('inf')
 *           for k in range(i, j):
 *               cost = dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j]
 *               dp[i][j] = min(dp[i][j], cost)
 *   print("min cost =", dp[1][n-1])
 */

#include <stdio.h>
#include <limits.h>

int min(int a, int b) { return a < b ? a : b; }

int main_mcm() {
    int arr[] = {10, 30, 5, 60};
    int n = 4;   /* number of matrices = n-1 = 3 */
    int dp[10][10];

    /* Initialise all dp values to 0 */
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = 0;

    /* Fill DP for increasing chain lengths */
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j]
                           + arr[i-1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    printf("min cost = %d\n", dp[1][n-1]);
    return 0;
}


/*
 * ============================================================
 *  0/1 KNAPSACK  (Dynamic Programming version)
 * ============================================================
 *
 * PRINCIPLE (differs from fractional greedy knapsack):
 *   - Each item must be taken WHOLE or left entirely (0 or 1).
 *   - Build a 2D DP table dp[i][w]:
 *       = max value using first i items with capacity w.
 *   - Recurrence:
 *       if wt[i-1] <= w:
 *           dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]],
 *                          dp[i-1][w])
 *       else:
 *           dp[i][w] = dp[i-1][w]
 *   - Time complexity: O(n * W).
 *
 * Python version (from notebook):
 *
 *   # 0/1 Knapsack
 *   wt  = [10, 20, 30]
 *   val = [60, 100, 120]
 *   W   = 50
 *   n   = len(wt)
 *   dp  = [[0]*(W+1) for _ in range(n+1)]
 *   for i in range(1, n+1):
 *       for w in range(W+1):
 *           if wt[i-1] <= w:
 *               dp[i][w] = max(val[i-1] + dp[i-1][w-wt[i-1]],
 *                              dp[i-1][w])
 *           else:
 *               dp[i][w] = dp[i-1][w]
 *   print("max value =", dp[n][W])
 */

#include <stdio.h>

int main_01knapsack() {
    int wt[]  = {10, 20, 30};
    int val[] = {60, 100, 120};
    int W     = 50;
    int n     = 3;
    int dp[10][60];

    /* Initialise */
    for (int i = 0; i <= n; i++)
        for (int w = 0; w <= W; w++)
            dp[i][w] = 0;

    /* Fill DP table */
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i-1] <= w)
                dp[i][w] = (val[i-1] + dp[i-1][w - wt[i-1]] > dp[i-1][w])
                           ? val[i-1] + dp[i-1][w - wt[i-1]]
                           : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    printf("max value = %d\n", dp[n][W]);
    return 0;
}


/*
 * ============================================================
 *  DRIVER MAIN
 *  (Call whichever function you need; rename them back to
 *   main() if compiling individually.)
 * ============================================================
 */
int main() {
    printf("=== Fractional Knapsack ===\n");
    /* main() already defined above for knapsack;
       rename the others to run them individually.     */

    printf("=== LCS ===\n");
    main_lcs();

    printf("=== Matrix Chain Multiplication ===\n");
    main_mcm();

    printf("=== 0/1 Knapsack ===\n");
    main_01knapsack();

    printf("=== Dijkstra ===\n");
    main_dijkstra();

    printf("=== Floyd-Warshall ===\n");
    main_floyd();

    printf("=== Kruskal ===\n");
    main_kruskal();

    return 0;
}
