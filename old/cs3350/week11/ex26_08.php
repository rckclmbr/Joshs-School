<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
	"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns = "http://www.w3.org/1999/xhtml">
	<head>
		<title>PHP String Searching
		</title>

	</head>
	<body>
<?php

	$states = "Mississippi Alabama Texas Massachusetts Kansas";
	
	ereg("[[:<:]]([a-zA-Z]*xas)[[:>:]]",$states , $statesArray[0]);
	eregi("[[:<:]](k[a-zA-Z]*s)[[:>:]]",$states , $statesArray[1]);
	ereg("[[:<:]](M[a-zA-Z]*s)[[:>:]]",$states , $statesArray[2]);
	ereg("[[:<:]]([a-zA-Z]*a)[[:>:]]",$states , $statesArray[3]);
	ereg("[[:<:]](M[a-zA-Z]*)[[:>:]]",$states , $statesArray[4]);
	
	for($i = 0; $i < count($statesArray); $i++) {
		print("statesArray[" . $i . "] - " . $statesArray[ $i ][1] . "<br />");
	}
	
?>
	</body>
</html>