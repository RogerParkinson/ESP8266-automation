<?php

$types = array("event" => "0", "battery" => "1", "mailbox" => "2", "driveway" => "3", "gate" => "4");
$sources = array("test" => "123","pond" => "16058556","backdoor" => "8442031", "mailbox" => "8425573");

echo "<html>";
echo "<head>";
echo "<META HTTP-EQUIV=\"CACHE-CONTROL\" CONTENT=\"NO-CACHE\">";
echo "<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">";
echo "<link rel=\"stylesheet\" href=\"style.css\">";
echo "</head>". PHP_EOL;
echo "<body>". PHP_EOL;
$csvFile = fopen("/home/receiver/log.csv", "r");
$data = [];

echo "<h1>Log</h1>". PHP_EOL;
echo "<div class=\"table\">";
while(!feof($csvFile)) {
        $line =fgetcsv($csvFile,1024);
        if ($line[0] != "") {
        echo "<div class=\"tr\">";
                echo "<div class=\"td\">";
                $n = array_search($line[0],$sources);
                if ($n == "") {
                        echo $line[0];
                } else {
                        echo $n;
                }
                echo "</div>";
                echo "<div class=\"td\">";
                $d = intval($line[1]);
                $date = new DateTime();
                $date->setTimestamp($d);
                echo $date->format("Y-M-d H:i:s");
                echo "</div>";
                echo "<div class=\"td\">";
                echo array_search($line[2],$types);
                echo "</div>";
                if ($line[2] == "6") {
                        if ($line[3] < "3000") {
                                echo "<div class=\"tdc\">";
                        } else {
                                echo "<div class=\"td\">";
                        }
                        echo $line[3];
                        echo "</div>";
                }
                if ($line[2] > "1") {
                        // siren
                }
        echo "</div>". PHP_EOL;
        }
   }
echo "</div>". PHP_EOL;
echo "<div class=\"buttons\">";
echo "<a class=\"button\" href=\"printlog.php\">Refresh</a>";
echo "<a class=\"button\" href=\"killlog.php\">Clear</a>";
echo "</div>". PHP_EOL;
echo "</body>";
echo "</html>";


?>

