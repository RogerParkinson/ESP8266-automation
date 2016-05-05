<?php

echo "<html>";
echo "<head>";
echo "<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">";
echo "<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">";
echo "<link rel=\"stylesheet\" href=\"style.css\">";
echo "</head>";
echo "<body>";
$r = unlink("/home/receiver/log.csv");
$file = fopen("/home/receiver/log.csv", "w+");
fclose($file);
echo "<form id=\"myform\" name=\"myform\" action=\"printlog.php\" method=\"GET\">";
//echo "<input type=\"submit\" value=\"submit\" name=\"mem_type\" border=\"0\">";
echo "</form>";
echo "<h1>Log cleared<h1/>";
echo "<script type=\"text/javascript\">";
echo "    window.onload=function(){";
echo "  document.forms['myform'].submit();";
echo "    }";
echo "</script>";
echo "</body>";
echo "</html>";


?>
