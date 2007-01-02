// Project #5 main program

public class P5Main
{
  public static void main(String[] args)
  {
    // Boolean matrix definitions

    int A[][] = new int[][]
                {{0, 1, 0, 0, 1},
                 {0, 0, 1, 0, 0},
                 {0, 0, 0, 0, 0},
                 {1, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0}};

    int B[][] = new int[][]
                {{0, 1, 0, 0, 1},
                 {0, 1, 1, 0, 0},
                 {0, 0, 1, 0, 0},
                 {1, 0, 0, 0, 0},
                 {0, 1, 0, 0, 1}};

    int C[][] = new int[][]
                {{0, 1, 0, 0, 0},
                 {0, 0, 1, 0, 0},
                 {0, 0, 0, 1, 0},
                 {1, 0, 0, 0, 1},
                 {0, 1, 0, 0, 0}};

    int D[][] = new int[][]
                {{1, 1, 0, 0, 0, 0},
                 {0, 1, 1, 0, 0, 0},
                 {0, 0, 1, 0, 0, 0},
                 {0, 0, 1, 1, 1, 0},
                 {0, 0, 0, 1, 1, 1},
                 {0, 0, 1, 0, 1, 1}};

    int E[][] = new int[][]
                {{0, 0, 1, 0, 0, 1},
                 {0, 0, 1, 0, 0, 1},
                 {0, 0, 1, 1, 0, 1},
                 {0, 0, 0, 1, 1, 1},
                 {0, 0, 0, 1, 1, 1},
                 {1, 0, 0, 0, 1, 1}};

	BMat MA = new BMat(A);
	BMat MB = new BMat(B);
	BMat MC = new BMat(C);
	BMat MD = new BMat(D);
	BMat ME = new BMat(E);
    
// PART A
    System.out.println("\n part a:");
    System.out.println("((A OR B) AND C') AND B'");
    BMat temp1 = MA.join(MB);       // (A OR B)
    BMat compC = MC.complement();   // C'
    BMat temp2 = temp1.meet(compC);   // (A OR B) AND C'
    BMat compB = MB.complement();   // B'
    BMat partA = temp2.meet(compB); // ((A OR B) AND C') AND B'

    partA.show();
    System.out.println("\n");

// PART B
    System.out.println("Part b:");
    System.out.println("(B o B^T) AND (C OR C^T)");
    BMat transB = MB.transpose();        // B^T
    BMat transC = MC.transpose();        // C^T
    temp1 = MB.product(transB);          // (B o B^T)
    temp2 = MC.join(transC);             // (C OR C^T)
    BMat partB = temp1.meet(temp2);     
    partB.show();
    System.out.println("\n");


// PART C
    System.out.println("part c:");
    System.out.println("oC^17");
    BMat partC = MC;
    for(int temp = 1; temp < 17; temp++) {
        partC = partC.product(MC);
    }
    partC.show();
    System.out.println("\n");

// PART D
    System.out.println("part d:");
    System.out.println("(no of arrows in E) - (trace of E):");
    int arrowE = ME.arrows();  // arrows of E
    int traceE = ME.trace();   // trace of E
    int partD = arrowE - traceE;
    System.out.println(arrowE + " - " + traceE + " = " + partD);
    System.out.println("\n");

// PART E
    System.out.println("part e:");
    System.out.println("(D OR E)^T AND (D^T OR E^T)");
    temp1 = MD.join(ME);        // D or E
    temp1 = temp1.transpose();  // (D or E)^T
    BMat transD = MD.transpose();   // D^T
    BMat transE = ME.transpose();   // E^T;
    temp2 = transD.join(transE);
    BMat partE = temp1.meet(temp2);
    partE.show();
    System.out.println("\n");

// PART F
    System.out.println("part f:");
    System.out.println("oD^1 OR oD^2 OR ... oD^7");
    BMat partF = MD;
    int var = 0;
    for(int tempF = 1; tempF <= 7; tempF++) {
        // Reinitilize last every iteration
        BMat last = MD;
        // < 7 because first iteration is assumed in (BMat partF = MD)
        for(int tempF2 = 1; tempF2 < tempF; tempF2++) {
            last = last.product(MD);
        }
        if(tempF != 1){
            partF = partF.join(last);
        }
    }
    partF.show();
    System.out.println("\n");

// PART G
    System.out.println("part g:");
    System.out.println("maximum out-degree of all nodes in D");
    int out;
    int maxOut = 0;  // For the maximum out-degree
    for(int i=0; i<6; i++) {
        out = MD.outdegree(i+1);
        if(out > maxOut)
            maxOut = out;
    }
    System.out.println("Max out: " + maxOut);
    System.out.println("\n");

// PART H
    System.out.println("part h:");
    System.out.println("no of nodes in D having in-degree 2");
    int in;
    int nodesin = 0;
    for(int i=0; i<6; i++) {
        in = MD.indegree(i);
        if(in == 2)
            nodesin++;
    }
    System.out.println("Nodes: " + nodesin);
    System.out.println("\n");

  }

} // end class
