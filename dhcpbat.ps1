try
{
	$gateway = $(ipconfig | select-string "Default Gateway")[0].tostring()
}
catch
{
	$gateway = ""
}

$index = $gateway.IndexOf(":") + 2

if (($index -lt 0) -or ($index -ge $gateway.length)){echo "no gateway"; exit}

$gateway = $gateway.substring($index,$gateway.length - $index)

echo "gateway = $gateway"

try
{
	$server = $(ipconfig | select-string "DHCP Server")[0].tostring()
}
catch
{
	$server = ""
}

if ($server.length -eq 0){$server = $gateway}
else {$index = $server.IndexOf(":") + 2; if (($index -lt 0) -or ($index -ge $server.ength)){echo "no server";exit}; $server = $server.substring($index,$server.length - $index)[0]}

echo "server = $server"

try
{
	$client = $(ipconfig | select-string "IPv4 Address")[0].tostring()
}
catch
{
	$client = ""
}

if ($client.length -eq 0){echo "no client address"; exit}

$index = $client.IndexOf(":") + 2

if (($index -lt 0) -or ($index -ge $client.length)){echo "no client";exit}

$client = $client.substring($index,$client.length - $index)

echo "client = $client"

try
{
	$mask = $(ipconfig | select-string "Subnet Mask")[0].tostring()
}
catch
{
	$mask = ""
}

if ($mask.length -eq 0){echo "no subnet mask"; exit} else {$index = $mask.IndexOf( 	":") + 2; $mask = $mask.substring($index,$mask.length - $index)}

$maskArray = @()
$index = 0
$index_up = 0
while ($index_up -ge 0){$index_up = $mask.substring($index,$mask.length - $index).IndexOf("."); if ($index_up -ge 0){$mask_sub = $mask.substring($index,$index_up)}else{$mask_sub = $mask.substring($index,$mask.length - $index)}; $maskArray += $([int]$mask_sub -bxor 255) -band $(get-random -minimum 2 -maximum 254); $index += $index_up + 1}

$gatewayIndex = 0

$index = 0
$index_up = 0
while ($index_up -ge 0){$index_up = $gateway.substring($index,$gateway.length - $index).Indexof("."); if ($index_up -ge 0){$gateway_sub = $gateway.substring($index,$index_up)} else {$gateway_sub = $gateway.substring($index,$gateway.length - $index)}; $maskArray[$gatewayIndex] = $maskArray[$gatewayIndex] -bxor [int]$gateway_sub; $gatewayIndex += 1; $index += $index_up + 1}


$request = $maskArray[0].ToString() + "." + $maskArray[1].ToString() + "." + $maskArray[2].ToString() + "." + $maskArray[3].ToString()


echo "request = $request"


$interface = $(read-host -prompt "interface")

$november = "$(get-netadapter | select-object name,macaddress | select-string $interface)"

$mike = "MacAddress="
$mac_prime = "xx-xx-xx-xx-xx-xx"

$mac = $november.substring($november.IndexOf($mike) + $mike.length, $mac_prime.length)

echo "mac = $mac"

$iota = $(netsh interface ipv4 show interface $interface)

$iota = "$(echo $iota | select-string ifindex)"

$index = $iota.indexof(":") + 2

$iota = $iota.substring($index,$iota.length - $index)


dhcp $server $gateway $mask $client $request $mac $iota

exit

$delta_prime = $($delta | select-string "socket error")

if ($delta_prime.length -gt 0){exit}

$delta_prime = $($delta | select-string "invalid socket")

if ($delta_prime.length -gt 0){exit}

$sierra = "new address: "

if ($delta.length -eq 0){echo "no new ipv4 address"; exit}

$newAddress = "$($delta | select-string `"$sierra`")"

$index = $newAddress.IndexOf($sierra) + $sierra.length

$newAddress = $newAddress.substring($index,$sierra.length - $index)

if ($newAddress -eq "0.0.0.0"){echo "ipv4 not acknowledged"; exit}

$index = 0
$mask_int = 0

while ($index -lt 4){$mask_int += $maskArray[$index] * [math]::pow(256,3-$index); $index += 1}

$mask_int = [convert]::tostring($mask_int,2)

$subnet = $mask_int.IndexOf("0") - 1

if ($newAddress -ne $request){echo "no ipv4 new assignment"; exit} else {new-netipaddress -interfacealias $interface -ipaddress $newAddress -prefixlength $subnet -defaultgateway $gateway}
