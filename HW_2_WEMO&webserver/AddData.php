
<?php

$l=$_GET["light"];
$h=$_GET["humi"];
$t=$_GET["temp"];
/*AddData.php*/
//1 . connect to db
$mysqli = new mysqli("localhost","root","0000","aiotdb");

// Check connection
if ($mysqli -> connect_errno) {
  echo "Failed to connect to MySQL: " . $mysqli -> connect_error;
  exit();
}

// 2. Perform query
if ($result = $mysqli -> query("insert into sensors (light,humi,temp) VALUES
   (".$light.",".$humi.",".$temp.")"));

$mysqli -> close();
?>
