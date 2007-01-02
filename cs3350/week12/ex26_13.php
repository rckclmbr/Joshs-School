
<?php
	extract($_POST);

	$connection = mysql_connect("localhost","W00209669","password") or die(mysql_error());
	mysql_select_db("W00209669");
		
	if($url) {
		$url = mysql_real_escape_string($url);
		$desc = mysql_real_escape_string($desc);
		$query = "INSERT INTO Urltable (URL, Description) VALUES ('$url','$desc')";
		mysql_query($query) or die(mysql_error());
	}
		
	$query = "SELECT URL, Description FROM Urltable";
	
	$results = mysql_query($query) or die(mysql_error());	
	mysql_close();
	
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Database</title>
</head>

<body>

<table width="500" border="1" cellpadding="0" cellspacing="2">
<tr>
	<td>URL</td>
	<td>Description</td>
</tr>
<?

	for($i = 0; $i < mysql_numrows($results); $i++) {
		echo "<tr><td>";
		echo mysql_result($results,$i,"URL");
		echo "</td><td>";
		echo mysql_result($results,$i,"Description");
		echo "</td></tr>";	
	}
?>
</table>
<a  href="ex26_13.html">Back</a>

</body>
</html>