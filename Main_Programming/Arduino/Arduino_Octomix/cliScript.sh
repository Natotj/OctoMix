echo "(1): Compile sketch"
echo "(2): Upload sketch"
echo "(3): Monitor sketch"
echo "(4): Everything"
echo ""

read options

if [ $options -eq 1 ]; then
  arduino-cli compile -p /dev/ttyACM0

elif [ $options -eq 2 ]; then
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno

elif [ $options -eq 3 ]; then
  echo "Enter baudrate: "
  read baudrate

  arduino-cli monitor -p /dev/ttyACM0 --config baudrate=31250

elif [ $options -eq 4 ]; then
  echo "Enter baudrate: "
  read baudrate

  arduino-cli compile -p /dev/ttyACM0
  arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno
  arduino-cli monitor -p /dev/ttyACM0 --config baudrate=$baudrate
fi
