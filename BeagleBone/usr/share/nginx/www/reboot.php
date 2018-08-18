<?php

echo "<html>";
echo "<head>";
echo "<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">";
echo "<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">";
echo "<link rel=\"stylesheet\" href=\"style.css\">";
echo "</head>";
echo "<body>";
exec('sudo /sbin/reboot');
echo "<form id=\"myform\" name=\"myform\" action=\"printlog.php\" method=\"GET\">";
echo "</form>";
echo "<h1>Rebooting...<h1/>";
echo "</body>";
echo "</html>";


?>
