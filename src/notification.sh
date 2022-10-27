#!/bin/bash
TELEGRAM_BOT_TOKEN=5628882310:AAEP9a9Zf1rysUCPbbioywCktK5euYqer3U
TELEGRAM_USER_ID=818545637
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Ты просто чудо!%0A Project:+$CI_PROJECT_NAME%0A$CI_JOB_NAME+$CI_JOB_STATUS"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
