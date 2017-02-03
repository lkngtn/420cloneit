<?php
   	include("connect.php");
   	
   	$link=Connection();

	if (isset($_POST['temp1'])){
		$temp1=$_POST["temp1"];
	}
	if (isset($_POST['hum1'])){
		$hum1=$_POST["hum1"];
	}

        if (isset($_POST['heat'])){
                $heat=$_POST["heat"];
        }

	if (isset($_POST['light'])){
                $light=$_POST["light"];
        }

	if (isset($_POST['humidifier'])){
                $humidifier=$_POST["humidifier"];
        }

	if (isset($_POST['fans'])){
                $fans=$_POST["fans"];
        }

	$query = "INSERT INTO tempLog (temperature, humidity, heat, light, humidifier, fans) 
		VALUES (".$temp1.",".$hum1.",".$heat.",".$light.",".$humidifier.",".$fans.")"; 
   	
   	mysqli_query($link,$query);
	mysqli_close($link);

   	//header("Location: index.php");
?>
