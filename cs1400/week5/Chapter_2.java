public class Chapter_2 {
	public static final int SUB_HEIGHT = 5;

	public static void main(String[] args) {
		drawLine();

		drawTop();
		drawBottom();

		drawLine();

		drawBottom();
		drawTop();

		drawLine();
	}

	public static void drawLine() {
		System.out.print("+");
		for (int i = 0; i <= (2 * SUB_HEIGHT); i++) {
			System.out.print("-");
		}
		System.out.println("+");
	}

	public static void drawSpaces(int spaces) {
		for (int i = 1; i <= spaces; i++) {
			System.out.print(" ");
		}

	}

	public static void drawBottom() {
		for(int line = 1; line < SUB_HEIGHT; line++) {
			System.out.print("|");

			int thingees = SUB_HEIGHT - line - 1;
			int spaces = line + 1;

			drawSpaces(spaces);

			for (int i = 1; i <= thingees; i++) {
				System.out.print("\\");
			}

			System.out.print("*");

			for (int i = 1; i <= thingees; i++) {
				System.out.print("/");
			}

			drawSpaces(spaces);

			System.out.println("|");
		}
		
	}

	public static void drawTop() {
		for(int line = 1; line < SUB_HEIGHT; line++) {
			System.out.print("|");

			int spaces = SUB_HEIGHT - line + 1;
			int thingees = line - 1;

			drawSpaces(spaces);
			for (int i = 1; i <= thingees; i++) {
				System.out.print("/");
			}

			System.out.print("*");

			for (int i = 1; i <= thingees; i++) {
				System.out.print("\\");
			}

			drawSpaces(spaces);

			System.out.println("|");
		}
		
	}

}
