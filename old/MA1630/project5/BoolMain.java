// BoolMain - program to test BMat class

public class BoolMain
{
  public static void main(String[] args)
  {
      int[][] R = new int[][]
                  {{0, 1, 0, 0, 1},
                   {0, 1, 1, 0, 0},
                   {0, 0, 0, 0, 0},
                   {1, 0, 0, 1, 0},
                   {0, 0, 0, 0, 1}};
      int[][] C = new int[][] 
                  {{0, 1, 0, 0, 0},
                   {0, 0, 1, 0, 0},
                   {0, 0, 0, 1, 0},
                   {1, 0, 0, 0, 1},
                   {0, 1, 0, 0, 0}};

      // Construct initial matrix
      BMat MR = new BMat(R);
      System.out.println("\n Initial matrix");
      MR.show();

      // Calculate trace of matrix
      int tr = MR.trace();
      System.out.println("\n Trace = " + tr);

      // Calculate complement of matrix
      BMat MRC = MR.complement();
      System.out.println("\n Complement");
      MRC.show();

      // Calculate join (OR) of two matrices
      BMat MRJ = MR.join(MRC);
      System.out.println("\n Join of matrix with complement");
      MRJ.show();

      // Calculate product of a matrix
      BMat TM = MR.product(MRC);
      System.out.println("\n Product of matrix");
      TM.show();

      BMat TransposeMR = MR.transpose();

      int arrows = TM.arrows();
      System.out.println("\n Arrows = " + arrows);
      
      BMat MC = new BMat(C);
      MC.show();
      System.out.println("\n");
      BMat powerC = MC.power(19);
      System.out.println("\n");
      powerC.show();

  }

} // end class
