<?php

echo "<html>";
echo "<head>";
echo "<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">";
echo "<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">";
echo "</head>";
echo "<body>";
$date = new DateTime();
$file = fopen("/home/receiver/log.txt","a+");
fwrite($file,"Battery low for device ".$_GET["name"]." ". $date->format("D M d H:i:s Y")." battery: ".$_GET["battery"]. PHP_EOL );
fclose($file);
echo "</body>";
echo "</html>";


?>

