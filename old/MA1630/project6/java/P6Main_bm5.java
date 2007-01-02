// Project #6 test program
public class P6Main_bm5
{
	public static void main(String[] args)
	{
	  // Boolean matrix definitions
	  int M5[][] = new int[][]
	 {{0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
	  {1, 0, 0, 1, 0, 0, 0, 0, 1, 0},
	  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

// Matrix #5
    // Instance objects
    BMat BM1 = new BMat(M5);
    boolean transitive = false;
    boolean cycles = false;
    boolean wconnected = false;
    
    System.out.println("Matrix BM5");
    
    BM1.show();
    
    // Reflexive test
    System.out.print("Is the digraph Reflexive? ");
    BMat tmpBM1 = BM1.rclosure();
    if( BM1.isEqual(tmpBM1) ) {
		System.out.println("Yes");
    }
	else
		System.out.println("No");
    
    // Symmetric test
    System.out.print("Is the digraph Symmetric? ");
    tmpBM1 = BM1.sclosure();
    if( BM1.isEqual(tmpBM1) ) {
    	System.out.println("Yes");
    }
    else
    	System.out.println("No");
    
    // Transitive test
    System.out.print("Is the digraph Transitive? ");
    tmpBM1 = BM1.tclosure();
    if( BM1.isEqual(tmpBM1) ) {
    	System.out.println("Yes");
    	transitive = true;
    }
    else
    	System.out.println("No");
    
    // Cycle test
    System.out.print("Does the digraph have any Cycles? ");
    tmpBM1 = BM1.tclosure();
    if( tmpBM1.trace() != 0) {
    	System.out.println("Yes");
    	cycles = true;
    }
    else
    	System.out.println("No");
    
    // Check if weakly connected
    System.out.print("Is the digraph weakly connected? ");
    tmpBM1 = BM1.sclosure();
    tmpBM1 = tmpBM1.tclosure();
    
    if( tmpBM1.minimum() == 1) {
    	System.out.println("Yes");
    	wconnected = true;
    }
    else
    	System.out.println("No");
    
    // Check for root node
    System.out.print("Does the digraph have a root node? If so, where? ");
    int rnode = BM1.rootnode();
    if(rnode != -1)
    	System.out.println("Yes, " + rnode);
    else
    	System.out.println("No");
    
    // Check for tree
    System.out.print("Is the digraph a tree? ");
    if(BM1.rootnode() == 1 && !cycles && !transitive && wconnected ) {
    	System.out.println("Yes");
    }
    else
    	System.out.println("No");

  } // end main

} // end class

