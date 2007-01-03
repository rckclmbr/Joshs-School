//                  Joshua Braegger
//                  CS 3230 - T H 7:30PM
//                  Assignment #12
//                  Mr. Rague
//                  Due: 12/08/2006
//                  Version: 1.0
//  -----------------------------------------------------------------
//  This is the server side of the java client-server application.
//  -----------------------------------------------------------------
import java.net.*;
import java.io.*;
import java.util.*;

public class ServerTest {

	ServerSocket ss;
	
	public static void main (String args[]) throws IOException  {
		ServerTest st = new ServerTest();
		st.listen();
	}
	
	public void listen() throws IOException {
		Socket response;
		ss = new ServerSocket(6000, 5);
		System.out.println("Listening...");
		// Run until terminated at console
		while(true)
		{
			response = ss.accept();
			InputStream in = response.getInputStream();
			OutputStream os = response.getOutputStream();
						
			BufferedReader buf = new BufferedReader(new InputStreamReader(in));
			String inString = buf.readLine();
			System.out.println("Received: " + inString);

			if(inString == null) inString = "";

			StringBuffer sb = new StringBuffer(inString);
			String outString = sb.reverse().toString();
	
			BufferedWriter bufWrite = new BufferedWriter(new OutputStreamWriter(os));
			System.out.println("Sending: " + outString);
			bufWrite.write(outString + "\n");
			bufWrite.flush();
		}
		// We don't need to close because it will run until the program is terminated (and it will close then)
		
	}
}