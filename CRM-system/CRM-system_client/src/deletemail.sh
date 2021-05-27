#!/bin/bash

> mail.txt

echo "From: \"CRM system HSE\" <crmsystemhse@gmail.com>" >> mail.txt
echo "To: \"$1\" <$2>" >> mail.txt
echo "Subject: Registration in CRM system HSE

Hi $1,
your account in the High CRM was successfully deleted!

Anna, Denis and Arkady
" >> mail.txt
curl --ssl-reqd \
  --url 'smtps://smtp.gmail.com:465' \
  --user 'crmsystemhse@gmail.com:BshXXq4w4s2Vp2S' \
  --mail-from 'crmsystemhse@gmail.com' \
  --mail-rcpt $2 \
  --upload-file mail.txt

> mail.txt
