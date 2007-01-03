//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #4
//                  Mr. Rague
//                  Due: 9/26/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This java application creates a function to add the capability to
//  find and replace.
//  -----------------------------------------------------------------
  
public class ReplaceTest {

	public static void main( String args[] ) {

		String s = "public static void main -- public test";
		String r = ReplaceString(s, "public", "private");

		System.out.println("Beginning String: " + s);
		System.out.println("Ending String:    " + r);

	}

	public static String ReplaceString(String strInput, 
									 String searchStr,
									 String replaceStr) {

		// This is too easy, don't think it's what you want
		//return strInput.replaceAll(searchStr,replaceStr);
		
		StringBuffer result = new StringBuffer();

		int start = 0;
		int end = 0;
		// Keep looping until we reach the last item found
		while(( end = strInput.indexOf(searchStr, start)) >= 0) {
			// Append the part of strInput BEFORE the replaceStr
			result.append( strInput.substring( start, end ) );
			// Append the replace string
			result.append( replaceStr );
			// Set our start to the last place we left off
			start = end + searchStr.length();
		}

		// Append the rest of the string
		result.append( strInput.substring(start) );
		return result.toString();
	}
}
