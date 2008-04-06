// Josh Braegger
// CS1400
// Creates a grocery list

class GroceryList {

	GroceryItemOrder[] groceries; // A list of groceries
	int groceries_index; // Used to keep track of how many groceries there are.

	// Constructor
	public GroceryList() {
		groceries = new GroceryItemOrder[10];
		groceries_index = 0;
	}

	// Add a GroceryItemOrder to the List
	public void add(GroceryItemOrder item) {
		this.groceries[groceries_index] = item;
		groceries_index++;
	}

	// Gets total cost of all groceries in the cart
	public double getTotalCost() {
		double totalCost = 0;
		for (int i = 0; i < this.groceries_index; i++) {
			totalCost += this.groceries[i].getCost();
		}
		return totalCost;
	}

}

class GroceryItemOrder {
	String name;         // The name of the grocery item
	int quantity;        // How many they purchased
	double pricePerUnit; // The price for each item

	// Constructor
	public GroceryItemOrder(String name, int quantity, double pricePerUnit) {
		this.quantity = quantity;
		this.name = name;
		this.pricePerUnit = pricePerUnit;
	}

	// Gets the cost of the grocery item order
	public double getCost() {
		return this.quantity * this.pricePerUnit;
	}

	// Sets/changes the quantity
	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}

}

// Tests the newly created classes
public class Chapter_8 {
	public static void main(String args[]) {
		System.out.println("Creating GroceryList");
		GroceryList g = new GroceryList();

		System.out.println("Creating new GroceryItemOrder");
		GroceryItemOrder go = new GroceryItemOrder("beans", 2, 3.75);

		System.out.println("Changing the quantity to 3");
		go.setQuantity( 3 );

		System.out.println("The total cost should be 11.25.  It is actually: "
				+ go.getCost() );

		System.out.println("Adding GroceryItemOrder to GroceryList");
		g.add( go );

		System.out.println("Create another GroceryItemOrder and adding it");
		GroceryItemOrder go2 = new GroceryItemOrder("peas", 4, 2.30);
		g.add( go2 );

		System.out.println("The total cost of groceries should be 20.45.  It "
				+ "is actually: " + g.getTotalCost() );

	}
}
