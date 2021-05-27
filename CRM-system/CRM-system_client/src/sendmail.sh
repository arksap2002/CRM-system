#!/bin/bash

> mail.txt

echo "From: \"High CRM\" <crmsystemhse@gmail.com>" >> mail.txt
echo "To: \"$1\" <$2>" >> mail.txt
echo "Subject: Registration in High CRM

Hi $1,
the registration in the High CRM was successful!

Anna, Denis and Arkady
" >> mail.txt
curl --ssl-reqd \
  --url 'smtps://smtp.gmail.com:465' \
  --user 'crmsystemhse@gmail.com:BshXXq4w4s2Vp2S' \
  --mail-from 'crmsystemhse@gmail.com' \
  --mail-rcpt $2 \
  --upload-file mail.txt

> mail.txt
