Write-Output "Copying JHP_Links.apx to Archicad 24 Add-On location..."
$BuildLocation = "${PSScriptRoot}\..\Build\x64\Release\JHP_Links.apx"
$Destination = "C:\Program Files\GRAPHISOFT\ARCHICAD 24\Add-Ons\JHP\JHP_Links.apx"

Copy-Item -path $BuildLocation -Destination $Destination -Force

