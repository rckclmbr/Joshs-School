//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #5
//                  Mr. Rague
//                  Due: 10/10/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  The person class is the base class for SalesPerson, Manager,
//  and Executive.  Shows deleting and adding objects, and counting
//  how many is currently in
//  -----------------------------------------------------------------

class Person {
	
	private static int numObjects = 0;
	private int age;
	private String name;

	Person() {
		numObjects++;
	}

	protected void destroy() {
		numObjects--;
	}

	public void setAge(int age) {
		this.age = age;
	}
	public int getAge() {
		return this.age;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getName() {
		return this.name;
	}
	
	public void show() {
		System.out.println("Age: " + this.age);
		System.out.println("Name: " + this.name);
		System.out.println("Objects: " + numObjects);
	}
}


//  -----------------------------------------------------------------
//  The SalesPerson class extends the Person class.  It simply
//  increments how many Salespeople there are, and has a district
//  too.
//  -----------------------------------------------------------------
class SalesPerson extends Person {
	
	private static int salesObjs = 0;
	private String district;

	SalesPerson(String name, int age, String district) {
		salesObjs++;
		this.district = district;
		this.setName(name);
		this.setAge(age);
	}
	public void destroy() {
		super.destroy();
		salesObjs--;
	}

	public void show() {
		System.out.println("SalesPerson");
		super.show();
		System.out.println("District: " + this.district);
		System.out.println("SalesPeople: " + salesObjs);
	}
}

//  -----------------------------------------------------------------
//  The Manager class extends the Person class.  It simply
//  increments how many Managers there are, and has a department
//  too.
//  -----------------------------------------------------------------

class Manager extends Person {	
	private static int managerObjs = 0;
	private String dept;

	Manager(String name, int age, String dept) {
		managerObjs++;
		this.dept = dept;
		this.setName(name);
		this.setAge(age);
	}

	public void destroy() {
		managerObjs--;
	}

	public void show() {
		System.out.println("Manager");
		super.show();
		System.out.println("Department: " + this.dept);
		System.out.println("Managers: " + managerObjs);
	}
}

//  -----------------------------------------------------------------
//  The Executive class extends the Person class.  It simply
//  increments how many Executives there are.
//  -----------------------------------------------------------------

class Executive extends Person {	
	private static int execObjs = 0;

	Executive(String name, int age) {
		execObjs++;
		this.setName(name);
		this.setAge(age);
	}

	public void destroy() {
		execObjs--;
	}

	public void show() {
		System.out.println("Executive");
		super.show();
		System.out.println("Executives: " + execObjs);
	}
}
