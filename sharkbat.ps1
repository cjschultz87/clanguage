$mac = read-host -prompt "mac"

while ($true)
{	
	<#
	$tango = $(tshark -i "wi-fi" -c 10 -Y "dhcp" -Y "eth.src == $mac" -Y "ip.src == 0.0.0.0" -T fields -e eth.src -e ip.src 2>null)
	#>
	
	tshark -l -i wi-fi -Y dhcp -Y "eth.src == $mac" -Y "ip.src == 0.0.0.0" -T fields -e eth.src -e ip.src 2>null | select-object -first 1 | tee -variable tango
	
	$bravo = $true
	
	while (($tango -like "*$mac*") -and ($bravo -eq $true))
	{
		echo "$(get-date) requesting new ipv4 address"
		
		echo "wi-fi" | powershell -executionpolicy bypass dhcpbat | tee-object -variable delta
		
		if ($delta -like "*new address*")
		{
			$bravo = $false
		}
	}

}
