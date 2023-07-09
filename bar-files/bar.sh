#!/bin/dash

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors
. ~/.config/dwm-config/bar-files/tokyonight 

cpu() {
  cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

  printf "^c$black^ ^b$red^ CPU"
  printf "^c$white^ ^b$black2^ $cpu_val"
}

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

battery() {
  get_capacity="$(cat /sys/class/power_supply/BAT1/capacity)"
  printf "^b$black^ ^c$blue^ 󰁹 $get_capacity"
}

brightness() {
  printf "^c$yellow^ "
  printf "^b$black^ ^c$yellow^%.0f\n" $(cat /sys/class/backlight/*/brightness)
}

mem() {
  printf "^c$black^ ^b$green^ MEM"
  printf "^c$white^ ^b$black2^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

swap() {
  printf "^b$blue^^c$black^ SWAP "
  printf "^c$white^ ^b$black2^ $(free -h | awk '/^Swap/ { print $3 }' | sed s/i//g)"
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$black^ ^b$blue^ 󰤨 ^d^%s" " ^c$blue^^b$terminalb^Connected" ;;
	down) printf "^c$black^ ^b$red^ 󰤭 ^d^%s" " ^c$red^^b$terminalb^Disconnected" ;;
	esac
}

clock() {
	printf "^c$black^ ^b$darkblue^ 󱑆 "
	printf "^c$black^^b$blue^ $(date '+%H:%M  ')  "
}

while true; do

  [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
  interval=$((interval + 1))

  sleep 1 && xsetroot -name " $(cpu) $(mem) $(swap) $(battery) $(brightness) $(wlan) $(clock)"
done
