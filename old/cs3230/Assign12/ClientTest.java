//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #12
//                  Mr. Rague
//                  Due: 12/08/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This is the client side of the java client-server application.
//  -----------------------------------------------------------------
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class ClientTest {

	private Socket s;
	private BufferedWriter writer;
	private BufferedReader reader;
	
	public ClientTest() { }
	
	// This is the main constructor, it creates a socket, and sends then receives data
	public ClientTest(String sendString) {
		System.out.println("Sending: " + sendString);
		String getString = process(sendString);
		System.out.println("Received: " + getString);
	}
	
	// Sends the string you pass in arguments, returns the string you get back.
	public String process(String sendString) {
		String retString = null;
		try {
			this.s = new Socket("127.0.0.1", 6000);
			this.open();
			this.writeToServer(sendString);
			retString = this.readFromServer();
			this.close();
		}
		catch (Exception e) 
			{ System.out.println("Exception: " + e); }
		
		return retString;
	}

	// This gets out command-line input, or prompts for input, then creates a new class with that
	public static void main (String args[]) {
		String outS = "";
		
		if((args.length < 1)) {
			System.out.println("You didn't enter any arguments! Enter something now.");
			while(outS.length() == 0) {
				System.out.print(">> ");
				outS = (new Scanner(System.in)).nextLine();
			}
		} else {
			outS = StringUtils.join(args, ' ');
		}
		ClientTest myClient = new ClientTest(outS);
	}
	
	// This writes to the server
	public void writeToServer(String stringToWrite) throws IOException {
			writer.write(stringToWrite + "\n");
			writer.flush();
	}
	
	// This receives data from the server
	public String readFromServer( ) throws IOException {
			String inString = null;
			// Wait for the reply
			while(inString == null)
				inString = reader.readLine();
			return inString;	
	}
	
	// This opens the streams
	public void open() throws IOException {
		InputStream in = this.s.getInputStream();
		reader = new BufferedReader(new InputStreamReader(in));	
		OutputStream os = s.getOutputStream();
		writer = new BufferedWriter(new OutputStreamWriter(os));	
	}
	
	// This closes the streams
	public void close() throws IOException {
		writer.close();
		reader.close();
		s.close();
	}
}

class StringUtils {
	// I took this from org.apache.commons.lang.StringUtils (it's a pretty big file, I
	// didn't want to include the whole thing but I still wanted to use this.)
	// It does the opposite of split()
    public static String join(Object[] array, char separator) {
        if (array == null) {
            return null;
        }
        int arraySize = array.length;
        int bufSize = (arraySize == 0 ? 0 : ((array[0] == null ? 16 : array[0].toString().length()) + 1) * arraySize);
        StringBuffer buf = new StringBuffer(bufSize);

        for (int i = 0; i < arraySize; i++) {
            if (i > 0) {
                buf.append(separator);
            }
            if (array[i] != null) {
                buf.append(array[i]);
            }
        }
        return buf.toString();
    }
}