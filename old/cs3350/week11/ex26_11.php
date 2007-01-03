<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
	"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<?php
	function validateEmail($email) {
		if ( ereg("^[a-zA-Z0-9_\.]+@[a-zA-Z0-9]+\.[a-zA-Z0-9\.]+$", $email) )
			return $email . " is a valid email<br />";
		else
			return $email . " is not a valid email<br />";
		return;
	}
	
	if( $_POST['email'] ) {
		$returnText = validateEmail( $_POST['email'] );
	}
?>


<html xmlns = "http://www.w3.org/1999/xhtml">
	<head>
		<title>PHP Email Validation
		</title>

	</head>
	<body>
	
<?php


		$inString = "aljk@alkj.com";
		


		/*echo validateEmail("aljk@alkj.com");
		echo validateEmail("billgates@msn.com");
		echo validateEmail("billgatesmsn.com");
		echo validateEmail("billgate@smsncom");
		echo validateEmail("billg123ate@smsn11.com");
		echo validateEmail("billg123ate@smsn11.net");
		echo validateEmail("billg123ate@smsn11.uk");
		echo validateEmail("billg123ate@.uk");*/
		
?>

	<form name="theform" method="post" action="ex26_11.php">
		Email to validate: <input type="text" name="email" />
		
		<input type="button" value="Submit" onclick="document.theform.submit();" />
	</form>

<?
	echo $returnText;
?>

	</body>
</html>