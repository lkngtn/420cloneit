<?php

	function Connection(){
		$server="127.0.0.1";
		$user="420user";
		$pass="420blazeit";
		$db="420cloneit";
	   	
		$connection = mysqli_connect($server, $user, $pass, $db);

		if (!$connection) {
	    	die('MySQL ERROR: ' . mysql_error());
		}
		
		// mysqli_select_db($db) or die( 'MySQL ERROR: '. mysqli_error() );

		return $connection;
	}
?>
