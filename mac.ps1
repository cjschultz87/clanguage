$mac = ""

$charArray = "0123456789abcdef"
$charArray_prime = "26ae"

$index = 0

while ($index -lt 12)
{
	if ($index -ne 1)
	{
		$m_i = get-random -maximum 12
		$mac += $charArray[$m_i]
	}
	else
	{
		$m_i = get-random -maximum 4
		$mac += $charArray_prime[$m_i]
	}
	
	$index += 1
}

echo "mac = $mac"

<# replace id and index with appropriate values found with regedit that correspond to the interface.#>

set-itemproperty -path "HKLM:\SYSTEM\CurrentControlSet\Control\Class\{id}\index" -name NetworkAddress -value $mac

$device = read-host -prompt "device"

get-pnpdevice -friendlyname "*$device*" | disable-pnpdevice -confirm:$false

$bravo = $true

try{
	get-pnpdevice -friendlyname "*$device*" -status OK -erroraction stop
}
catch
{
	$bravo = $false
	echo "status disabled"
}

if ($bravo -eq $true){echo "did not disable device"}

$bravo = $true

get-pnpdevice -friendlyname "*$device*" | enable-pnpdevice -confirm:$false

try{
	get-pnpdevice -friendlyname "*$device*" -status OK
}
catch
{
	$bravo = $false
	echo "status disabled"
}

if ($bravo -eq $true){echo "device enabled"}

get-netadapter | select-object name,macaddress