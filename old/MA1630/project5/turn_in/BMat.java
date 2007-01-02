// Joshua Braegger
// MA1630
// Project #5
// Boolean Matrix Class
public class BMat
{
  // Prewritten stuff removed to save paper (As per Dr. McMaster)
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
