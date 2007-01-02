// Boolean Matrix Class
public class BMat
{
  // Instance variables
  private int M[][];
  private int SIZE;

  // Boolean matrix constructors

  public BMat(int s)
  {
    SIZE = s;
    M = new int[SIZE][SIZE];
    // Fill M with zeros
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        M[r][c] = 0;
      }
    }
  } 

  public BMat(int[][] B)
  {
    SIZE = B.length;
    M = new int[SIZE][SIZE];
    // Copy matrix B values into M
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        if(B[r][c] == 0)
          M[r][c] = 0;
        else
          M[r][c] = 1;
      }
    }
  } 

  // Boolean matrix functions

  public int getSIZE()
  {
    return SIZE;
  }

  public BMat copy()
  {
    // Copy current matrix
    BMat W1 = new BMat(this.M);
    return W1;
  }

  public boolean isEqual(BMat M1)
  {
    // Check if matrix equals current object
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        if(this.M[r][c] != M1.M[r][c])
          return false;
      }
    }
    return true;
  }

  public void show()
  {
    // Display matrix
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        System.out.print("  " + M[r][c]);
      }
      System.out.println();
    }
    return;
  }

  public int indegree(int node)
  {
    // In-degree for one node of digraph
    // Nodes are numbered 0,1,2,...,SIZE-1
    int colsum = 0;
    for(int r = 0; r < SIZE; r++)
      colsum = colsum + M[r][node];
    return colsum;
  }

  public int trace()
  {
    // Trace of matrix
    int diag = 0;
    for(int r = 0; r < SIZE; r++)
      diag = diag + M[r][r];
    return diag;
  }

  public int minimum()
  {
    // Minimum value in matrix
    int xmin = M[0][0];
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        if(M[r][c] < xmin)
          xmin = M[r][c];
      }
    }
    return xmin;
  }

  public int maximum()
  {
    // Maximum value in matrix
    int xmax = M[0][0];
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        if(M[r][c] > xmax)
          xmax = M[r][c];
      }
    }
    return xmax;
  }

  // Boolean matrix operations

  public BMat complement()
  {
    // Complement of current matrix (logical NOT)
    BMat W1 = new BMat(SIZE);
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        if(this.M[r][c] == 0)
          W1.M[r][c] = 1;
        else
          W1.M[r][c] = 0;
      }
    }
    return W1;
  }

  public BMat join(BMat M2)
  {
    // Logical OR of current matrix with input matrix
    BMat W1 = new BMat(SIZE);
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        W1.M[r][c] = this.M[r][c] | M2.M[r][c];
      }
    }
    return W1;
  }

  // Project #5 functions to add

  public int arrows()
  {
    // No. of 1's in matrix
    int narrows = 0;
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        narrows = narrows + M[r][c];
      }
    }
    return narrows;
  }

  public int outdegree(int node)
  {
    // Out-degree for one node of digraph
    // Nodes are numbered 0,1,2,...,SIZE-1
    int rowsum = 0;
    for(int c = 0; c < SIZE; c++){
      rowsum = rowsum + M[node][c];
    }
    return rowsum;
  }

  public BMat transpose()
  {
    // Transpose of current matrix
    BMat W1 = new BMat(SIZE);
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        W1.M[r][c] = this.M[c][r];
      }
    }
    return W1;
  }

  public BMat meet(BMat M2)
  {
    // Logical AND of current matrix with input matrix
    BMat W1 = new BMat(SIZE);
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++)
        W1.M[r][c] = this.M[r][c] & M2.M[r][c];
    }
    return W1;
  }

  public BMat product(BMat M2)
  {
    // Boolean product of current matrix with input matrix
    BMat W1 = new BMat(SIZE);
    for(int r = 0; r < SIZE; r++){
      for(int c = 0; c < SIZE; c++){
        W1.M[r][c] = 0;
        for(int k = 0; k < SIZE; k++){
          if(this.M[r][k] > 0 && M2.M[k][c] > 0)
            W1.M[r][c] = 1;
        }
      }
    }
    return W1;
  }

  public BMat power(int N)
  {
    // Raise current matrix to Boolean Nth power
    BMat W1 = new BMat(this.M);
    BMat W2 = new BMat(this.M);
    for(int k = 2; k <= N; k++){
      W1 = W1.product(W2);
    }
    return W1;
  }
  
  public BMat rclosure()	// Returns the reflexive closure of object BM1.
  {
	BMat W1 = new BMat(this.M);
	int r;
	for(r = 0; r < SIZE; r++)
		W1.M[r][r] = 1;
	return W1;
  }
  
  public BMat sclosure()	// Returns the symmetric closure of BM1
  {
	  BMat W1 = new BMat(this.M);
	  W1 = W1.transpose();
	  W1.join(this);
	  return W1;
  }
  
  public BMat tclosure()	// Returns the transitive closure of BM1 (use Warshall's algorithm)
  {
	  BMat W1 = new BMat(this.M);
	  // Warshall's Algorithm
	  int i,j,k;
	  for(k = 0; k < SIZE; k++) {
		  for(i = 0; i < SIZE; i++) {
			  for(j = 0; j < SIZE; j++) {
				  if(W1.M[i][j] != 1) {
					  W1.M[i][j] = W1.M[i][k] & W1.M[k][j];
				  }
			  }
		  }
	  }
	  return W1;
  }
  
  public int rootnode()	// Returns the root node number (0 to SIZE-1) of BM1 if it exists.
  {							// Returns -1 if there is no root node.  For a root node to exist, there must
							// be exactly one node with in-degree 0.  All other nodes must have in-degree 1.
	  int in;
	  int rnode = 0;
	  int nodes = 0;		// Number of nodes with in-degree of zero
	  int node1 = 0;
	  
	  for(int i = 0; i < SIZE; i++) {
		  in = this.indegree(i);
		  if(in == 0) {
			  nodes++;
			  rnode = i;
		  }
		  if(in == 1) {
			  node1++;
		  }
	  }
	  // There can only be one node with in-degree 0
	  if(nodes == 1) {
		  if(node1 == (SIZE-1)) {
			  return rnode;		// Return root node if it exists
		  }
	  }
	  return -1;				// Return -1 if root node doesn't exist
  }
} // end class
