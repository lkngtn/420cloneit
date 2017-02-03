<?php

	include("connect.php"); 	
	
	$link=Connection();

	$result=mysqli_query($link,"SELECT * FROM `tempLog` ORDER BY `timeStamp` DESC");
?>

<html>
   <head>
      <title>Sensor Data</title>
   </head>
<body>
   <h1>Temperature / moisture sensor readings</h1>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Timestamp&nbsp;</td>
			<td>&nbsp;Temperature 1&nbsp;</td>
			<td>&nbsp;Moisture 1&nbsp;</td>
			<td>&nbsp;Heat&nbsp;</td>
                        <td>&nbsp;Light&nbsp;</td>
                        <td>&nbsp;Humidifier&nbsp;</td>
                        <td>&nbsp;Fans&nbsp;</td>
		</tr>

      <?php 
		  if($result!==FALSE){
		     while($row = mysqli_fetch_array($result)) {
		        printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           $row["timeStamp"], $row["temperature"], $row["humidity"], $row["heat"], $row["light"],$row["humidifier"], $row["fans"]);
		     }
		     mysqli_free_result($result);
		     mysqli_close($link);
		  }
      ?>

   </table>
</body>
</html>