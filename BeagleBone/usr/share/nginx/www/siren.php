<?php

echo "<html>";
echo "<head>";
echo "<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">";
echo "<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">";
echo "</head>";
echo "<body>";
$count = intval($_GET["count"]);
for ($i = 1; $i <= $count; $i++) {
        echo $i;
        shell_exec("echo 1 > /sys/class/gpio/gpio60/value");
        sleep(1);
        shell_exec("echo 0 > /sys/class/gpio/gpio60/value");
        sleep(1);
}
echo "<p>Ran siren ###</p>";
echo "</h1>";
if ($_GET["redirect"] == "true") {
echo "<form id=\"myform\" name=\"myform\" action=\"printlog.php\" method=\"GET\">";
echo "</form>";
echo "<h1>Log cleared<h1/>";
echo "<script type=\"text/javascript\">";
echo "    window.onload=function(){";
echo "  document.forms['myform'].submit();";
echo "    }";
echo "</script>";
}
echo "</body>";
echo "</html>";


?>
