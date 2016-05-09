<?php

echo "<html>";
echo "<head>";
echo "<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">";
echo "<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">";
echo "</head>";
echo "<body>";
echo "submitting event...";
$sources = array("test" => "123","pond" => "16058556","backdoor" => "8442031", "mailbox" => "8425573");
$source = array_search($_GET["name"],$sources);
if ($source == "mailbox") {
	// Chime once for mailbox
        shell_exec("echo 1 > /sys/class/gpio/gpio60/value");
        sleep(1);
        shell_exec("echo 0 > /sys/class/gpio/gpio60/value");
        sleep(1);
}
if ($source == "gate") {
	// chime twice for gate
        shell_exec("echo 1 > /sys/class/gpio/gpio60/value");
        sleep(1);
        shell_exec("echo 0 > /sys/class/gpio/gpio60/value");
        sleep(1);

        shell_exec("echo 1 > /sys/class/gpio/gpio60/value");
        sleep(1);
        shell_exec("echo 0 > /sys/class/gpio/gpio60/value");
        sleep(1);
}

$csvfile = fopen("/home/receiver/log.csv","a+");
fwrite($csvfile,$_GET["name"].",". time().",".$_GET["type"].",".$_GET["battery"].PHP_EOL);
fclose($csvfile);
echo "success";
echo "</body>";
echo "</html>";


?>

