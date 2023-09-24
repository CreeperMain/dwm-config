#!/bin/dash

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors
. ~/.config/dwm-config/bar-files/tokyo-night 

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
   echo "^b$black2^^c$dggreen^ 󰁹 $get_capacity%  "
  elif [ $get_capacity -le 90 ] && [ $get_capacity -ge 80 ]
   then
   echo "^b$black2^^c$gaqua^ 󰂂 $get_capacity%  "
  elif [ $get_capacity -le 80 ] && [ $get_capacity -ge 70 ]
   then
   echo "^b$black2^^c$green^ 󰂁 $get_capacity%  "
  elif [ $get_capacity -le 70 ] && [ $get_capacity -ge 60 ]
   then
   echo "^b$black2^^c$lggreen^ 󰂀 $get_capacity%  "
  elif [ $get_capacity -le 60 ] && [ $get_capacity -ge 50 ]
   then
   echo "^b$black2^^c$yellow^ 󰁿 $get_capacity%  "
  elif [ $get_capacity -le 50 ] && [ $get_capacity -ge 40 ]
   then
   echo "^b$black2^^c$gyellow^ 󰁾 $get_capacity%  "
  elif [ $get_capacity -le 40 ] && [ $get_capacity -ge 30 ]
   then
   echo "^b$black2^^c$lgorange^ 󰁽 $get_capacity%  "
  elif [ $get_capacity -le 30 ] && [ $get_capacity -ge 20 ]
   then
   echo "^b$black2^^c$dgorange^ 󰁼 $get_capacity%  "
  elif [ $get_capacity -le 20 ] && [ $get_capacity -ge 10 ]
   then
   echo "^b$black2^^c$red^ 󰁻 $get_capacity%  "
  elif [ $get_capacity -le 10 ]
   then
   echo "^b$black2^^c$gred^ 󰁺 $get_capacity%  "
fi
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$theotherone^^b$blue^ 󰖩 ^d^%s" "^c$blue^^b$theotherone^ Connected " ;;
	down) printf "^c$theotherone^^b$red^ 󰖪 ^d^%s" "^c$red^^b$theotherone^ Disconnected " ;;
	esac
}

clock() {
	printf "^c$black2^^b$whitegreen^ 󱑆 "
	printf "^c$black2^^b$tgreen^ $(date '+%H:%M') "
	printf "^c$black2^^b$whitegreen^ 󰨲 "
	printf "^c$black2^^b$tgreen^ $(date "+%u/%d/%m/%y")    " #this is 21st century for u future ppl
}

audio() {
	printf "^c$yellow^ 󰋋 "
	printf "^c$yellow^$(amixer sget Master | awk -F"[][]" '/Left:/ {print $2}')% "
}

charge() {
get_charge="$(cat /sys/class/power_supply/BAT1/status)"
 if [ "$get_charge" = Charging ]
 then
	 printf "^c$theotherone^^b$green^  " 
   printf "^c$green^^b$theotherone^ Charging "
fi
}

kblayout() {
	printf "^c$theotherone^^b$orange^ 󰌌 "
	printf "^c$orange^^b$theotherone^ $(setxkbmap -query | awk '/layout:/ {print $2}') "
}

while true; do

  [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
  interval=$((interval + 1))

  sleep 1 && xsetroot -name " $(audio)$(battery)$(charge)$(wlan)$(kblayout)$(clock)"
done
