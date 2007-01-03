import java.io.*;
public class MyClass implements java.io.Serializable {
		double x,y;
		String s;
 		public MyClass() {
			this.x = 0;
			this.y = 0;
			this.s = "";
 		}
		
		public MyClass(double x, double y, String s)  {
			this.x = x;
			this.y = y;
			this.s = s;
		}
		
		public static void main(String[] args) {
			FileOutputStream fo;
			FileInputStream fi;
			
			try {
				fo = new FileOutputStream(new File("myFile.ser"));
				MyClass myObj = new MyClass(2.4,4.5,"I am serializable!");
				System.out.println("Original Object:");		
				myObj.printObject();
				ObjectOutputStream oos = new ObjectOutputStream(fo);
				oos.writeObject(myObj);
				fo.close();
				fi = new FileInputStream("myFile.ser");
				MyClass myNewObj;
				ObjectInputStream ois = new ObjectInputStream(fi);
				myNewObj = (MyClass)ois.readObject();
				System.out.println();		
				System.out.println("New Object:");		
				myNewObj.printObject();
			}
			catch(IOException e) { System.out.println("There was an error reading/writing the file"); }
			catch(ClassNotFoundException e) { System.out.println("There isn't that class"); }
		}
		
		public void printObject() {
			System.out.println("x: " + this.x);
			System.out.println("y: " + this.y);
			System.out.println("s: " + this.s);
		}
		private void writeObject(ObjectOutputStream o) throws IOException {
			// out goes here
			o.writeDouble((double)(x + y));
			o.defaultWriteObject();
		}
		
		private void readObject(ObjectInputStream i) throws IOException, ClassNotFoundException {
				double checksum = i.readDouble();
				i.defaultReadObject();
			
				// Check the checksum
				if( this.x + this.y == checksum )
					System.out.println("Checksum ok!");
				else
					System.out.println("Checksum bad");
		}

}