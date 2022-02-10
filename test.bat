ping -n 1 192.168.18.35 | find "TTL=" >nul 
if errorlevel 1 ( 
    curl -X GET -v -i "https://blynk.cloud/external/api/update?token=MuQHgY0EqIsPYjqcXRwrsj7uVHea6ptr&V2=0"
)
ping -n 1 192.168.18.20 | find "TTL=" >nul 
if errorlevel 1 ( 
    curl -X GET -v -i "https://blynk.cloud/external/api/update?token=MuQHgY0EqIsPYjqcXRwrsj7uVHea6ptr&V3=0"
)
