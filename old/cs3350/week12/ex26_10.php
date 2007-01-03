<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
   "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns = "http://www.w3.org/1999/xhtml">
   <head>
      <title>Form Validation</title>
   </head>

   <body style = "font-family: arial,sans-serif">

      <?php
         extract($_POST);

         // determine whether phone number is valid and print
         // an error message if not
         if ( !ereg( "^\([0-9]{3}\)[0-9]{3}-[0-9]{4}$",
            $phone ) ){

            print( "<p><span style = \"color: red; 
               font-size: 2em\">
               INVALID PHONE NUMBER:</span><br />
               A valid phone number must be in the form
               <strong>(555)555-5555</strong><br />
               <span style = \"color: blue\">  
               Click the Back button, enter a valid phone
               number and resubmit.<br /><br />
               Thank You.</span></p></body></html>" );

            die(); // terminate script execution
         }
		 
		 // write to the file
		 $writestr = "Name: " . $fname . " " . $lname . "\n";
		 $writestr .= "Book: " .$book . "\n";
		 $writestr .- "Email: " . $email . "\n";
		 $writestr .= "Phone: " . $phone . "\n";
		 $writestr .= "OS: " . $os . "\n\n";

		 $fstream = @fopen("userinput.txt","a+")  or die("can't open file");
		 fwrite($fstream,$writestr);
		 fclose($fstream);
		 
		 // now read the file
		 $istream = @fopen("userinput.txt","r") or die("can't open file");
		 $contents = fread($istream, filesize("userinput.txt"));
		 fclose($istream);
		 
		 // print the files inputs
		 print "Contents of file: <br />";
		 print ereg_replace("\n","<br />", $contents);
		 print "<br /><br />";
      ?>
   </body>
</html>
