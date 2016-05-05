<?php

echo "<html>";
echo "<head>";
echo "<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">";
echo "<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">";
echo "</head>";
echo "<body>";
echo "submitting event...";
if ($_GET["type"] > "1") {
	$count = intval($_GET["param"]);
	for ($i = 1; $i <= $count; $i++) {
		echo $i;
		shell_exec("echo 1 > /sys/class/gpio/gpio60/value");
		sleep(1);
		shell_exec("echo 0 > /sys/class/gpio/gpio60/value");
		sleep(1);
	}
}

$csvfile = fopen("/home/receiver/log.csv","a+");
fwrite($csvfile,$_GET["name"].",". time().",".$_GET["type"].",".$_GET["param"].PHP_EOL);
fclose($csvfile);
echo "success";
echo "</body>";
echo "</html>";


?>

