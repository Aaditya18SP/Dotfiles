#!/bin/bash

declare -i battery_percent=$(($( cat /sys/class/power_supply/BAT0/uevent | grep -m 1 POWER_SUPPLY_ENERGY_NOW= | grep -o '[0-9]\+')*100/$( cat /sys/class/power_supply/BAT0/uevent | grep -m 1 POWER_SUPPLY_ENERGY_FULL | grep -o '[0-9]\+')))

battery_percent=29
if [[ battery_percent -le 30 ]];then
    $(notify-send "Low Battery. Please plug in");
else echo "No need to plug in.";
fi
