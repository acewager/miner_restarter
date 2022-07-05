ping -n 1 192.168.18.35 | find "TTL=" >nul 
if errorlevel 1 ( 
    curl -X GET -v -i "https://blynk.cloud/external/api/update?token="
)
ping -n 1 192.168.18.20 | find "TTL=" >nul 
if errorlevel 1 ( 
    curl -X GET -v -i "https://blynk.cloud/external/api/update?token="
)
