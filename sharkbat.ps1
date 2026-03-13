$mac = read-host -prompt "mac"

while ($true)
{	
	$tango = $(tshark -i "wi-fi" -c 10 -Y "dhcp" -Y "eth.src == $mac" -Y "ip.src == 0.0.0.0" -T fields -e eth.src -e ip.src 2>null)
	
	$bravo = $true
	
	if (($tango -like "*$mac*") -and ($bravo -eq $true))
	{
		$iota_0 = "$(ipconfig | select-string ipv4)"
		
		echo "requesting new ipv4 address"
		
		echo "wi-fi" | powershell -executionpolicy bypass dhcpbat
		
		$iota_1 = "$(ipconfig | select-string ipv4)"
		
		if ($iota_0 -ne $iota_1)
		{
			$bravo = $false
		}
	}

}