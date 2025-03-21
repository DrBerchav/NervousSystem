<?php
function setcputemp(&$Memory)
{
$hf=popen("sensors | grep '°C' | awk -f /home/adminbrad/bin/temp.awk","r");
$heat=fread($hf,4096);
fclose($hf);
echo "CPU Temp is $heat\n";
$Memory["cputemp"]=$heat;
shell_exec("/home/adminbrad/bin/heat_check");
}

function slowspeed(&$Memory)
{
$Memory["speed"]++;
$speed=$Memory["speed"];
echo "Slowing Speed to: $speed!\n";
setcputemp($Memory);
}
function morespeed()
{
$Memory["speed"]--;
$speed=$Memory["speed"];
echo "Increasong Speed to: $speed!\n";
setcputemp($Memory);

}
?>
