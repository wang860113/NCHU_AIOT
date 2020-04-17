<?php

$l=$_GET["l"];
$h=$_GET["h"];
$t=$_GET["t"];
/*AddData.php*/
//1 . connect to db
$mysqli = new mysqli("localhost","chung","0000","aiot");

// Check connection
if ($mysqli -> connect_errno) {
  echo "Failed to connect to MySQL: " . $mysqli -> connect_error;
  exit();
}

// 2. Perform query
if ($result = $mysqli -> query("insert into sensors (light,humi,temp) VALUES
   (".$l.",".$h.",".$t.")"));

$mysqli -> close();
?>
