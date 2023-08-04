#!/bin/dash

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors
. ~/.config/dwm-config/bar-files/tokyonight 

pkg_updates() {
  #updates=$({ timeout 20 doas xbps-install -un 2>/dev/null || true; } | wc -l) # void
  updates=$({ timeout 20 checkupdates 2>/dev/null || true; } | wc -l) # arch
  # updates=$({ timeout 20 aptitude search '~U' 2>/dev/null || true; } | wc -l)  # apt (ubuntu, debian etc)

  if [ -z "$updates" ]; then
    printf "  ^c$green^    Fully Updated"
  else
    printf "  ^c$green^    $updates"" updates"
  fi
}
#add => cuz it messes up round numbers and look into gruvbox colors
battery() {
  get_capacity="$(cat /sys/class/power_supply/BAT1/capacity)"
  if [ $get_capacity -le 100 ] && [ $get_capacity -ge 90 ]
   then
   printf "^b$black^ ^c$dggreen^ 󰁹 $get_capacity"
  elif [ $get_capacity -le 90 ] && [ $get_capacity -ge 80 ]
   then
   printf "^b$black^ ^c$gaqua^ 󰂂 $get_capacity"
  elif [ $get_capacity -le 80 ] && [ $get_capacity -ge 70 ]
   then
   printf "^b$black^ ^c$green^ 󰂁 $get_capacity"
  elif [ $get_capacity -le 70 ] && [ $get_capacity -ge 60 ]
   then
   printf "^b$black^ ^c$lggreen^ 󰂀 $get_capacity"
  elif [ $get_capacity -le 60 ] && [ $get_capacity -ge 50 ]
   then
   printf "^b$black^ ^c$yellow^ 󰁿 $get_capacity"
  elif [ $get_capacity -le 50 ] && [ $get_capacity -ge 40 ]
   then
   printf "^b$black^ ^c$gyellow^ 󰁾 $get_capacity"
  elif [ $get_capacity -le 40 ] && [ $get_capacity -ge 30 ]
   then
   printf "^b$black^ ^c$lgorange^ 󰁽 $get_capacity"
  elif [ $get_capacity -le 30 ] && [ $get_capacity -ge 20 ]
   then
   printf "^b$black^ ^c$dgorange^ 󰁼 $get_capacity"
  elif [ $get_capacity -le 20 ] && [ $get_capacity -ge 10 ]
   then
   printf "^b$black^ ^c$red^ 󰁻 $get_capacity"
  elif [ $get_capacity -le 10 ]
   then
   printf "^b$black^ ^c$gred^ 󰁺 $get_capacity"
fi
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$terminalb^^b$blue^ 󰖩 ^d^%s" "^c$blue^^b$terminalb^ Connected " ;;
	down) printf "^c$terminalb^^b$red^ 󰖪 ^d^%s" "^c$red^^b$terminalb^ Disconnected " ;;
	esac
}
#like wlan but make a module for charging and make it only show when smth is charging
clock() {
	printf "^c$black^^b$darkblue^ 󱑆"
	printf "^c$black^^b$blue^ $(date '+%H:%M')"
	printf "^c$black^^b$darkblue^ 󰨲"
	printf "^c$black^^b$blue^ $(date "+%A, %B %d %Y")"
	printf "     "
}

audio() {
	printf "^c$yellow^ 󰋋"
	printf "^c$yellow^ $(amixer sget Master | awk -F"[][]" '/Left:/ { print $2 }')"
}

charge() {
get_charge="$(cat /sys/class/power_supply/BAT1/status)"
 if [ "$get_charge" = Charging ]
 then
	 printf "^c$terminalb^^b$green^  " 
   printf "^c$green^^b$terminalb^ Charging "
fi
}

while true; do

  [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
  interval=$((interval + 1))

  sleep 1 && xsetroot -name "$(battery)% $(audio)% $(wlan)$(charge)$(clock)"
done
