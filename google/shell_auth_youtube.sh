#!/bin/sh

MY_EMAIL=lkj@sdf.fr
MY_PASSWORD="123456"

AUTH=$(curl --silent https://www.google.com/accounts/ClientLogin --data-urlencode Email="$MY_EMAIL" --data-urlencode Passwd="$MY_PASSWORD" -d accountType=GOOGLE -d source=Google-cURL-Example -d service=youtube | grep Auth)

XML=$(curl --silent --header "Authorization: GoogleLogin $AUTH" "https://gdata.youtube.com/feeds/api/users/m42am/uploads?orderby=updated&max-results=50")

echo "$XML" | tidy -xml -indent -quiet 2>/dev/null
