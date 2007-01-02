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
        M[r][c] = B[r][c];
      }
    }
  } 

  // Boolean matrix functions

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
	int arrows=0;

    BMat W1 = new BMat(SIZE);
    for(int r = 0; r < SIZE; r++){
        for(int c = 0; c < SIZE; c++) {
       	    if(this.M[r][c] == 1)
    	    	arrows = arrows + 1;
        }
    }
	return arrows;
  }

  public int outdegree(int node)
  {
    // Out-degree for one node of digraph
    // Nodes are numbered 0,1,2,...,SIZE-1
    
    int rowsum = 0;
    for(int c = 0; c < SIZE; c++) {
        rowsum = rowsum + M[node - 1][c];
    }
    return rowsum;
  }

  public BMat transpose()
  {
    // Transpose of current matrix
    BMat W1 = new BMat(SIZE);
    for(int r = 0; r < SIZE; r++) 
        for(int c = 0; c < SIZE; c++) 
            W1.M[c][r] = this.M[r][c];
    return W1;
  }

  public BMat meet(BMat M2)
  {
    // Logical AND of current matrix with input matrix
    BMat W1 = new BMat(SIZE);
    for(int r =0; r < SIZE; r++) {
        for(int c = 0; c < SIZE; c++) {
            if(this.M[r][c] == 1 && M2.M[r][c] == 1) 
                W1.M[r][c] = 1;
            else 
                W1.M[r][c] = 0;
        }
    }
    return W1;
  }

  public BMat product(BMat M2)
  {
    // Boolean product of current matrix with input matrix
    BMat W1 = new BMat(SIZE);
    int tmp = 0;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            for(int k = 0; k < SIZE; k++) {
                W1.M[i][j] = 0;     // 0 by default
                if(this.M[i][k] == 1  && M2.M[k][j] == 1){
                    W1.M[i][j] = 1;
                    break;
                }
            }
        }
    }
    return W1; 
  }

  public BMat power(int N)
  {
    int i = 1;
    // Raise current matrix to Boolean Nth power
    BMat W1 = new BMat(SIZE);
    BMat tempM = new BMat(SIZE);   // temporary M

    // If matrix is raised to the 1st power, return original matrix
    if(i == N)
        W1 = this.copy();
    else
        tempM = this.copy(); // Make a copy of M

    while(i<N){
        W1 = this.product(tempM);

        // Copy for next iteration
        tempM = W1.copy();
        i++;
    }

    return W1;
  }


} // end class
